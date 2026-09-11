#pragma once
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Shaders.h"
namespace Modeling {
  enum ModelType{
    Cube = 0x010,
    Ball = 0x011,
    Triangle = 0x012
  };

  struct Material{};

  struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv_position;
    glm::vec3 normal;
  };

  class Model{
    private:
      unsigned int VBO, EBO, VAO;
      std::shared_ptr<std::vector<Vertex>> _vertices;
      std::shared_ptr<std::vector<unsigned int>> _indices;

      std::shared_ptr<Shaders::Shader> _shader;
    public:
      Shaders::Shader* GetShader();
    Model(const std::vector<Vertex>& _verts, const std::vector<unsigned int>& indices, const Shaders::Shader& shad);
    void RenderModel();
    ~Model();
  };
  Model Make_Model(const ModelType& _mod_type);
  Model Make_Model(const std::string& path_to_model);
} // namespace Modeling
