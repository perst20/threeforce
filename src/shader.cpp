//
// Created by kimigaev on 10.04.2021.
//

#include <shader.h>

std::string read_source_file(const std::string &path) {
    std::ifstream file;
    std::string code;
    file.exceptions(std::ifstream::failbit);
    try {
        file.open(path);
        code.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();
    } catch (std::ifstream::failure &e) {
        throw std::ifstream::failure("error reading \"" + path + "\" or no such file");
    }
    return code;
}

GLuint compile_shader(GLuint type, const std::string &source) {
    GLuint shader;

    shader = glCreateShader(type);
    char const *c_source = source.c_str();
    glShaderSource(shader, 1, &c_source, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        throw std::runtime_error("error: shader compilation failed");
    }
    return shader;
}

GLuint create_program(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string
            vertexCode = read_source_file(vertexPath),
            fragmentCode = read_source_file(fragmentPath);
    GLuint
            vertexShader = compile_shader(GL_VERTEX_SHADER, vertexCode),
            fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragmentCode);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        throw std::runtime_error("error: program_ linking failed");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
