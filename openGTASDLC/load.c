#include "topdown.h"

unsigned char *loadMap(char *path) {
	FILE *mapfile;
	unsigned char databyte, x, y;
	unsigned char *mapdata;
	unsigned int temp1, temp2;

	mapfile = fopen(path, "r");
	if(!mapfile) {
		printf("Couldn't open map file.\n");
		exit(1);
	}

	/*Windows Y U NO support %hhu :(*/
	fscanf(mapfile, "%3ux%3u", &temp1, &temp2);
	mapWidth = (unsigned char)temp1;
	mapHeight = (unsigned char)temp2;

	/*printf("%ix%i.\n", mapWidth, mapHeight); */

	mapdata = (unsigned char *)calloc(mapWidth*mapHeight, sizeof(char));

	x = y = 0;
	while(x < mapWidth && y < mapHeight) {
		fscanf(mapfile, " %3u ", &temp1);
		databyte = (unsigned char)temp1;

		mapdata[y*mapWidth + x] = databyte;
		/*printf("%i ", databyte); */

		x++;
		if(x >= mapWidth) {
			x = 0;
			y++;
			/*printf("\n");*/
		}
	}

	fclose(mapfile);

	return mapdata;
}

int loadGLTextures() {
	int i;
	char pathstr[255];

	/* load road textures */

	if(!texturesLoaded) {
		for(i=0; i<NUM_ROAD_TYPES; i++) {
			sprintf(pathstr, "textures/road%i.bmp", i);
			textureImage[i] = SDL_LoadBMP(pathstr);
			glGenTextures(1, &texture[ROAD_ID_START+i]);
		}

		textureImageFont = SDL_LoadBMP("textures/font.bmp");
		if(!textureImageFont) return 0;

		textureImageBuilding = SDL_LoadBMP("textures/building.bmp");
		if(!textureImageBuilding) return 0;

		glGenTextures(1, &fontTexture);
		glGenTextures(1, &buildingTexture);

		texturesLoaded = 1;
	}

	for(i=0; i<NUM_ROAD_TYPES; i++) {
		glBindTexture(GL_TEXTURE_2D, texture[ROAD_ID_START+i]);

		/*gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureImage[i]->w, textureImage[i]->h, GL_BGR, GL_UNSIGNED_BYTE, textureImage[i]->pixels);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[i]->w, textureImage[i]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, textureImage[i]->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		/*SDL_FreeSurface(textureImage[i]);*/

	}

	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImageFont->w, textureImageFont->h, 0, GL_BGR, GL_UNSIGNED_BYTE, textureImageFont->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, buildingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImageBuilding->w, textureImageBuilding->h, 0, GL_BGR, GL_UNSIGNED_BYTE, textureImageBuilding->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	/*SDL_FreeSurface(textureImageFont);*/

	return 1;
}
