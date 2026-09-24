#ifndef SCENE
#define SCENE
#include "GameObject.h"
#include <unordered_map>
#include <cstdint>
#include <iostream>
namespace Game
{
  class Scene {
    private:
      std::unordered_map<uint32_t, GameObject*> objects = {};
      uint32_t current = 0;
    public:
      std::string name;
      GameObject* Create(const std::string& name){
        current ++;
        objects[current] = new GameObject();
        objects[current]->name = name;
        std::cout << objects[current]->name << std::endl;
        return objects[current];
      }

      GameObject* Get(uint32_t id){
        return objects[id];
      }

      template <typename T> GameObject* GetByComponent()
      {
        for(auto& obj : objects){
          T* w;
          if(obj.second->TryComponent<T>(w)){
            return obj.second; 
          }
        }
      } 

      void Delete(uint32_t id){
        objects[id]->~GameObject();
        objects.erase(current);
      }

      void Update(){
        for(auto& obj : objects){ 
          obj.second->Update();
        }
      }
  };
}
#endif
