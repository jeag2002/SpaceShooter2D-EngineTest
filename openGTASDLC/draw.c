#include "topdown.h"

void drawMap() {
	int i, id, r, g, b, x, y;
	float height;

	glLoadIdentity();
	glTranslatef(-playerData.position.x, -playerData.position.y, 0.0);

	for(x=0; x<mapWidth; x++) {
		for(y=0; y<mapHeight; y++) {
			if(mapdata[y * mapWidth + x] >= HOUSE_ID_START) {
				/*house*/

				id = mapdata[y * mapWidth + x] - HOUSE_ID_START;
				height = (float)houses[id][0] / 100.0; /*TODO: this is arbitrary, load this from a file, see main.c*/
				r = houses[id][1];
				g = houses[id][2];
				b = houses[id][3];

				glDisable(GL_TEXTURE_2D);
				glPushMatrix();
				glTranslatef(x, (mapHeight-1-y), cameraHeight+(height/2.0));
				glScalef(1.0, 1.0, height);
				glColor3ub(r, g, b);
				drawBuilding();
				glPopMatrix();

			}
			else {

				/*road*/
				id = mapdata[y * mapWidth + x] - ROAD_ID_START;

				glEnable(GL_TEXTURE_2D);
				glPushMatrix();

				glTranslatef(x, (mapHeight-1-y), cameraHeight);


				glColor3f(1.0, 1.0, 1.0);
				glBindTexture(GL_TEXTURE_2D, texture[id]);
				glScalef(0.5, 0.5, 1.0);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
					glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 0.0);
					glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
					glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 0.0);
				glEnd();

				glPopMatrix();
			}
		}
	}
}

void drawPlayer() {
	switch(playerData.state) {
		case STATE_ONFOOT:
			/*A cube with an arrow will do for now*/
			/*Cube*/
			glDisable(GL_TEXTURE_2D);
			glLoadIdentity();
			glTranslatef(0.0, 0.0, cameraHeight);
			glRotatef(-playerData.rotation, 0.0, 0.0, 1.0);
			glScalef(0.08, 0.04, 0.08);
			glColor3f(1.0, 1.0, 0.0);
			drawCube();

			/*Arrow*/
			glTranslatef(0.0, 0.0, 0.6);
			glScalef(0.25, 0.25, 1.0);
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_TRIANGLES);
				glVertex3f(0.0, 1.0, 0.0);
				glVertex3f(-1.0,-1.0, 0.0);
				glVertex3f(1.0,-1.0, 0.0);
			glEnd();

			break;

		case STATE_DRIVING:
			glDisable(GL_TEXTURE_2D);
			glLoadIdentity();
			glTranslatef(0.0, 0.0, cameraHeight);
			glRotatef(-playerData.rotation, 0.0, 0.0, 1.0);
			glColor3f(1.0, 1.0, 0.0);

			/*Car*/
			glScalef(0.5, 0.5, 1.0);
			glBegin(GL_QUADS);
				glVertex3f(-playerData.carWidth, -playerData.carHeight, 0.0);
				glVertex3f(playerData.carWidth, -playerData.carHeight, 0.0);
				glVertex3f(playerData.carWidth, playerData.carHeight, 0.0);
				glVertex3f(-playerData.carWidth, playerData.carHeight, 0.0);
			glEnd();

			/*Arrow*/
			glTranslatef(0.0, 0.0, 0.1);
			glScalef(0.1, 0.1, 1.0);
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_TRIANGLES);
				glVertex3f(0.0, 1.0, 0.0);
				glVertex3f(-1.0,-1.0, 0.0);
				glVertex3f(1.0,-1.0, 0.0);
			glEnd();
			break;
	}
}

void drawPeds() {
	int i;

	for(i=0; i<numPeds; i++) {
			/*Cube*/
			glDisable(GL_TEXTURE_2D);
			glLoadIdentity();
			glTranslatef(-playerData.position.x, -playerData.position.y, 0.0);
			glTranslatef(pedData[i].position.x, mapHeight-pedData[i].position.y, cameraHeight);
			/*glScalef(-1, -1, 1);*/

			glRotatef(-pedData[i].rotation, 0.0, 0.0, 1.0);
			glScalef(0.08, 0.04, 0.08);
			glColor3f(1.0, 1.0, 0.0);
			drawCube();

			/*Arrow*/
			glTranslatef(0.0, 0.0, 2.0);
			glScalef(0.25, 0.25, 1.0);
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_TRIANGLES);
				glVertex3f(0.0, 1.0, 0.0);
				glVertex3f(-1.0,-1.0, 0.0);
				glVertex3f(1.0,-1.0, 0.0);
			glEnd();

	}
}

