/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifdef WIN32
#include <windows.h>
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "glcontrol.h"
#include "Player.h"
#include "RocketMan.h"
#include "arena.h"
#include "FixedTrig.h"
#include "GameContext.h"
#include "Heart.h"
#include "text.h"
#include "wiz.h"
#include "ExplosionParticle.h"

#include "defines.h"

static Heart *heart;

void DrawHUD(GameContext *context, Player *player) {

  static clock_t lastClock = clock();
  static int frameCount = 0;
  static int lastFPS = 0;

  glLoadIdentity();


  // Display the health hearts
  if (player) {
    for (int i = 0; i < player->hitPoints; i++) {
      heart->SetXY(f2x(280 + i * 16), f2x(8));
      heart->Draw();
    }
  }

  char szBuff[120];
  glColor4x(0, 0, 0, f2x(1));
  sprintf(szBuff, "SCORE:%04d", context->GetScore());
  DrawCenteredString(szBuff, f2x(160), f2x(32), f2x(3.0));

#if 1
  glColor4x(f2x(.25), f2x(.25), f2x(.9), f2x(1));
  sprintf(szBuff, "%03d", lastFPS);
  DrawCenteredString(szBuff, f2x(30), f2x(23), f2x(2.0));

  frameCount++;
  clock_t count = clock();
  if (count - lastClock > CLOCKS_PER_SEC) {
    lastFPS = frameCount / ((count - lastClock) / CLOCKS_PER_SEC);
    lastClock = count;
    frameCount = 0;
  };
#endif

}

#ifdef WIN32
// Main entry point to program.  Windows specific, but the guts of this should be reusable in another OS appropriate main().
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{

  // Randomize!
  srand( (unsigned)time( NULL ) );

  GameContext *context = new GameContext(TextureManager::GetInstance(), new ObjectManager(), new ObjectManager(), Input::GetInstance());

  GLControl *gl = new GLControl();

  //**********
  // Note that any GameObject creation needs to be done after the following INIT
  //**********

#ifdef WIN32
  if (gl->Init(hInstance)) {
#else
  WIZ_Init();
  if (gl->Init()) {
#endif

#if 1
    printf("Initialed GL\n");
    // Load in our textures
    if (context->texMgr->LoadTextures()) {
      printf("Loaded Textures\n");
      // Initialize some special textures
      context->texMgr->PreMultiplyAlpha(context->texMgr->GetRawTexture(T_WHITE16), context->texMgr->GetRawTexture(T_SMOKE), T_SMOKE);
      context->texMgr->PreMultiplyAlpha(context->texMgr->GetRawTexture(T_ROCKET), context->texMgr->GetRawTexture(T_ROCKET_A), T_ROCKET);
      context->texMgr->PreMultiplyAlpha(context->texMgr->GetRawTexture(T_GREEN32), context->texMgr->GetRawTexture(T_CIRCLE), T_CIRCLE);
	    context->texMgr->PreMultiplyAlpha(context->texMgr->GetRawTexture(T_WHITE64), context->texMgr->GetRawTexture(T_CLOUD), T_CLOUD);
	    context->texMgr->PreMultiplyAlpha(context->texMgr->GetRawTexture(T_HEART), context->texMgr->GetRawTexture(T_HEART_A), T_HEART);

      printf("Configured Textures\n");

      // Set our background color
      glClearColorx(f2x(217.0 / 255.0), f2x(222.0/255.0), f2x(224.0/255.0), 0);

      // Add the player to the mix
      Player *player = new Player(context);
      player->SetXY(f2x(120), f2x(120));
      context->objMgr->Add(player);

      // Add an initial enemy
      RocketMan *boss = new RocketMan(context);
      boss->SetXY(f2x(240), f2x(200));
      context->objMgr->Add(boss);

      Arena *arena = new Arena();

      heart = new Heart();

      printf("Starting loop\n");

      int count = 0;

      while (context->input->select == false) {

        context->input->Refresh();

#if 0
        if (context->input->fireBtn && context->fxMgr->Count() == 0) {
          ExplosionParticle *exp = new ExplosionParticle(600, count);
          exp->SetXY(f2x(160), f2x(120));
          context->fxMgr->Add(exp);
          count++;
        }
#endif

        player = (Player *)context->objMgr->GetPlayer();

        glColor4x(f2x(1), f2x(1), f2x(1), f2x(1));
        glClear(GL_COLOR_BUFFER_BIT);

        // Update all objects
        context->objMgr->UpdateAll();

        // Comment this out to not rotate the view around the player
#if 1
        // Center the view around the player
        if (player) {
          glLoadIdentity();
          glTranslatex(f2x(320 / 2) - player->GetX(),  f2x(240 / 2) - player->GetY(), 0);
          glTranslatex(player->GetX(),  player->GetY(), 0);
          glRotatex(f2x(90), 0, 0, f2x(1));
          glRotatex(-player->GetAngle(), 0, 0, f2x(1));
          glTranslatex(-player->GetX(),  -player->GetY(), 0);

        } else {
          glLoadIdentity();
        }
#endif

        arena->Draw();

        // Draw all objects
        context->objMgr->DrawAll();

        // Update all effects (only smoke SmokeParticles so far)
        context->fxMgr->UpdateAll();
        // Draw all effects
        context->fxMgr->DrawAll();

        // Draw the HUD
        DrawHUD(context, player);

        // Flip the page and read input
        gl->Pump();
      }

      printf("Cleaning up\n");

      context->texMgr->FreeTextures();
      context->objMgr->DeleteAll();
      context->fxMgr->DeleteAll();
    }
#endif
  }

  gl->Term();

#ifndef WIN32
  WIZ_Close();
#endif

  return 0;

}

