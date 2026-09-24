#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../headers/Logger.h"
#include "../headers/WindowManager.h"
#include "../headers/Scene.h"
#include "../headers/Component.h"

int main(int argc, char** argv){
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  glfwInit();
  gwm::gWindow window(640, 640, "IAMGANGOD");

  if(window.HasWindow() == false){
    Logger::log_err("GLFW", "ERROR WHILE CREATING WINDOW, ERROR CODE: " + std::to_string(glGetError()));
    return -1; 
  }
  else{
    Logger::log("GLFW", "WINDOW WAS CREATED."); 
  }
  glewExperimental = GL_TRUE; // Safest for core profiles
  GLenum glewerr = glewInit();
  if (glewerr != GLEW_OK) {
     Logger::log_err("GLEW", "ERROR WHILE MAKING GLEW!");
     std::cout << (const char*)glewGetErrorString(glewerr) << " " << glewerr; 
     return -1;
  } 
  Game::Scene gamescene;
  gamescene.name = "Some";
  auto obj = gamescene.Create("obj");
  auto cam = gamescene.Create("obj2");

  obj->AddComponent<Game::Renderable>(Modeling::Make_Model(Modeling::ModelType::Cube));
  //obj->GetComponent<Game::Renderable>()->_model->GetShader()->ChangeTexture("/tex/Image.jpg");
  cam->AddComponent<Game::Camera>(Game::Camera::CameraView::Perspective, 90.0f, &window);
  Game::Camera::SetCurrent(cam->GetComponent<Game::Camera>());
  glEnable(GL_DEPTH_TEST);
  while(!window.MustClose()){
      
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    if(window.GetKey(gwm::S)){
       cam->transform.position.x -= 0.1f;
    }
    if(window.GetKeyDown(gwm::W)){
       cam->transform.position.x += 0.1f;
    }
    if(window.GetKeyDown(gwm::A)){
       cam->transform.position.z -= 0.1f;
    }
    if(window.GetKeyDown(gwm::D)){
       cam->transform.position.z += 0.1f;
    }
    if(window.GetKeyDown(gwm::Space)){
        cam->transform.position.y += 0.1f;
        }
     if(window.GetKeyDown(gwm::LeftControl)){
        cam->transform.position.y -= 0.1f;
        }
    
    gamescene.Update(); 
    window.Swap();
    glfwPollEvents();
  }
}
