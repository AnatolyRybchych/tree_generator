#include <iostream>

#include <window.hpp>
#include <gl.hpp>
#include <tree.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    program *prog;

    window window;
    window.create(800, 600, "window");

    std::vector<glm::vec2> vertices;

    vertices.push_back(glm::vec2(1, 1));
    vertices.push_back(glm::vec2(-1, -1));

    tree test;

    default_body_interpolator interpolator((value){
        .body_width = 0.2,
        .branches_spread = 0.2,
    });
    test.init(1, &interpolator);

    window.initWithGlContex([&](){
        shader frag(GL_FRAGMENT_SHADER, 
        R"shader(

            varying vec2 FragPos;

            void main(){
                gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )shader");
        shader vert(GL_VERTEX_SHADER, 
        R"shader(
            attribute vec4 VertPos;
            varying vec2 FragPos;

            void main() {
                gl_Position = VertPos;
                FragPos = VertPos.xy;
            }
        )shader");
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
