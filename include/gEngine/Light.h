#ifndef LIGHTS
#define LIGHTS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <gEngine/GameObject.h>
#include <gEngine/Scene.h>
#include <gEngine/BasicComponents.h>
namespace Game{
  class Light : public Component
  {
    public:
      glm::vec3 color;
      virtual void Update(float dt) override;
      virtual void Awake() override;
  };

  class PointLight : public Light
  {
    public:
      glm::vec3 position;
      float radius;

      void Update(float dt) override;
  };

  class SpotLight : public PointLight{
    public:
      glm::vec3 direction;

      void Update(float dt);
  };

  class AmbientLight : public Light 
  {
    public:
      float ambientStrength;

      void Update(float dt) override;
  };
}
#endif
