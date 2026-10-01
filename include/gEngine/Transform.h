#ifndef TRANSFORMS
#define TRANSFORMS
#define GLM_ENABLE_EXPERIMENTAL   
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>       
#include <glm/gtx/quaternion.hpp>       
#include <glm/gtc/matrix_transform.hpp> 
#include <cmath>
namespace transform {
  struct Transform{
    glm::vec3 position{0.0f};
    glm::quat rotation{1.0f, 0.0f, 0.0f,0.0f};
    glm::vec3 scale{1.0f};

    glm::mat4 matrix(){
        return glm::translate(glm::mat4(1.0f), position * 1e-8f) // meters
             * glm::toMat4(rotation)
             * glm::scale(glm::mat4(1.0f), scale * 3.25e-7f);
    }

  };

  float inline Distance(glm::vec3 A, glm::vec3 B){
    return std::sqrt(std::pow(B.x - A.x, 2) + std::pow(B.y - A.y, 2) + std::pow(B.z - A.z, 2));
  }
}
#endif
