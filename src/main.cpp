#include <iostream>
#include <fstream>
#include <string.h>

#include <window.hpp>
#include <gl.hpp>
#include <tree.hpp>

using namespace std;

string read_all_file(string file){
    ifstream source(file);

    if(!source.is_open()){
        fprintf(stderr, "ERROR: %s \"%s\"\n", "cannot open file", file.c_str());
        return "";
    }

    source.seekg(0,ios::end);
    size_t file_size = source.tellg();
    source.seekg(0, ios::beg);

    string res(file_size, ' ');
    source.read(&res[0], file_size);

    return res;
}

int main(int argc, char const *argv[])
{
    program *prog;

    window window;
    window.create(800, 600, "window");

    std::vector<glm::vec2> vertices;

    window.initWithGlContex([&](){
        shader frag(GL_FRAGMENT_SHADER, read_all_file("frag.glsl"));
        shader vert(GL_VERTEX_SHADER, read_all_file("vert.glsl"));
        prog = new program(frag, vert);

        if(!prog->is_linked()){
            std::cout<<"shader program:"<<prog->get_log()<<endl;

            if(!prog->get_vertex_shader().is_compiled()){
                std::cout<<"vertex shader:"<<prog->get_vertex_shader().get_log()<<endl;
            }

            if(!prog->get_fragment_shader().is_compiled()){
                std::cout<<"fragment shader:"<<prog->get_fragment_shader().get_log()<<endl;
            }
        }

        glClearColor(0, 0, 0, 1);
    });

    window.set_update_handler([&](){

    });

    window.set_render_handler([&](){
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(prog->get_id());

        GLint vert_pos = glGetAttribLocation(prog->get_id(), "VertPos");
        glEnableVertexAttribArray(vert_pos);
        glVertexAttribPointer(vert_pos, 2, GL_FLOAT, false, 0, vertices.data());
        glDrawArrays(GL_LINES, 0, vertices.size());
    });


    window.start_event_loop();
    return 0;
}
