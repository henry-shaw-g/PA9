#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/Body.h"


class Wall 
{

public:
	Wall() {height = 0.0; width = 0.0; xpos = 0, ypos = 0; };
	Wall(float newheight, float newwidth, int newxpos, int newypos);



private:
	float height;
	float width;
	int xpos;
	int ypos;
};