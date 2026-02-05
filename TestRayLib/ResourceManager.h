#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <raylib.h>
#include <iostream>


//carga y gestiona recursos de raylib

class ResourceManager
{

public:
	//acceso a la instancia (singleton)

	static ResourceManager& instance() {
		static ResourceManager rm; 
		return rm; 
	}


	//obtener textura (carga automatica si no existe)
	std::shared_ptr<Texture2D> getTexture(const std::string& file) {
		std::string fullPath = texturePath + file;   //concatenar path base 
		auto it = textures.find(fullPath);
		if (it != textures.end()) return it->second; //si ya esta cargada, volver

		//verificar si existe un archivo 
		if (!FileExists(fullPath.c_str()))
		{
			Log::print("ERROR: no se encontro textura: " + fullPath);
			return nullptr; 

		}

		auto tex = std::make_shared<Texture2D>(LoadTexture(fullPath.c_str())); //cargar 
		textures[fullPath] = tex; 
		return tex; 

		
	
	}
};

