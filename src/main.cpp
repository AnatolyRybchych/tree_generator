#include <iostream>
#include <fstream>
#include <string.h>

#include <window.hpp>
#include <gl.hpp>
#include <tree.hpp>
#include <glm/ext/scalar_constants.hpp>

#define RANDF ((rand() % 10000) / 10000.0)

using namespace std;

class test_tree: public tree{
    public:
    test_tree(tree_branch root):tree(root){}

    std::vector<tree_child_branch_info> create_sub_branches(tree_parent_branch_info parent) const override{
        std::vector<tree_child_branch_info> res;

        int count_childs = 1;
        if(rand() % 5 == 0){
            count_childs += (int)(RANDF * 4.0);
        }

        float node_width = (1.0 - parent.length_to_branch) * 0.1;
        for (size_t i = 0; i < count_childs; i++) {
            float width = node_width * (RANDF * 0.8 + 0.2);

            if(i == count_childs - 1) width = node_width;
            node_width -= width;

            tree_child_branch_info child = {
                .end_width = width,
                .branch_length = 0.09,
                .angle = parent.angle + (float)((RANDF - 0.45f) * 0.6f),
            };

            res.push_back(child);
        }
        
        return res;
    }
};

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

void init_tree_frame(std::vector<glm::vec2> *lineVertices, data_tree<tree_branch> *root_branch, glm::vec2 pos){
    auto root = root_branch->get_value();
    for (size_t i = 0; i < root_branch->get_length(); i++){
        auto child_branch = (*root_branch)[i];
        auto child = child_branch.get_value();

        glm::vec2 dstpos(
            child.branch_length * sinf(glm::pi<float>() * child.angle),
            child.branch_length * cosf(glm::pi<float>() * child.angle)
        );

        dstpos += pos;

        lineVertices->push_back(pos);
        lineVertices->push_back(dstpos);

        init_tree_frame(lineVertices, &child_branch, dstpos);
    }
}

int main(int argc, char const *argv[])
{
    program *prog;

    window window;
    window.create(800, 600, "window");

    std::vector<glm::vec2> vertices;

    test_tree ttree((tree_branch){
        .width_from = 0.1,
        .width_to = 0.095,
        .branch_length = 0.05,
        .length_to_branch = 0,
        .angle = 0.0,
    });

    ttree.init();

    auto ttree_root = ttree.root;
    init_tree_frame(&vertices, &ttree_root, glm::vec2(0, -1));
    

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
