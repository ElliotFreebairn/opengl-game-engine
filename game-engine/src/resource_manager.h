#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"

// Resource Manager hosts several functions to load Textures and Shaders.
// Each loaded texture/shader is stored for future reference by string 
// handles. All static and no public constructor
class ResourceManager
{
public:
  // resource storage
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
  // loads and generates a shader program from file
  static Shader LoadShader(const char *vShaderFile, const char *fShaderFile,
                           std::string name);
  // retrieves a stored shader
  static Shader GetShader(std::string name);
  // loads and generates a texture from a file
  static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
  // retrieves a stored texture
  static Texture2D GetTexture(std::string name);
  // properly de-allocates all loaded resources
  static void Clear();
private:
  ResourceManager() {}
  // loads and generates a shader from file
  static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);
  // loads a single texture from file
  static Texture2D loadTextureFromFile(const char *file, bool alpha);
};
#endif
