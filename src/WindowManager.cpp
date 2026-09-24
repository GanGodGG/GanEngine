#include "../headers/WindowManager.h"
gwm::gWindow::gWindow(uint16_t __wid, uint16_t __hei, const std::string& _title) : _window(nullptr, glfwDestroyWindow) // Creating new window unique ptr with null pointer and destructor
{
  _width = __wid;
  _height = __hei;
  _window_title = _title; // Ik i can append them to construct step, but I won't
  GLFWwindow* tempWind = glfwCreateWindow(__wid, __hei, _title.c_str(), NULL, NULL); // Just temp window for instance of _window
  if(!tempWind){
    return; // Uhh fuck
  }

  _window.reset(tempWind); // We got the window!
  glfwMakeContextCurrent(_window.get());
}

gwm::gWindow::gWindow(int16_t __wid, uint16_t __hei, const std::string& _title, GLFWmonitor* _monitor, GLFWwindow* _shared_window) : _window(nullptr, glfwDestroyWindow), _width(__wid), _height(__hei), _window_title(_title)
{
  GLFWwindow* tempWind = glfwCreateWindow(__wid, __hei, _title.c_str(), _monitor, _shared_window);
  if(!tempWind){
    return; // FUCK!!
  }

  _window.reset(tempWind); //...
  glfwMakeContextCurrent(_window.get());
}
 
bool gwm::gWindow::HasWindow(){
  return _window.get() != nullptr;
}

bool gwm::gWindow::MustClose(){
  return glfwWindowShouldClose(_window.get());
}

void gwm::gWindow::Swap(){
  glfwSwapBuffers(_window.get());
}

float gwm::gWindow::GetAspect(){
  return (float)_width / _height;
}

bool gwm::gWindow::GetKeyUp(const keys& key){
  return glfwGetKey(_window.get(), key) == GLFW_RELEASE; 
}
bool gwm::gWindow::GetKeyDown(const keys& key){
  return glfwGetKey(_window.get(), key) == GLFW_PRESS; 
}
bool gwm::gWindow::GetKey(const keys& key){
  return glfwGetKey(_window.get(), key) == GLFW_PRESS; 
}
