#include "../headers/Objects.h"

Objects::Renderable::Renderable(){
  
}

Objects::Renderable::Renderable(Modeling::Model model) : _model(nullptr){
  _model = std::make_unique<Modeling::Model>(model);
}

void Objects::Renderable::Update(){
  glUseProgram(_model->GetShader()->GetShaderID());
  _model->GetShader()->ChangeUniformValue(Shaders::Uni::Matrix4, &Interface->_parent->_model, "model");
  _model->RenderModel();

}
Objects::Spaceable::Spaceable() : component_manager(nullptr){
  component_manager = std::make_unique<Objects::ComponentManager>(this);
  _position = {0, 0, 0};
  _rotation = {0, 0, 0, 0};
}

void Objects::Spaceable::Update(){
  _model = glm::mat4(1.0f);
  _model = glm::translate(_model, _position); 
  _model = _model * glm::toMat4(_rotation); 
  _model = glm::scale(_model, _scale); 
  component_manager->UpdateAll(); 
}

