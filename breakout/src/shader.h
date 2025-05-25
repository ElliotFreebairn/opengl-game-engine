#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_prt.hpp>

class Shader {
public:
  // state
  unsigned int ID;
  // constructor
  Shader()  {}
  // sets the current shader as active
  Shader &Use();
  // compile the shader from given source code
  void Compile(const char  *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
  // utility functions
  void SetFloat(const char *name, float value, bool useShader = false);
  void SetInteger(const char *name, int value, bool useShader = false);
  void SetVector2f(const char *name, float x, float y, bool useShader = false);
}
