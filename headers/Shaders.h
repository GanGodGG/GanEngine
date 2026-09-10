#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#define DEFAULT_SHADER_PATH "/shaders/"
#define DEFAULT_VERT_SHADER "vert.gvr"
#define DEFAULT_FRAG_SHADER "frag.gfr"
namespace Shaders{
  class Shader{
    private:
      unsigned int SH_ID;
      unsigned char* image;
    public:
      Shader(); 
      Shader(const std::string& vertex, const std::string& fragment);
      unsigned int GetShaderID();
     
  };
}
