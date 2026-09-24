#ifndef GAMEOBJ
#define GAMEOBJ
#include "Transform.h"
#include <vector>
#include <string>
#include <memory>
namespace Game{
  class GameObject;

  class Component {
   public:
    virtual ~Component() = default;
    virtual void Update() {}
    virtual void Awake() {} 
    GameObject* owner = nullptr; 
    Component(GameObject* own) : owner(own) {}
  };

  class GameObject{
    private:
      std::vector<std::unique_ptr<Component>> _components;
      std::vector<std::unique_ptr<GameObject>> _children;
    public:
      std::string name = "";
      transform::Transform transform = {};
    
      template <class T, typename... args>
      void AddComponent(args&&... arguments){
        static_assert(std::is_base_of_v<Component, T>, "[GANGOD] The component does not inherit from class 'Component'");
        std::unique_ptr<T> comp = std::make_unique<T>(this, std::forward<args>(arguments)...);  
        _components.push_back(std::move(comp)); 
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
     bool TryComponent(T*& out){
       for(auto& comp : _components){
          if(T* cast = dynamic_cast<T*>(comp.get())){
            out = cast;
            return true;
           }
       }
       return false;
     };

     template <class T>
     T* GetComponent(){
       for(auto& comp : _components){
          if(T* cast = dynamic_cast<T*>(comp.get())){
            return cast;
            
           }
       }
        return nullptr; 
     };
     void Update(){
        for(auto& comp : _components){
          comp->Update();
        }
        for(auto& child : _children){
          child->Update();
        }
     }
  };
}
#endif
