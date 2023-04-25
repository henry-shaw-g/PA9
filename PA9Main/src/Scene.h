/*
	file: Scene.h
	desc: 
		- inteface/ abstract class for organizing rendering and updating of 'scenes'
		- is mostly an interface

*/
#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Scene {
public:
	virtual void init() = 0;

	virtual void update(float dt) = 0;

	virtual void draw(sf::RenderTarget renderTarget) = 0;
protected:
};