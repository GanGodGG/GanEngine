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

      static inline int sceneCount = 0;
      static inline Scene* current_scene = nullptr;
    public:
      std::string name;

      Scene(){
        if(sceneCount == 0){
          current_scene = this;
        }
        sceneCount++;
      }

      static Scene* GetCurrent(){
        return current_scene;
      }
      static void ChangeScene(Scene* scen){
        current_scene = scen;
      }
      GameObject* Create(const std::string& name){
        current ++;
        objects[current] = new GameObject();
        objects[current]->name = name; 
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
      template <typename T> std::shared_ptr<std::vector<std::shared_ptr<T>>> GetByComponentAll()
      {
        std::shared_ptr<std::vector<std::shared_ptr<T>>> cmps = std::make_shared<std::vector<std::shared_ptr<T>>>();
        for(auto& obj : objects){
          T* w;
          if(obj.second->TryComponent<T>(w)){
             std::shared_ptr<T> ptr(w);
             cmps->push_back(ptr); 
          }
        }
        return cmps;
      } 


      void Delete(uint32_t id){
        objects[id]->~GameObject();
        objects.erase(current);
      }

      void Update(float dt){
        for(auto& obj : objects){ 
          obj.second->Update(dt);
        }
      }
      void Wake(){
        for(auto& obj : objects){ 
          obj.second->Awake();
        }
      }
  };
}
#endif
