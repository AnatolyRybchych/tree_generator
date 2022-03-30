#include <iostream>

#include <window.hpp>
#include <tree.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    window window;
    window.create(800, 600, "window");

    window.initWithGlContex([&](){
        glClearColor(0, 0, 0, 1);
    });

    window.set_update_handler([&](){

    });

    window.set_render_handler([&](){
        glClear(GL_COLOR_BUFFER_BIT);


    });


    window.start_event_loop();
    cout<<"qwe\n"<<endl; 
    return 0;
}
