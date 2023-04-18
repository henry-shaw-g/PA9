/*
	file: GuiContainer
	desc: class that has a position and size and holds child elements / containers
*/

#pragma once

#include "SFML/Graphics.hpp"

class GuiContainer : public sf::Drawable {
public:
	
	// ctor: default
	GuiContainer();

	// delete: ctor: copy
	GuiContainer(const GuiContainer&) = delete;

	// desc: uses sfml idiom to draw to the render target (probably the render window)
	//	- we are probably gonna end up overriding this a lot
	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;

	// dtor:
	~GuiContainer();

	// public members:
	bool visible;
private:

	// desc: we can throw any coupled rendering in here
	virtual void drawCustom(sf::RenderTarget& renderTarget) const;
	
	// private members:
	sf::Rect<float> _rect;
};