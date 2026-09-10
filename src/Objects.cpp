#include "../headers/Objects.h"

Objects::Renderable::Renderable(){
  
}

Objects::Renderable::Renderable(Modeling::Model model) : _model(nullptr){
  _model = std::make_unique<Modeling::Model>(model);
}

void Objects::Renderable::Update(){
 _model->RenderModel(); 
}


Objects::ComponentManager::ComponentManager(){

}

Objects::Spaceable::Spaceable(){
  component_manager = {};
  _position = {0, 0, 0};
  _rotation = {0, 0, 0, 0};
}

void Objects::Spaceable::Update(){
 component_manager.UpdateAll(); 
}
