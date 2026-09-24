#include "../headers/Modeling.h"
  
Modeling::Model Modeling::Make_Model(const Modeling::ModelType& _mod_type)
{
  std::vector<Modeling::Vertex> verts; 
  std::vector<unsigned int> indices;
  switch(_mod_type){
    case Modeling::ModelType::Cube:
      std::cout << "Making cube" << std::endl;
        glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);      
        verts = {
          // back
          {{-0.25f,-0.25f,-0.25f}, white, {1.0f, 0.0f}}, // back left bottom (0)
          {{0.25f, -0.25f, -0.25f}, white, {0.0f,0.0f}},// back right bottom (1)
          {{0.25f, 0.25f, -0.25f}, white, {0.0f,1.0f}}, // back right top (2)
          {{-0.25f, 0.25f, -0.25f}, white, {1.0f,1.0f}}, // back left top (3)
          // front
          {{-0.25f,-0.25f,0.25f}, white, {0.0f,0.0f}}, // front left bottom (4)
          {{0.25f, -0.25f, 0.25f}, white, {0.0f,0.0f}},// front right bottom (5)
          {{0.25f, 0.25f, 0.25f}, white, {0,1.0f}}, // front right top (6)
          {{-0.25f, 0.25f, 0.25f}, white, {0.0f,0.0f}} // front left top (7)
         };
        indices = {
          4, 5, 6, // front right-side triangle
          6, 7, 4,  // front left-side triange

          4, 0, 7,
          7, 3, 0,

          0, 1, 3,
          3, 2, 1,

          1, 5, 2,
          2, 6, 5,

          5, 1, 0,
          0, 4, 5,

          6, 2, 3,
          3, 7, 6
        };
      break;
  }
  std::cout << "Made cube..." << std::endl;
  Model _model(verts, indices, {});
  std::cout << "Return model... " << std::endl;
  return _model;
}

 
Modeling::Model::Model(const std::vector<Modeling::Vertex>& _verts, const std::vector<unsigned int>& indices, const Shaders::Shader& shad) : _vertices(nullptr), _indices(nullptr), _shader(nullptr)
{
  _vertices = std::make_shared<std::vector<Modeling::Vertex>>(_verts);
  _indices = std::make_shared<std::vector<unsigned int>>(indices);
  _shader = std::make_shared<Shaders::Shader>();
  glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices->size() * sizeof(Vertex), _vertices->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Modeling::Vertex, position))); // position values for gpu
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv_position)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices->size()*sizeof(unsigned int), _indices->data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
Modeling::Model::Model(const Modeling::Model& _cpy){
  VBO = _cpy.VBO;
  VAO = _cpy.VAO;
  EBO = _cpy.EBO;

  _vertices = _cpy._vertices;
  _indices = _cpy._indices;
  _shader = _cpy._shader;

  glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices->size() * sizeof(Vertex), _vertices->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Modeling::Vertex, position))); // position values for gpu
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv_position)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices->size()*sizeof(unsigned int), _indices->data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}


void Modeling::Model::RenderModel(){
  _shader->Render();
  glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _indices->size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

Shaders::Shader* Modeling::Model::GetShader(){
  return _shader.get();
}

Modeling::Model::~Model(){
  std::cout << "Called destructor" << std::endl;
}
