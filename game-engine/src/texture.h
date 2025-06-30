#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D
{
public:
  unsigned int ID;
  unsigned int Width, Height;

  unsigned int Internal_Format; // format of texture object
  unsigned int Image_Format; // format of loaded image
  // texture config
  unsigned int Wrap_S;
  unsigned int Wrap_T;
  unsigned int Filter_Min;
  unsigned int Filter_Max;
  // constructor
  Texture2D();
  // generates texture from image data
  void Generate(unsigned int width, unsigned int height, unsigned char* data);
  // binds texture as the current active GL_TEXTURE_2D texture object
  void Bind() const;
};

#endif
