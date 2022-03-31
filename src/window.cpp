#include <window.hpp>

bool window::_isInit = window::init();


bool window::create(int width, int heigth, std::string title){
    destroy();
    _window = glfwCreateWindow(width, heigth, title.c_str(), NULL, NULL);
    if(_window){
        glfwSetWindowSizeCallback(_window, [](GLFWwindow *window,int width, int height){
            glfwMakeContextCurrent(window);
            glViewport(0,0, width, height);
        });


    }

    return _window;
}

void window::initWithGlContex(std::function<void()> handler){
    glfwMakeContextCurrent(_window);
    handler();
}

void window::destroy(){
    if(_window){
        glfwDestroyWindow(_window);
    }
}

void window::set_render_handler(std::function<void()> handler){
    _on_render = handler;
}

void window::set_update_handler(std::function<void()> handler){
    _on_update = handler;
}

void window::set_mouse_handler(void (*handler)(GLFWwindow *glfw_window, int m_button, int state, int)){
    glfwSetMouseButtonCallback(_window, handler);
}

window::window():_window(NULL)
{
}

void window::start_event_loop(){
    while (glfwWindowShouldClose(_window) == false)
    {
        glfwMakeContextCurrent(_window);
        glfwPollEvents();

        if(_on_update) _on_update();
        if(_on_render) _on_render();

        glfwSwapBuffers(_window);
    }
}

window::~window(){
    destroy();
}


bool window::init(){
    glfwWindowHint(GL_MAJOR_VERSION, 2);
    glfwWindowHint(GL_MINOR_VERSION, 0);

    if(glfwInit() == false){
        fprintf(stderr, "ERROR: %s\n", "glfw initialization failed");
        exit(1);
        return false;
    }
    return true;
}