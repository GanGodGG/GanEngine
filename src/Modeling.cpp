#include <gEngine/Modeling.h>
  
Modeling::Model Modeling::Make_Model(const Modeling::ModelType& _mod_type, glm::vec3 color)
{
  std::vector<Modeling::Vertex> verts; 
  std::vector<unsigned int> indices;
  switch(_mod_type){
    case Modeling::ModelType::Cube:{
      std::cout << "Making cube" << std::endl; 
        verts = {
          // back
          {{-0.25f,-0.25f,-0.25f}, color, {1.0f, 0.0f}}, // back left bottom (0)
          {{0.25f, -0.25f, -0.25f}, color, {0.0f,0.0f}},// back right bottom (1)
          {{0.25f, 0.25f, -0.25f}, color, {0.0f,1.0f}}, // back right top (2)
          {{-0.25f, 0.25f, -0.25f}, color, {1.0f,1.0f}}, // back left top (3)
          // front
          {{-0.25f,-0.25f,0.25f}, color, {0.0f,0.0f}}, // front left bottom (4)
          {{0.25f, -0.25f, 0.25f}, color, {0.0f,0.0f}},// front right bottom (5)
          {{0.25f, 0.25f, 0.25f}, color, {0,1.0f}}, // front right top (6)
          {{-0.25f, 0.25f, 0.25f}, color, {0.0f,0.0f}} // front left top (7)
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
    case Modeling::ModelType::Ball:{
          int stackCount = 64;
          int sectorCount = 64;
          float radius = 1.0f;
          for (uint32_t i = 0; i <= stackCount; ++i) {
            // stackAngle идёт от +90° (полюс) до -90° (полюс)
            float stackAngle = glm::pi<float>() / 2.0f - i * (glm::pi<float>() / stackCount);
            float xy = radius * std::cos(stackAngle); // радиус текущего "кольца"
            float z  = radius * std::sin(stackAngle);

            for (uint32_t j = 0; j <= sectorCount; ++j) {
                float sectorAngle = j * (2.0f * glm::pi<float>() / sectorCount);

                float x = xy * std::cos(sectorAngle);
                float y = xy * std::sin(sectorAngle);

                Vertex v;
                v.color = color;
                v.position = {x, y, z};
                v.normal = glm::normalize(glm::vec3(x, y, z)); // для сферы normal = направление от центра
                v.uv_position = {
                    (float)j / sectorCount,
                    (float)i / stackCount
                };
                verts.push_back(v);
            }
        }
 
        for (uint32_t i = 0; i < stackCount; ++i) {
            uint32_t k1 = i * (sectorCount + 1);
            uint32_t k2 = k1 + sectorCount + 1;

            for (uint32_t j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }
                if (i != (stackCount - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }
     
                                   }
  }
  
  Model _model(verts, indices, {});
 
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
