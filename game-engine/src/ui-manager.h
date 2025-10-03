#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*
    UIManager should handle all aspects of the user interface, including rendering UI elements,
    managing user input for UI interactions, and updating UI states.
*/
class UIManager {

public:
    UIManager();
    ~UIManager();

    void Render();
    void Update(float deltaTime);
private:
    // Add private members and methods as needed
};
#endif