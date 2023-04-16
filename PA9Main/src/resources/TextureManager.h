/*
	file: Textures.h
	authors: Chase, Henry, Korbyn
	desc:
		- service that loads and keeps references to all textures
		- for now, since the texture lifetimes need to last for the entire program, we are just using a singleton to hold the textures, and elsewhere they can be referenced
	todo:
		- add an index for slices of spritesheets
	
*/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> // this probably could have been implemented with a BST, but the STL hash maps are reliable, and probably faster

#include "SFML/Graphics.hpp"

class TextureManager {
public:
	// ctor: copy
	// desc: deleted to enforce singleton
	TextureManager(const TextureManager&) = delete;

	// dtor:
	// desc: may use in the future to deallocate textures at end of program
	//~TextureManager();

	// desc: initializes the singleton
	static void init();

	// desc: gets the singleton
	static TextureManager& service();

	// desc: get a reference to a texture (make sure not to copy)
	const sf::Texture& getTextureRef(const std::string& textureId);

	// desc: get a pointer to the texture (idk, might need)
	const sf::Texture* getTexturePtr(const std::string& textureId);

private:
	// ctor: default
	// desc: private to enforce singleton
	TextureManager();

	// desc: this will be where we enter all the files to load
	bool loadGameTextures();

	// desc: given the path, loads a texture from a file and stores it in the search datastructure with the given id)
	bool loadTexture(const std::string& textureId, const std::string& path);

	/* STATIC MEMBERS */
	static bool _initialized;
	static TextureManager _singleton;

	/* MEMBERS */
	std::unordered_map<std::string, sf::Texture*> _textures;
};