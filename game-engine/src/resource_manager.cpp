#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile,
                                   std::string name)
{
  Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
  return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
  return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
  Textures[name] = loadTextureFromFile(file, alpha);
  return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
  return Textures[name];
}

void ResourceManager::Clear()
{
  for (auto iter : Shaders)
    glDeleteProgram(iter.second.ID);
  for (auto iter : Textures)
    glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile)
{
  // retrieve the vertex/fragment source code from file
  std::string vertexCode;
  std::string fragmentCode;
  try {
    // open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::exception e)
  {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // create shader object from source code'
  Shader shader;
  shader.Compile(vShaderCode, fShaderCode);
  return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
  Texture2D texture;
  // load image
  int width, height, nrChannels;
  unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

  if (nrChannels == 4) {
      texture.Internal_Format = GL_RGBA;
      texture.Image_Format = GL_RGBA;
  } else if (nrChannels == 3) {
      texture.Internal_Format = GL_RGB;
      texture.Image_Format = GL_RGB;
  } else {
      std::cerr << "Unsupported number of channels: " << nrChannels << std::endl;
      stbi_image_free(data);
      return texture;
  }

  // generate texture
  texture.Generate(width, height, data);
  // free image data
  stbi_image_free(data);
  return texture;
}
