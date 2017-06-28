#ifndef MOD_H_INCLUDED
#define MOD_H_INCLUDED

#include "GLGraphics.h"
#include "Debug.h"
#include "Bullets.h"
#include "vector2.h"
#include "vector3.h"
#include "GLText.h"

#define R_COLOR  0x00000001
#define G_COLOR  0x00000002
#define B_COLOR  0x00000004
#define A_COLOR  0x00000008
#define X_POS    0x00000010
#define Y_POS    0x00000020
#define ROT      0x00000040
#define TEXTURE  0x00000100
#define X_SIZE   0x00000200
#define Y_SIZE   0x00000400
#define SET_MASK 0x00000FFF
#define DAMAGE_MOD 0x00001000
#define SHIELD_MOD 0x00002000
#define BUBBLE_MOD 0x00003000
#define MOD_MASK   0x0000F000

class Mod{
	public:
		Mod(vector2, vector2, int, int, int, int);
		virtual ~Mod();
		void Set(unsigned int, float);
		float Get(unsigned int);
		friend class Ship;
		friend class PlayerShip;
		friend class aiShip;
		friend class Game;
	protected:
        virtual int Update(int, int, int, float);
        virtual void Draw();
        virtual void OnEvent(SDL_Event*, float);
        virtual void CheckCollide(BulletManager*, float);
        virtual void OnCollide();
        virtual void AI(vector2);
		vector2 pos, off;
		vector2 size;
		int t;
		float relT;
		int r,g,b,a;
		GLuint texture;
		GLuint* vbo;
		unsigned int type;
	private:

};

#endif // MOD_H_INCLUDED

