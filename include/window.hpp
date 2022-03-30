#pragma once

#include <iostream>
#include <stdlib.h>
#include <functional>

#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>

class window{
private:
    GLFWwindow *_window;
    std::function<void()> _on_render;
    std::function<void()> _on_update;
public:
    window();
    ~window();
    bool create(int width, int heigth, std::string title);
    void initWithGlContex(std::function<void()> handler);
    void destroy();
    void start_event_loop();
    void set_render_handler(std::function<void()> handler);
    void set_update_handler(std::function<void()> handler);


private:
    static bool _isInit;
    static bool init();
};