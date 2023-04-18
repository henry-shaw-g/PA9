/*
	file: ResourceManager.cpp
	desc: implements ResourceManager
*/

#include <iostream>
#include <stdexcept>
#include "ResourceManager.h"

using std::string;
using std::runtime_error;
using std::logic_error;

// define the static ResourceManager members
bool ResourceManager::isLoaded = false;
ResourceManager ResourceManager::singleton;

/* UTILITY */
template<typename T>
const T& getResourceRef(const std::unordered_map<string, T>& map, const string& id) {
	if (map.count(id) < 1) {
		throw logic_error("Tried to get resource with invalid id.");
	}
	return map.at(id);
}

template<typename T>
const T* getResourcePtr(const std::unordered_map<string, T>& map, const string& id) {
	if (map.count(id) < 1) {
		throw logic_error("Tried to get resource with invalid id.");
	}
	return &(map.at(id));
}

/* STATIC */
bool ResourceManager::load()
{
	if (ResourceManager::isLoaded) {
		throw logic_error("Tried to load ResourceManager, already loaded.");
	}
	ResourceManager::isLoaded = true;
	return ResourceManager::singleton.doLoad();
}

ResourceManager& ResourceManager::service() 
{
	if (!ResourceManager::isLoaded) {
		// don't want any possible get attempts if we haven't loaded everything
		throw logic_error("Tried to get ResourceManager sfervice, not loaded.");
	}
	return ResourceManager::singleton;
}

/* CLASS */
ResourceManager::ResourceManager() {}

const sf::Texture& ResourceManager::getTextureRef(const string& id) const
{
	return getResourceRef(_textures, id);
}

const sf::Font& ResourceManager::getFontRef(const string& id) const
{
	return getResourceRef(_fonts, id);
}

bool ResourceManager::doLoad() {
	// load textures
	loadTexture("smiley_face_0", "assets/smiley_face_0.png");
	loadTexture("tank_blue", "assets/tank_sprites/tank_blue");
	// load font(s?)
	loadFont("freecam_font", "assets/fonts/freecam v2.ttf");
	return true;
}

bool ResourceManager::loadTexture(const string& id, const string& path) 
{
	if (_textures.count(id) > 0) {
		std::cout << "Warning: tried to load texture for duplicate id. id: " << id << '\n';
		return false;
	}
	sf::Texture& texture = _textures[id]; // todo: can this fail?
	if (!texture.loadFromFile(path)) {
		std::cout << "Warning: failed to load texture from file. path: " << path << '\n';
		_textures.erase(id);
		return false;
	}
	return true;
}

bool ResourceManager::loadFont(const string& id, const string& path) {
	if (_fonts.count(id) > 0) {
		std::cout << "Warning: tried to load font for duplicate id. id: " << id << '\n';
		return false;
	}
	sf::Font& font = _fonts[id];
	if (!font.loadFromFile(path)) {
		std::cout << "Warning: failed to load font from file. path" << path << '\n';
		_fonts.erase(id);
		return false;
	}
	return true;
}