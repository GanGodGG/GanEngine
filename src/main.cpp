#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "../headers/Modeling.h"
#include "../headers/WindowManager.h"
#include "../headers/Objects.h"
int main(int argc, char** argv){
  glfwInit();
  std::cout << "penis" << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  gwm::gWindow window(640, 640, "IAMGANGOD");
  glewExperimental = GL_TRUE; // Safest for core profiles
  if (glewInit() != GLEW_OK) {
    std::cerr << "[GLEW] ERROR WHILE LOADING GLEW!" << std::endl; 
  }

  if(window.HasWindow() == false){
    std::cerr << "[GLFW] ERROR WHILE CREATING WINDOW" << glGetError() << std::endl; 
  }
  else{
    std::cout << "[GLFW] REPORT: WINDOW CREATION SUCCESSFUL!" << std::endl;
  } 
  Objects::Spaceable obj;
  std::cout << "end..." << std::endl;
  obj.component_manager.AddComponent<Objects::Renderable>(Modeling::Make_Model(Modeling::ModelType::Cube));
  while(!window.MustClose()){
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    obj._position.x += 1.0f;
    obj._position.y += 1.0f;
    obj.Update();
    window.Swap();
    glfwPollEvents();
  }
}
