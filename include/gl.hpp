#pragma once

#include <string>
#include <vector>

#include <GLES2/gl2.h>


class shader{
private:
    GLuint _id;
public:
    shader(GLenum type, std::string source);
    GLuint get_id();
    bool is_compiled();
    std::string get_log();
    ~shader();
};


class program{
private:
    GLuint _id;
    shader& _frag;
    shader& _vert;
public:
    program(shader &fragment, shader &vertex);
    GLuint get_id();
    shader &get_vertex_shader();
    shader &get_fragment_shader();
    bool is_linked();
    std::string get_log();
};