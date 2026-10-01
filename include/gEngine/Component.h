#ifndef COMP
#define COMP
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>       
#include <glm/gtc/matrix_transform.hpp> 

#include "Modeling.h"
#include "WindowManager.h"
namespace Game{ 
    class GameObject;  

    class Component {
       public:
        virtual ~Component() = default;
        virtual void Update(float dt) {}
        virtual void Awake() {} 
        GameObject* owner = nullptr; 
        Component(GameObject* own) : owner(own) {}
      };
}
#endif
