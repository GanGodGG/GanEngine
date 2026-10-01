#include <gEngine/Time.h>

float gtime::_lastTime = 0;
float _currentTime = 0;
void gtime::Poll(){
  gtime::_lastTime = _currentTime;
  _currentTime = glfwGetTime();
}

float gtime::GetDelta(){
  return _currentTime - gtime::_lastTime;
}
