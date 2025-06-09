#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>


// Texture2D able to store and configure a texture in OpenGL
// Also has utility functions for easy management
class Texture2D
{
public:
  // olds the ID of the texture object
  unsigned int ID;
  // texture image dimensions
  unsigned int Width, Height;
  // texture format
  unsigned int Internal_Format; // format of texture object
  unsigned int Image_Format; // format of loaded image
  // texture configuration
  unsigned int Wrap_S;
  unsigned int Wrap_T; // wrapping mode on T axis
  unsigned int Filter_Min; // filtering mode if texture pixels > screen pixels
  unsigned int Filter_Maxl; // filtering mode if texture pixels < screen pixels
  
  // constructor
  Texture2D();
  // generates texture form image data
  void Generate(unsigned int width, unsigned int height, unsigned char* data);
  // binds the texture as the current active GL_TEXTURE_2D object
  void Bind() const;


};

#endif
