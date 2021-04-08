#define GLFW_DLL

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include <display.h>
#include <iostream>

using namespace std;

Display *display;
void update();

int main()
{
    display = new Display(1920, 1080);
    update();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void update() {
    float r = 0.3f;
    float change = 0.01f;
    bool dir = true;
    // while (!glfwWindowShouldClose(window))
    while (!glfwWindowShouldClose(display->window))
    {
        // input
        // -----
        display->processInput();

        // render
        // ------
        if (r >= 1.0f) {
            change = -0.01f;
        } else if (r <= 0.3f) {
            change = 0.01f;
        }
        r += change;
        glClearColor(r, 0.3f, 0.3f, 1.0f);
        // glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(display->window);
        glfwPollEvents();
    }
}