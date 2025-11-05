#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <list>
#include <tuple>
#include <optional>

#include "shader.h"
#include "game.h"
#include "ui.h"
/*
    UIManager should handle all aspects of the user interface, including rendering UI elements,
    managing user input for UI interactions, and updating UI states.
*/
class UIManager {

public:
    UIManager();
    UIManager(const int width, const int height);
    ~UIManager();

    void Render();
    void Update(GLFWwindow* window, float deltaTime, float xpos, float ypos, Game &game);
    void ProcessInput(GLFWwindow* window);
    void ProcessMouseInput(float xoffset, float yoffset);
    void Init();
    
    bool is_active();

    bool keys[1024];
private:
    void update_cursor(GLFWwindow* window);
    void set_cursor(GLFWwindow* window, int cursor);

    Shader shader;
    int screenWidth;
    int screenHeight;
    bool active = false;
    bool resize = false;
    bool dragging = false;
    
    UI* dragged_obj;
    UI* resized_obj;

    std::tuple<UI*, Point> resize_point;
    
};
#endif
