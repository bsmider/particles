#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display
{
public:
    const uint32_t SCREEN_WIDTH;
    const uint32_t SCREEN_HEIGHT;
    GLFWwindow *window;
    uint32_t shader_program;
    uint32_t compute_program;
    Display(const uint32_t SCREEN_WIDTH, const uint32_t SCREEN_HEIGHT)
        : SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT)
    {
        init();
    }
    void processInput();

private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    int init();
};