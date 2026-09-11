#pragma once
#include <cstdint>
#include <concepts>
#include <type_traits>

#include <memory>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include <glm/fwd.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Modeling.h"
// i lov tee

// I have plan: goto goto goto goto "goto" 
// And 
// Now: I'll make basic rendering (as rendering objects and shaders)
// Then: I'll make camera object
// Then 2: Ill goto: sleep
namespace Objects
{
  class ComponentManager;
  class Object 
  {
    private:
    uint32_t _id; // 2 ^ 32 = idk
    public:
    uint32_t GetId();

  };
  class Component : virtual public Object {
    protected:
      ComponentManager* Interface;
    public:
      void ChangeComponentInterface(ComponentManager* _interface){
        Interface = _interface;
      }
      virtual void Update() = 0;
      virtual ~Component() = default;
  };
  class Spaceable : public Object {
    public:
      glm::mat4x4 _model; 
      glm::quat _rotation; 
      glm::vec3 _scale;
      glm::vec3 _position;
      std::unique_ptr<ComponentManager> component_manager;
      std::shared_ptr<Spaceable> parent;
      void Update(); 
      void Rotate(glm::vec3 rotation);
      Spaceable();
     
  };

  class ComponentManager {
    private:
     std::vector<std::unique_ptr<Component>> _components;
    
    public:
     ComponentManager(Spaceable* spaceable) : _parent(nullptr){
        _parent.reset(spaceable);  
     }
 std::unique_ptr<Spaceable> _parent;
    void UpdateAll(){
       for(auto& i : _components){
          i->Update();
       }
     }
     template <class T, typename... args>
     void AddComponent(args&&... arguments){
       static_assert(std::is_base_of_v<Component, T>, "[GANGOD] The component does not inherit from class 'Component'");
        std::unique_ptr<T> comp = std::make_unique<T>(std::forward<args>(arguments)...);
        dynamic_cast<Component>(comp).ChangeComponentInterface(this);
        _components.push_back(comp);
        
     }
     template <class T>
     void RemoveComponent(){
       for(size_t i = 0; i < _components.size(); i++){
          if(dynamic_cast<T>(_components.at(i).get())){
            _components.erase(_components.begin() + i);
            break;
          }
       }
     }
     template <class T>
     bool TryComponent(T& out){
        for(size_t i = 0; i < _components.size(); i++){
          if(dynamic_cast<T>(_components.at(i).get())){
            out = _components.at(i);
            return true;
          }
       }
     };
  };

  class Renderable : public Component {
    private:
      std::unique_ptr<Modeling::Model> _model;
    public:
      Renderable();
      Renderable(Modeling::Model model);
      Renderable(Modeling::ModelType _type);
       
      void Update() override;
  };
}
