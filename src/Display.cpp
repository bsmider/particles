#define GLFW_DLL

#include <Display.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Shader
{
    string source;
    uint32_t type;
    Shader(uint32_t type, string source) : type(type), source(source) {}
};

static void createShader(uint32_t shader_program, const string &filepath);
static Shader getShader(const string &filepath);
static uint32_t compileShader(uint32_t type, const string &source);

int Display::init()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physarum", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // load shaders
    shader_program = glCreateProgram();
    createShader(shader_program, "res/shaders/vertex.shader");
    createShader(shader_program, "res/shaders/fragment.shader");
    glLinkProgram(shader_program);
    glValidateProgram(shader_program);
    glUseProgram(shader_program);

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Display::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Display::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

static void createShader(uint32_t shader_program, const string &filepath)
{
    // uint32_t program = glCreateProgram();
    // uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    // uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // glAttachShader(program, vs);
    // glAttachShader(program, fs);
    // glLinkProgram(program);
    // glValidateProgram(program);

    // glDeleteShader(vs);
    // glDeleteShader(fs);

    // return program;
    Shader shader = getShader(filepath);
    uint32_t shader_id = compileShader(shader.type, shader.source);
    glAttachShader(shader_program, shader_id);
    glDeleteShader(shader_id);
}

static Shader getShader(const string &filepath)
{
    ifstream stream(filepath);

    string line;
    stringstream shader_source;
    uint32_t shader_type;
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
            {
                shader_type = GL_VERTEX_SHADER;
            }
            else if (line.find("fragment") != string::npos)
            {
                shader_type = GL_FRAGMENT_SHADER;
            }
            else if (line.find("compute") != string::npos)
            {
                shader_type = GL_COMPUTE_SHADER;
            }
        }
        else
        {
            shader_source << line << '\n';
        }
    }

    return Shader(shader_type, shader_source.str());
}

static uint32_t compileShader(uint32_t type, const string &source)
{
    uint32_t id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    // glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}