void drawInfo() {
	char infoStr[50];
	int tileX, tileY;

	viewOrtho();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(20, 20, 0);
	glPushMatrix();
		glScalef(8, -8, 1.0);
		sprintf(infoStr, "FPS: %.1f", fps);
		drawString(infoStr);
	glPopMatrix();


	glTranslatef(0, 20, 0);
	glPushMatrix();
		glScalef(8, -8, 1.0);

		sprintf(infoStr, "X:%.1f, Y:%.1f", playerData.position.x, playerData.position.y);
		drawString(infoStr);
	glPopMatrix();

	glTranslatef(0, 20, 0);
	glPushMatrix();
		glScalef(8, -8, 1.0);
		tileX = round(playerData.position.x);
		tileY = round(playerData.position.y);
		sprintf(infoStr, "Tile: %d, %d", tileX, tileY);
		drawString(infoStr);
	glPopMatrix();

	glTranslatef(0, 20, 0);
	glPushMatrix();
		glScalef(8, -8, 1.0);

		sprintf(infoStr, "Height: %.1f", -cameraHeight);
		drawString(infoStr);
	glPopMatrix();

	glTranslatef(0, 20, 0);
	glPushMatrix();
		glScalef(8, -8, 1.0);

		sprintf(infoStr, "Speed: %.2f", playerData.speed);
		drawString(infoStr);
	glPopMatrix();

	glTranslatef(0, 20, 0);
	glPushMatrix();
		glScalef(8, -8, 1.0);

		sprintf(infoStr, "Rotation: %03.0f", playerData.rotation);
		drawString(infoStr);
	glPopMatrix();


	viewPerspective();
}

void drawString(char *string) {
	int i;
	char down, right;

	glVertex3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, fontTexture);

	glPushMatrix();
	for(i=0; i<strlen(string); i++) {
		down = string[i] >> 4;
		right = string[i] & 0x0F;


		glBegin(GL_QUADS);

			glTexCoord2f((1.0/16.0) * right, (1.0/16.0) * down + (8.0/128.0)); glVertex3f(-1.0, -1.0, 0.0);
			glTexCoord2f((1.0/16.0) * right + (8.0/128.0), (1.0/16.0) * down + (8.0/128.0)); glVertex3f(1.0, -1.0, 0.0);
			glTexCoord2f((1.0/16.0) * right + (8.0/128.0), (1.0/16.0) * down); glVertex3f(1.0, 1.0, 0.0);
			glTexCoord2f((1.0/16.0) * right, (1.0/16.0) * down); glVertex3f(-1.0, 1.0, 0.0);
		/*
			glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 1.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 1.0);
			glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
*/
		glEnd();

		glTranslatef(2.0, 0.0, 0.0);
	}
	glPopMatrix();

	glDisable(GL_BLEND);
}

/*This is temporary*/
void drawBuilding() {
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, buildingTexture);

	glBegin(GL_QUADS);

	/* top*/
	/*glColor3f(0.0, 1.0, 0.0);*/
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);

	/*bottom*/
	/*glColor3f(1.0, 0.5f, 0.0);*/
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, -1.0);

	/*front*/
	/*glColor3f(1.0, 0.0, 0.0);*/
	glTexCoord2f(0.5, 0.5); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(1.0, -1.0, 1.0);

	/*back*/
	/*glColor3f(1.0, 1.0, 0.0);*/
	glTexCoord2f(0.5, 0.5); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(1.0, 1.0, -1.0);

	/*left*/
	/*glColor3f(0.0, 0.0, 1.0);*/
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);

	/*right*/
	/*glColor3f(1.0, 0.0, 1.0);*/
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, -1.0, -1.0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

/*This function is for testing purposes, hence the colors.*/
void drawCube() {
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);


	glBegin(GL_QUADS);
	/*top*
	/*glColor3f(0.0, 1.0, 0.0);*/
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);

	/*bottom*/
	/*glColor3f(1.0, 0.5f, 0.0);*/
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);

	/*front*/
	/*glColor3f(1.0, 0.0, 0.0);*/
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	/*back*/
	/*glColor3f(1.0, 1.0, 0.0);*/
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);

	/*left*/
	/*glColor3f(0.0, 0.0, 1.0);*/
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	/*right*/
	/*glColor3f(1.0, 0.0, 1.0);*/
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	/*top*/
	/*glColor3f(0.0, 1.0, 0.0);*/
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	/*bottom*/
	/*glColor3f(1.0, 0.5f, 0.0);*/
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	/*front*/
	/*glColor3f(1.0, 0.0, 0.0);*/
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	/*back*/
	/*glColor3f(1.0, 1.0, 0.0);*/
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	/*left*/
	/*glColor3f(0.0, 0.0, 1.0);*/
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	/*right*/
	/*glColor3f(1.0, 0.0, 1.0);*/
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	glPopMatrix();

}
