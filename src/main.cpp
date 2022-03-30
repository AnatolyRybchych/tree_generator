#include <iostream>

#include <window.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    window window;
    window.create(800, 600, "window");


    window.initWithGlContex([&](){

    });

    window.set_update_handler([&](){

    });

    window.set_render_handler([&](){

    });


    window.start_event_loop();
    cout<<"qwe\n"<<endl; 
    return 0;
}
