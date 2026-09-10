#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
namespace gwm {
  class gWindow {
    private:
      uint16_t _width, _height;
      std::string _window_title;
      std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
    public:
      gWindow(uint16_t __wid, uint16_t __hei, const std::string& _title) ;
      gWindow(int16_t __wid, uint16_t __hei, const std::string& _title, GLFWmonitor* _monitor, GLFWwindow* _shared_window);
     

      bool HasWindow();
      bool MustClose();
      void Swap();
  };
} // namespace Gangod Window Manager
