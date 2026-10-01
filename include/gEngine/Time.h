#ifndef GTIME
#define GTIME
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
namespace gtime{
  extern float _lastTime;
  void Poll();
  float GetDelta();
}
#endif
