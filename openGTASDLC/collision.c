#include "topdown.h"

/*
  point1/point2 define the plane to collide with
  returns 1 when colliding, 0 when not
*/
int collideCircle(vector2 center, float radius, vector2 point1, vector2 point2) {
	float a = center.x - point1.x;
	float b = center.y - point1.y;
	float c = point2.x - point1.x;
	float d = point2.y - point1.y;

	float dot = a * c + b * d;
	float len = c * c + d * d;
	float param = dot / len;

	float x, y;

	if(param < 0) {
		x = point1.x;
		y = point1.y;
	}
	else if(param > 1) {
		x = point2.x;
		y = point2.y;
	}
	else {
		x = point1.x + param * c;
		y = point1.y + param * d;
	}

	return sqrt((center.x-x)*(center.x-x) + (center.y-y)*(center.y-y)) <= radius;
}

/*
  point1/point2 define the line to collide with
  corner1/corner2 define the rectangle
  returns 1 when colliding, 0 when not
*/
int collideRectangle(vector2 corner1, vector2 corner2, vector2 corner3, vector2 corner4, vector2 point1, vector2 point2) {
	float line;


/*
	// vertical line
	if(point1.x == point2.x) {
		line = point1.x;

		if(side == 0) {
			// wall on the right

			if(corner1.x < line && corner2.x < line && corner3.x < line && corner4.x < line) {
				return 0;
			}
			else if(corner1.x > line && corner2.x < line && corner3.x < line && corner4.x < line) {
				if((corner1.y > point1.y && corner1.y < point2.y) || (corner1.y < point1.y && corner1.y > point2.y)) {
					return 1;
				}

				printf("ja\n");
			}
			else if(corner1.x < line && corner2.x > line && corner3.x < line && corner4.x < line) {
				if((corner2.y > point1.y && corner2.y < point2.y) || (corner2.y < point1.y && corner2.y > point2.y)) {
					return 1;
				}
			}
			else if(corner1.x < line && corner2.x < line && corner3.x > line && corner4.x < line) {
				if((corner3.y > point1.y && corner3.y < point2.y) || (corner3.y < point1.y && corner3.y > point2.y)) {
					return 1;
				}
			}
			else if(corner1.x < line && corner2.x < line && corner3.x < line && corner4.x > line) {
				if((corner4.y > point1.y && corner4.y < point2.y) || (corner4.y < point1.y && corner4.y > point2.y)) {
					return 1;
				}
			}
		}
		else{
			// wall on the left

			if(corner1.x > line && corner2.x > line && corner3.x > line && corner4.x > line) {
				return 0;
			}
			else if(corner1.x < line && corner2.x > line && corner3.x > line && corner4.x > line) {
				if((corner1.y > point1.y && corner1.y < point2.y) || (corner1.y < point1.y && corner1.y > point2.y)) {
					return 1;
				}
			}
			else if(corner1.x > line && corner2.x < line && corner3.x > line && corner4.x > line) {
				if((corner2.y > point1.y && corner2.y < point2.y) || (corner2.y < point1.y && corner2.y > point2.y)) {
					return 1;
				}
			}
			else if(corner1.x > line && corner2.x > line && corner3.x < line && corner4.x > line) {
				if((corner3.y > point1.y && corner3.y < point2.y) || (corner3.y < point1.y && corner3.y > point2.y)) {
					return 1;
				}
			}
			else if(corner1.x > line && corner2.x > line && corner3.x > line && corner4.x < line) {
				if((corner4.y > point1.y && corner4.y < point2.y) || (corner4.y < point1.y && corner4.y > point2.y)) {
					return 1;
				}
			}
		}

	}
	// horizontal line
	else if(point1.y == point2.y) {

	}
	else {
*/
		/* TODO: Make this work for angled lines */


		if(intersectLines(corner1, corner2, point1, point2)) return 1;
		if(intersectLines(corner2, corner3, point1, point2)) return 1;
		if(intersectLines(corner3, corner4, point1, point2)) return 1;
		if(intersectLines(corner4, corner1, point1, point2)) return 1;

/*
	}
*/
	return 0;
}

int intersectLines(vector2 point1, vector2 point2, vector2 point3, vector2 point4) {
	float a, b, c, d, e;

	point2.x -= point1.x; point2.y -= point1.y;
	point3.x -= point1.x; point3.y -= point1.y;
	point4.x -= point1.x; point4.y -= point1.y;

	a = sqrt(point2.x*point2.x + point2.y*point2.y);

	b = point2.x / a;
	c = point2.y / a;

	d = point3.x*b + point3.y*c;
	point3.y = point3.y*b - point3.x*c;
	point3.x = d;

	d = point4.x*b + point4.y*c;
	point4.y  = point4.y*b - point4.x*c;
	point4.x = d;

	if(point3.y < 0 && point4.y < 0 || point3.y >= 0 && point4.y >= 0) {
		return 0;
	}

	e = point4.x+(point3.x-point4.x) * point4.y/(point4.y-point3.y);

	if(e < 0 || e > a) {
		return 0;
	}

	return 1;
}
