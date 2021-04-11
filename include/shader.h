#ifndef THREEFORCE_SHADER_H
#define THREEFORCE_SHADER_H

#include <string>
#include <fstream>
#include <exception>
#include <GL/glew.h>
#include <cstring>
#include <iostream>


std::string read_source_file(const std::string &path);

GLuint compile_shader(GLuint type, const std::string &source);

GLuint create_program(const std::string &vertexPath, const std::string &fragmentPath);


#endif //THREEFORCE_SHADER_H
