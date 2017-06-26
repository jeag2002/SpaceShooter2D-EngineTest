#include "topdown.h"

void movePeds() {
	int i;

	for(i=0; i<numPeds; i++) {
		pedData[i].position.x += pedData[i].direction.x * dt * pedData[i].speed;
		if(mapdata[(int)round(pedData[i].position.y) * mapWidth + (int)round(pedData[i].position.x)] >= HOUSE_ID_START) {
			pedData[i].direction.x = -pedData[i].direction.x;
		}

		pedData[i].position.y += pedData[i].direction.y * dt * pedData[i].speed;
		if(mapdata[(int)round(pedData[i].position.y) * mapWidth + (int)round(pedData[i].position.x)] >= HOUSE_ID_START) {
			pedData[i].direction.y = -pedData[i].direction.y;
		}
	}
}

void movePlayer() {
	float oldPosX, oldPosY, oldRot;
	int tileX, tileY;
	vector2 point1, point2, corner1, corner2, corner3, corner4, playerVec;

	switch(playerData.state) {
		case STATE_ONFOOT:
			oldPosX = playerData.position.x;
			oldPosY = playerData.position.y;

			playerData.rotation += playerRotating * dt * PLAYER_ROTATE_SPEED;
			while(playerData.rotation > 360.0) playerData.rotation -= 360.0;
			while(playerData.rotation < -360.0) playerData.rotation += 360.0;

			playerData.position.x += (playerMoving * dt * playerData.speed) * sin((playerData.rotation/360.0) * (2*M_PI));
			playerData.position.y += (playerMoving * dt * playerData.speed) * cos((playerData.rotation/360.0) * (2*M_PI));

			/*check for collision with all walls surrounding current tile*/
			tileX = round(playerData.position.x);
			tileY = mapHeight - 1 - round(playerData.position.y);

			playerVec.x = playerData.position.x;
			playerVec.y = mapHeight - 1 - playerData.position.y;

            /*
			if(tileX > 0) {
				if(mapdata[(tileY) * mapWidth + (tileX-1)] >= HOUSE_ID_START) {
					point1.x = (tileX-1) + 0.5;
					point1.y = (tileY) - 0.5;

					point2.x = (tileX-1) + 0.5;
					point2.y = (tileY) + 0.5;

					if(collideCircle(playerVec, playerData.radius, point1, point2)) {
						playerData.position.x = oldPosX;
					}
				}
			}

			if(tileX < mapWidth-1) {
				if(mapdata[(tileY) * mapWidth + (tileX+1)] >= HOUSE_ID_START) {
					point1.x = (tileX+1) - 0.5;
					point1.y = (tileY) - 0.5;

					point2.x = (tileX+1) - 0.5;
					point2.y = (tileY) + 0.5;

					if(collideCircle(playerVec, playerData.radius, point1, point2)) {
						playerData.position.x = oldPosX;
					}
				}
			}

			if(tileY > 0) {
				if(mapdata[(tileY-1) * mapWidth + (tileX)] >= HOUSE_ID_START) {
					point1.x = (tileX) + 0.5;
					point1.y = (tileY-1) + 0.5;

					point2.x = (tileX) - 0.5;
					point2.y = (tileY-1) + 0.5;

					if(collideCircle(playerVec, playerData.radius, point1, point2)) {
						playerData.position.y = oldPosY;
					}
				}
			}

			if(tileY < mapHeight-1) {
				if(mapdata[(tileY+1) * mapWidth + (tileX)] >= HOUSE_ID_START) {
					point1.x = (tileX) + 0.5;
					point1.y = (tileY+1) - 0.5;

					point2.x = (tileX) - 0.5;
					point2.y = (tileY+1) - 0.5;

					if(collideCircle(playerVec, playerData.radius, point1, point2)) {
						playerData.position.y = oldPosY;
					}
				}
			}
			*/
			break;

		case STATE_DRIVING:
			oldPosX = playerData.position.x;
			oldPosY = playerData.position.y;
			oldRot = playerData.rotation;

			if(playerData.speed > 0 && playerMoving == 0) playerData.speed -= playerData.speedDecay * dt;
			if(playerData.speed < 0 && playerMoving == 0) playerData.speed += playerData.speedDecay * dt;

			if(playerMoving > 0) {
				playerData.speed += playerData.carAcceleration * dt;
			}
			else if(playerMoving < 0 && playerData.speed > 0) {
				/*brake*/
				playerData.speed -= 2.0 * playerData.carAcceleration * dt;
			}
			else if(playerMoving < 0 && playerData.speed <= 0) {
				/*reverse*/
				playerData.speed -= 0.5 * playerData.carAcceleration * dt;
			}

			if(playerData.speed > playerData.carMaxSpeed) playerData.speed = playerData.carMaxSpeed;
			if(playerData.speed < -playerData.carMaxReverseSpeed) playerData.speed = -playerData.carMaxReverseSpeed;

			playerData.rotation += playerRotating * (playerData.speed / playerData.carMaxSpeed) * dt * playerData.carRotateSpeed;

			while(playerData.rotation < 0.0) playerData.rotation += 360.0;
			while(playerData.rotation > 360.0) playerData.rotation -= 360.0;

			playerData.position.x += playerData.speed * dt * sin((playerData.rotation/360.0) * (2*M_PI));
			playerData.position.y += playerData.speed * dt * cos((playerData.rotation/360.0) * (2*M_PI));


			/*check for collision with all walls surrounding current tile*/
			tileX = round(playerData.position.x);
			tileY = mapHeight - 1 - round(playerData.position.y);

			playerVec.x = playerData.position.x;
			playerVec.y = mapHeight - 1 - playerData.position.y;



			corner1.x = -(playerData.carWidth/2.0);
			corner1.y = -(playerData.carHeight/2.0);
			corner1.x = corner1.x * cos((playerData.rotation/360.0)*(2*M_PI)) - corner1.y * sin((playerData.rotation/360.0)*(2*M_PI));
			corner1.y = corner1.x * sin((playerData.rotation/360.0)*(2*M_PI)) + corner1.y * cos((playerData.rotation/360.0)*(2*M_PI));
			corner1.x += playerVec.x;
			corner1.y += playerVec.y;


			corner2.x = (playerData.carWidth/2.0);
			corner2.y = (playerData.carHeight/2.0);
			corner2.x = corner2.x * cos((playerData.rotation/360.0)*(2*M_PI)) - corner2.y * sin((playerData.rotation/360.0)*(2*M_PI));
			corner2.y = corner2.x * sin((playerData.rotation/360.0)*(2*M_PI)) + corner2.y * cos((playerData.rotation/360.0)*(2*M_PI));
			corner2.x += playerVec.x;
			corner2.y += playerVec.y;

			corner3.x = (playerData.carWidth/2.0);
			corner3.y = -(playerData.carHeight/2.0);
			corner3.x = corner3.x * cos((playerData.rotation/360.0)*(2*M_PI)) - corner3.y * sin((playerData.rotation/360.0)*(2*M_PI));
			corner3.y = corner3.x * sin((playerData.rotation/360.0)*(2*M_PI)) + corner3.y * cos((playerData.rotation/360.0)*(2*M_PI));
			corner3.x += playerVec.x;
			corner3.y += playerVec.y;

			corner4.x = -(playerData.carWidth/2.0);
			corner4.y = (playerData.carHeight/2.0);
			corner4.x = corner4.x * cos((playerData.rotation/360.0)*(2*M_PI)) - corner4.y * sin((playerData.rotation/360.0)*(2*M_PI));
			corner4.y = corner4.x * sin((playerData.rotation/360.0)*(2*M_PI)) + corner4.y * cos((playerData.rotation/360.0)*(2*M_PI));
			corner4.x += playerVec.x;
			corner4.y += playerVec.y;



			if(tileX > 0) {
				if(mapdata[(tileY) * mapWidth + (tileX-1)] >= HOUSE_ID_START) {
					point1.x = (tileX-1) + 0.5;
					point1.y = (tileY) - 0.5;

					point2.x = (tileX-1) + 0.5;
					point2.y = (tileY) + 0.5;

					if(collideRectangle(corner1, corner2, corner3, corner4, point1, point2)) {
						playerData.position.x = oldPosX;
						playerData.position.y = oldPosY;
						playerData.rotation = oldRot;
					}
				}
			}

			if(tileX < mapWidth-1) {
				if(mapdata[(tileY) * mapWidth + (tileX+1)] >= HOUSE_ID_START) {
					point1.x = (tileX+1) - 0.5;
					point1.y = (tileY) - 0.5;

					point2.x = (tileX+1) - 0.5;
					point2.y = (tileY) + 0.5;

					if(collideRectangle(corner1, corner2, corner3, corner4, point1, point2)) {
						playerData.position.x = oldPosX;
						playerData.position.y = oldPosY;
						playerData.rotation = oldRot;
					}
				}
			}

			if(tileY > 0) {
				if(mapdata[(tileY-1) * mapWidth + (tileX)] >= HOUSE_ID_START) {
					point1.x = (tileX) + 0.5;
					point1.y = (tileY-1) + 0.5;

					point2.x = (tileX) - 0.5;
					point2.y = (tileY-1) + 0.5;

					if(collideRectangle(corner1, corner2, corner3, corner4, point1, point2)) {
						playerData.position.x = oldPosX;
						playerData.position.y = oldPosY;
						playerData.rotation = oldRot;
					}
				}
			}

			if(tileY < mapHeight-1) {
				if(mapdata[(tileY+1) * mapWidth + (tileX)] >= HOUSE_ID_START) {
					point1.x = (tileX) + 0.5;
					point1.y = (tileY+1) - 0.5;

					point2.x = (tileX) - 0.5;
					point2.y = (tileY+1) - 0.5;

					if(collideRectangle(corner1, corner2, corner3, corner4, point1, point2)) {
						playerData.position.x = oldPosX;
						playerData.position.y = oldPosY;
						playerData.rotation = oldRot;
					}
				}
			}



			break;

	}
}
