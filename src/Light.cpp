#include <gEngine/Light.h>

void Game::AmbientLight::Update(float dt){
  auto Rend = Scene::GetCurrent()->GetByComponentAll<Game::Renderable>();

  for(auto& re : *Rend){
    Shaders::Shader* shader = re->_model->GetShader();
    size_t uniId = shader->GetShaderID();
    glUseProgram(uniId);
    shader->ChangeUniformValue(Shaders::Uni::Vector3, (void*)&color, "global_LightColor");
    shader->ChangeUniformValue(Shaders::Uni::Float, (void*)&ambientStrength, "global_LightIntense");
  }
}
