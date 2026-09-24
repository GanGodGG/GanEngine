#ifndef COMP
#define COMP
#include "Modeling.h"
#include "GameObject.h"
#include "WindowManager.h"
namespace Game{ 
  class Camera : public Component{
    private:
      static inline Camera* _current = nullptr;
    public:
      gwm::gWindow* window;

      glm::vec3 up = {0.0f, 1.0f, 0.0f};
      glm::vec3 fow = {1.0f, 0.0f, 0.0f};

      float fov = 90.0f;
      float far_max = 100.0f;
      float far_min = .1f;
      enum CameraView{
        Perspective,
      Ortho
      };
      static void SetCurrent(Camera* cam) { _current = cam; }
      static Camera* current() { 
          return _current; 
      }
    Camera(GameObject* _cm, const CameraView& _CamView, const float& fv, gwm::gWindow* wind) : Component(_cm), cam_view(_CamView), fov(fv), window(wind) {};
    void Update() override {};
    glm::mat4 GetView() {return glm::lookAt(owner->transform.position, owner->transform.position + fow, up);}
    glm::mat4 GetProjection() { return glm::perspective(fov, window->GetAspect(), far_min, far_max); }
    private:
      CameraView cam_view;
  }; 

   class Renderable : public Component {  
    public:
       std::shared_ptr<Modeling::Model> _model;
        Renderable(GameObject* own, Modeling::Model _inmodel) : Component(own), _model(nullptr)
     {
       _model = std::make_shared<Modeling::Model>(_inmodel);
     }
      void Update() override{
        glUseProgram(_model->GetShader()->GetShaderID());
        auto mat = owner->transform.matrix();
        _model->GetShader()->ChangeUniformValue(Shaders::Uni::Matrix4, (void*)&mat, "model"); 
        glm::mat4 proj = Camera::current()->GetProjection();
        glm::mat4 view = Camera::current()->GetView();
        _model->GetShader()->ChangeUniformValue(Shaders::Uni::Matrix4, (void*)&proj, "projection");
        _model->GetShader()->ChangeUniformValue(Shaders::Uni::Matrix4, (void*)&view, "view");
        _model->RenderModel();
      }
  };
}
#endif
