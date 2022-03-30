#include <gl.hpp>

shader::shader(GLenum type, std::string source){
    _id = glCreateShader(type);
    const char *source_ptr = source.c_str();
    glShaderSource(_id, 1, &source_ptr, NULL);
    glCompileShader(_id);
}

GLuint shader::get_id(){
    return _id;
}

bool shader::is_compiled(){
    GLint status;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
    return status != 0;
}

std::string shader::get_log(){
    const size_t log_len = 1000;
    std::vector<char> log(log_len);
    glGetShaderInfoLog(_id, log_len, NULL, log.data());
    return log.data();
}

shader::~shader(){
    if(is_compiled()){
        glDeleteShader(_id);
    }
}




program::program(shader &fragment, shader &vertex):_frag(fragment), _vert(vertex){
    _id = glCreateProgram();
    glAttachShader(_id, _frag.get_id());
    glAttachShader(_id, _vert.get_id());
    glLinkProgram(_id);
}

GLuint program::get_id(){
    return _id;
}

shader &program::get_vertex_shader(){
    return _vert;
}

shader &program::get_fragment_shader(){
    return _frag;
}

bool program::is_linked(){
    GLint status;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    return status != 0;
}

std::string program::get_log(){
    const size_t log_len = 1000;
    std::vector<char> log(log_len);
    glGetProgramInfoLog(_id, log_len, NULL, log.data());
    return log.data();
}