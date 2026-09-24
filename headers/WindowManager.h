#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
namespace gwm {
  enum keys{
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    Space = GLFW_KEY_SPACE,
    Escape = GLFW_KEY_ESCAPE,
    LeftControl = GLFW_KEY_LEFT_CONTROL
  };

  class gWindow {
    private:
      uint16_t _width, _height;
      std::string _window_title;
      std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window; 
    public:
      gWindow(uint16_t __wid, uint16_t __hei, const std::string& _title) ;
      gWindow(int16_t __wid, uint16_t __hei, const std::string& _title, GLFWmonitor* _monitor, GLFWwindow* _shared_window);
       
      float GetAspect();
      bool HasWindow();
      bool MustClose();
      void Swap();

      bool GetKeyDown(const keys& key);
      bool GetKeyUp(const keys& key);
      bool GetKey(const keys& key);
  };
} // namespace Gangod Window Manager
