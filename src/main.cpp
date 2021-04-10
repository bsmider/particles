#define GLFW_DLL

#include <display.h>
#include <iostream>
#include <array>

using namespace std;

Display *display;
void update();

struct Vec2
{
    float x, y;
};

struct Vec4
{
    float x, y, z, w;
};

struct Vertex
{
    Vec2 position;
    Vec4 color;
};

struct Slime
{
    Vec2 position;
    Vec2 velocity;
    Vec4 color;
    float size = 0.002f;
    Slime(Vec2 position, Vec2 velocity, Vec4 color) : position(position), velocity(velocity), color(color) {}
    Slime() {}
    array<Vertex, 4> vertices()
    {
        Vertex bot_left;
        bot_left.position = {position.x, position.y};
        bot_left.color = color;

        Vertex bot_right;
        bot_right.position = {position.x + size, position.y};
        bot_right.color = color;

        Vertex top_left;
        top_left.position = {position.x, position.y + size};
        top_left.color = color;

        Vertex top_right;
        top_right.position = {position.x + size, position.y + size};
        top_right.color = color;

        return {
            bot_left,
            bot_right,
            top_left,
            top_right};
    }
};

array<Slime, 7000> slimes;
uint32_t VBO;

int main()
{
    display = new Display(800, 800);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    uint32_t VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // uint32_t VBO;
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * slimes.size() * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexArrayAttrib(VBO, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));

    glEnableVertexArrayAttrib(VBO, 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, color));


    Vertex vertices[slimes.size() * 4];
    uint32_t indices[slimes.size() * 6];
    for (int i = 0; i < slimes.size(); i++)
    {
        float x = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - -1.0f)));
        float y = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - -1.0f)));
        float vx = 0.005f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.01f - 0.005f)));
        float vy = 0.005f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.01f - 0.005f)));
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float a = 0.5f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (1.0f - 0.5f));
        slimes[i] = Slime({x, y}, {vx, vy}, {r, g, b, 0.5f});
        auto temp = slimes[i].vertices();
        memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
        indices[i * 6] = i * 4;
        indices[i * 6 + 1] = i * 4 + 2;
        indices[i * 6 + 2] = i * 4 + 3;
        indices[i * 6 + 3] = i * 4 + 3;
        indices[i * 6 + 4] = i * 4 + 1;
        indices[i * 6 + 5] = i * 4;
    }

    uint32_t IBO;
    glCreateBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    update();

    glDeleteProgram(display->shader_program);
    glfwTerminate();
    return 0;
}

// loop
void update()
{
    float r = 0.0f;
    float change = 0.01f;
    bool dir = true;
    while (!glfwWindowShouldClose(display->window))
    {
        display->processInput();

        Vertex vertices[slimes.size() * 4];
        for (int i = 0; i < slimes.size(); i++)
        {
            if (slimes[i].position.x <= -1.0f || slimes[i].position.x >= 1.0f)
            {
                slimes[i].velocity.x = -1.0f * slimes[i].velocity.x;
            }
            if (slimes[i].position.y <= -1.0f || slimes[i].position.y >= 1.0f)
            {
                slimes[i].velocity.y = -1.0f * slimes[i].velocity.y;
            }
            slimes[i].position = {slimes[i].position.x + slimes[i].velocity.x, slimes[i].position.y + slimes[i].velocity.y};
            auto temp = slimes[i].vertices();
            memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
        }
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        // if (r >= 0.5f)
        // {
        //     change = -0.01f;
        // }
        // else if (r <= 0.0f)
        // {
        //     change = 0.01f;
        // }
        // r += change;
        // glClearColor(r, r, r, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // slimes.size() * 2 * 3
        glDrawElements(GL_TRIANGLES, slimes.size() * 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(display->window);
        glfwPollEvents();
    }
}