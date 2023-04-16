/*
	file: ResourceManager
	desc:
		- singleton
		- holds all the non-lightweight objects
			that need to exist for the lifetime of the program
			and potentially be referenced by many users in the program
		- could have used a BST but we <3 STL & hashmaps
*/
#pragma once

#include <string>
#include <unordered_map> // hashmap

#include "SFML/Graphics.hpp" // texture, font
class ResourceManager {
public:
	// desc: statically loads the resource manager
	//	made static so we don't accidently call load somewhere on the object
	static bool load();

	// desc: gets the resource manager singleton
	static ResourceManager& service();

	// ctor: copy
	// desc: deleted to maintain singleton
	ResourceManager(ResourceManager&) = delete;
	
	// dtor:
	// desc: might need
	//~ResourceManager();

	// desc: get const ref to a texture
	// precond: the texture at the id is loaded
	const sf::Texture& getTextureRef(const std::string& id) const;

	// desc: get const ref to a font
	const sf::Font& getFontRef(const std::string& id) const;


private:
	// desc: here to be singletoon
	ResourceManager();

	// desc: here we will define / implement the loading routine
	bool doLoad(); 

	// desc: utility to load a single texture resource
	bool loadTexture(const std::string& id, const std::string& path);

	// desc: utility to load a single font resource
	bool loadFont(const std::string& id, const std::string& path);

	// members
	std::unordered_map<std::string, sf::Texture> _textures;
	std::unordered_map<std::string, sf::Font> _fonts;

	// singleton state
	static bool isLoaded;
	static ResourceManager singleton;
};