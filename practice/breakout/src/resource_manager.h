#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <iostream>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and sources are static and no public
// constructor defined.
//
// Notes: singleton a design pattern. Only one object of its kind
// exists and provides a single point of access it for any other code.
class ResourceManager 
{
public:
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
  // loads (and generates) a shader program from file loading vertex, fragment (and geom)
  static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile,
                           std::string name);
  // retrieves a stored shader
  static Shader& GetShader(std::string name);
  // loads (and generates) a texture form a file
  static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
  // retrieves a stored texture
  static Texture2D& GetTexture(std::string name);
  // de-allocated all loaded resources
  static void Clear();
private:
  // private constructor, don't want any actual resource manager objects
  ResourceManager() {}
  // loads and generates a shader from a file
  static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
  // loads a single texture from file
  static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif
