#include "../headers/Shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
Shaders::Shader::Shader(){
  std::string Code_vert;
  std::string Code_frag;
  
  std::ifstream Stream_vert;
  std::ifstream Stream_frag;
  std::cout << "Tryna open path" << (std::filesystem::path(SOURCE_DIRECTORY DEFAULT_SHADER_PATH) / std::filesystem::path(DEFAULT_VERT_SHADER)) << std::endl;
	Stream_vert.open(std::filesystem::path(SOURCE_DIRECTORY DEFAULT_SHADER_PATH) / std::filesystem::path(DEFAULT_VERT_SHADER));
	Stream_frag.open(std::filesystem::path(SOURCE_DIRECTORY DEFAULT_SHADER_PATH) / std::filesystem::path(DEFAULT_FRAG_SHADER));
  std::cout << "opened path..." << std::endl;
  std::stringstream SS_vert, SS_frag;

	SS_vert << Stream_vert.rdbuf();
	SS_frag << Stream_frag.rdbuf();
  std::cout << SS_vert.str() << std::endl;
	Stream_vert.close();
	Stream_frag.close();

	Code_vert = SS_vert.str();
	Code_frag = SS_frag.str();

	const char* Clean_vert = Code_vert.c_str();
	const char* Clean_frag = Code_frag.c_str();

	unsigned int vert_Shader = glCreateShader(GL_VERTEX_SHADER);
	int sucess;
	char info[512];
	glShaderSource(vert_Shader, 1, &Clean_vert, NULL);
	glCompileShader(vert_Shader);

	glGetShaderiv(vert_Shader, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {
		glGetShaderInfoLog(vert_Shader, 512, NULL, info);
    std::cerr << "CLOUDN'T COMPILE!, love, new GSI! (VERTEX) " << info << std::endl;
	}
	unsigned int frag_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_Shader, 1, &Clean_frag, NULL);
	glCompileShader(frag_Shader);

	glGetShaderiv(frag_Shader, GL_COMPILE_STATUS, &sucess);

	if (!sucess) {
		glGetShaderInfoLog(frag_Shader, 512, NULL, info);
    std::cerr << "CLOUDN'T COMPILE!, love, new GSI! (FRAGMENT) " << info << std::endl;
	}
  std::cout << "Creating progIV" << std::endl;
	SH_ID = glCreateProgram();
	glAttachShader(SH_ID, vert_Shader);
	glAttachShader(SH_ID, frag_Shader);
	glLinkProgram(SH_ID);

	glGetProgramiv(SH_ID, GL_LINK_STATUS, &sucess);
	if (!sucess) {
		glGetProgramInfoLog(SH_ID, 512, NULL, info);
    std::cerr << "CLOUDN'T COMPILE!, love, new GSI!" << info << std::endl;
	}

	glDeleteShader(vert_Shader);
	glDeleteShader(frag_Shader);
  std::cout << "Compiled shaders!" << std::endl;
  // there goes texture path, but no.
}

unsigned int Shaders::Shader::GetShaderID(){
  return SH_ID;
}

void Shaders::Shader::ChangeUniformValue(Shaders::Uni _type, void* value, const char* field){
  int uni = glGetUniformLocation(SH_ID, field);

  switch (_type){
    case Shaders::Uni::Float:
      glUniform1f(uni, *(float*)value);
      break;
    case Shaders::Uni::Vector2:
      glUniform2fv(uni, 1, &((glm::vec2*)value)->x); // pointer to first value of array in glm vec2
      break;
    case Shaders::Uni::Vector3:
      glUniform3fv(uni, 1, &((glm::vec3*)value)->x);
      break;

    case Shaders::Uni::Matrix3:{
      glm::mat3 mat3 = *(glm::mat3*)value;
      glUniformMatrix3fv(uni, 1, GL_FALSE, &mat3[0][0]);
      break;
                               }
    case Shaders::Uni::Matrix4:
      glm::mat4 mat4 = *(glm::mat4*)value;
      glUniformMatrix3fv(uni, 1, GL_FALSE, &mat4[0][0]);
      break;
  }
}
