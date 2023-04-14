/*
	file: Textures.cpp
	desc: 
		- implements the textures service
		- note: i am abusing expceptions here
*/

#include "TextureManager.h"

using std::cout;

/* STATIC */

// define/initialize the static class member (same method as extern)
bool TextureManager::_initialized = false;
TextureManager TextureManager::_singleton;

void TextureManager::init() {
	if (_initialized)
		throw "Can't initialize TextureManager service, already initialized.";

	_singleton.loadGameTextures();
	_initialized = true;
}

TextureManager& TextureManager::service() {
	if (!_initialized)
		throw "Can't get TextureManager service, not initialized.";
	return _singleton;
}

/* NON-STATIC */
TextureManager::TextureManager() {}

const sf::Texture& TextureManager::getTextureRef(const std::string& textureId) {
	/*if (_textures.count(textureId)) {
		cout << "warning: attempting to get unloaded texture, id: " << textureId << '\n';
	}
	return _textures[textureId];*/
	return *getTexturePtr(textureId);
}

const sf::Texture* TextureManager::getTexturePtr(const std::string& textureId)
{
	if (_textures.count(textureId) < 1) {
		cout << "warning: attempting to get unloaded texture, id: " << textureId << '\n';
	}
	return _textures[textureId];
}

bool TextureManager::loadGameTextures()
{
	loadTexture("smiley_face_0", "assets/smiley_face_0.png");
	return true;
}

bool TextureManager::loadTexture(const std::string& textureId, const std::string& path)
{
	if (_textures.count(textureId) > 0) {
		return false; // a texture is already loaded for the texture id
		cout << "warning: could not load texture, id already exists, id: " << textureId << '\n';
	}

	sf::Texture* texturePtr = new sf::Texture();
	if (texturePtr == nullptr)
		return false;

	//sf::Texture temp; // this might be bad
	//sf::Texture reffed = _textures.insert(textureId); // temporarily let the texture exist in the table
	bool success = texturePtr->loadFromFile(path);
	if (!success) {
		// remove the the texture from the table
		cout << "warning: could not load texture from file, path: " << path << '\n';

	}
	else {
		_textures[textureId] = texturePtr;
		cout << "loaded texture, path: " << path << ", id: " << textureId << 'n';
	}

	return success;
}
