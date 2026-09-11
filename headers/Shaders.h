#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#define DEFAULT_SHADER_PATH "/shaders/"
#define DEFAULT_VERT_SHADER "vert.gvr"
#define DEFAULT_FRAG_SHADER "frag.gfr"
namespace Shaders{
  enum Uni {
    Float = 0x01,
    Vector2 = 0x011,
    Vector3 = 0x012,

    Matrix3 = 0x02,
    Matrix4 = 0x021
  };

  class Shader{
    private:
      unsigned int SH_ID;
      unsigned char* image;
    public:
      Shader(); 
      Shader(const std::string& vertex, const std::string& fragment);
      unsigned int GetShaderID();
      void ChangeUniformValue(Uni _type, void* _data, const char* field);
  };
}
