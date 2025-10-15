#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
/*
    UIManager should handle all aspects of the user interface, including rendering UI elements,
    managing user input for UI interactions, and updating UI states.
*/
class UIManager {

public:
    UIManager(const int width, const int height);
    ~UIManager();

    void Render();
    void Update(float deltaTime);
private:
    Shader shader;
    int screenWidth;
    int screenHeight;
};
#endif