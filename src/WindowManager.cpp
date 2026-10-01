#include <gEngine/WindowManager.h>
gwm::gWindow::gWindow(uint16_t __wid, uint16_t __hei, const std::string& _title) : _window(nullptr, glfwDestroyWindow) // Creating new window unique ptr with null pointer and destructor
{
  _width = __wid;
  _height = __hei;
  _window_title = _title; // Ik i can append them to construct step, but I won't

  if (_winCount == 0) {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    glfwInit();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* tempWind = glfwCreateWindow(__wid, __hei, _title.c_str(), NULL, _shared_context); // Just temp window for instance of _window

  if(!tempWind){
    return; // Uhh fuck
  }
  _window.reset(tempWind); // We got the window!
  glfwMakeContextCurrent(_window.get());
  if (_winCount == 0) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        Logger::log("GLEW", "GLEW LOAD FAIL.");
    }
    glEnable(GL_DEPTH_TEST);
    _shared_context = _window.get();     
  }

  glfwSetWindowUserPointer(_window.get(), this);
  glfwSetFramebufferSizeCallback(_window.get(), framebuffercallback); 
  _winCount++;
}

gwm::gWindow::~gWindow(){
  _window.reset(nullptr);
  _winCount--;
  if (_winCount == 0) {
    glfwTerminate();
    _shared_context = nullptr;
  }
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
void gwm::gWindow::Clean(float colR, float colG, float colB, float colA){
    glClearColor(colR, colG, colB, colA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void gwm::gWindow::Poll(){
 glfwPollEvents();
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
void gwm::gWindow::GetGlfwPos(float* x, float* y){
  double dx, dy;
  glfwGetCursorPos(_window.get(), &dx, &dy);
  *x = dx;
  *y = dy;
  
}
GLFWwindow* gwm::gWindow::get(){
  return _window.get();
}

void gwm::gWindow::framebuffercallback(GLFWwindow* window, int w, int h)
{
  auto* self = static_cast<gWindow*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, w, h);

    // если нужно сохранить размер для расчёта aspect ratio проекции
    self->_width = w;
    self->_height = h;
}
