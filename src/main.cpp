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
    Slime(Vec2 position, Vec2 velocity, Vec4 color) : position(position), velocity(velocity), color(color) {}
    Slime() {}
    // array<Vertex, 4> vertices()
    // {
    //     Vertex bot_left;
    //     bot_left.position = {position.x, position.y};
    //     bot_left.color = color;

    //     Vertex bot_right;
    //     bot_right.position = {position.x + size, position.y};
    //     bot_right.color = color;

    //     Vertex top_left;
    //     top_left.position = {position.x, position.y + size};
    //     top_left.color = color;

    //     Vertex top_right;
    //     top_right.position = {position.x + size, position.y + size};
    //     top_right.color = color;

    //     return {
    //         bot_left,
    //         bot_right,
    //         top_left,
    //         top_right};
    // }
};

const int num_slimes = 1000000;
// array<Slime, num_slimes> slimes;
Slime slimes[num_slimes];
uint32_t VAO, VBO, instanceVBO;
Vertex vertices[num_slimes * 4];
// uint32_t indices[num_slimes * 6];
uint32_t indices[6];

Vec2 slime_positions[num_slimes];

int WORK_GROUP_SIZE = 256;

int main()
{

    float size = 0.002f;
    display = new Display(800, 800);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < num_slimes; i++)
    {
        float x = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - -1.0f)));
        float y = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - -1.0f)));
        float vx = 0.005f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.01f - 0.005f)));
        float vy = 0.005f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.01f - 0.005f)));
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float a = 0.5f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (1.0f - 0.5f));
        slimes[i] = Slime({x, y}, {vx, vy}, {0.0f, g, 0.5f, 0.5f});
        slime_positions[i] = {x, y};
        // auto temp = slimes[i].vertices();
        // memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
        // indices[i * 6] = i * 4;
        // indices[i * 6 + 1] = i * 4 + 2;
        // indices[i * 6 + 2] = i * 4 + 3;
        // indices[i * 6 + 3] = i * 4 + 3;
        // indices[i * 6 + 4] = i * 4 + 1;
        // indices[i * 6 + 5] = i * 4;
    }

    // uint32_t instanceVBO;
    glCreateBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(slime_positions), &slime_positions[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(slimes), slimes, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // uint32_t VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // // uint32_t VBO;
    // glCreateBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * slimes.size() * 4, nullptr, GL_DYNAMIC_DRAW);

    // glEnableVertexArrayAttrib(VBO, 0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));

    // glEnableVertexArrayAttrib(VBO, 1);
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, color));

    // float quadVertices[] = {
    //     // positions     // colors
    //     -0.05f, 0.05f, 1.0f, 0.0f, 0.0f, 0.5f,
    //     0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.5f,
    //     -0.05f, -0.05f, 0.0f, 0.0f, 1.0f, 0.5f,

    //     -0.05f, 0.05f, 1.0f, 0.0f, 0.0f, 0.5f,
    //     0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.5f,
    //     0.05f, 0.05f, 0.0f, 1.0f, 1.0f, 0.5f};
    Slime slime;
    // float quadVertices[] = {
    //     // positions     // colors
    //     -slime.size, slime.size, 1.0f, 0.0f, 0.0f, 0.5f,
    //     slime.size, -slime.size, 0.0f, 1.0f, 0.0f, 0.5f,
    //     -slime.size, -slime.size, 0.0f, 0.0f, 1.0f, 0.5f,

    //     -slime.size, slime.size, 1.0f, 0.0f, 0.0f, 0.5f,
    //     slime.size, -slime.size, 0.0f, 1.0f, 0.0f, 0.5f,
    //     slime.size, slime.size, 0.0f, 1.0f, 1.0f, 0.5f};
    // float quadVertices[] = {
    //     // positions     // colors
    //     -slime.size, slime.size, 1.0f, 0.0f, 0.0f, 0.5f,
    //     slime.size, -slime.size, 1.0f, 0.0f, 0.0f, 0.5f,
    //     -slime.size, -slime.size, 1.0f, 0.0f, 0.0f, 0.5f,
    //     slime.size, slime.size, 1.0f, 0.0f, 0.0f, 0.5f};
    // float quadVertices[] = {
    //     // positions     // colors
    //     -slime.size, slime.size,
    //     slime.size, -slime.size,
    //     -slime.size, -slime.size,
    //     slime.size, slime.size};

    float quadVertices[] = {
        // positions     // colors
        -size, size,
        size, -size,
        -size, -size,
        size, size};

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 1;
    indices[5] = 3;

    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_DYNAMIC_DRAW);

    // // glEnableVertexArrayAttrib(VBO, 0);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)0);

    // // glEnableVertexArrayAttrib(VBO, 1);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)(2 * sizeof(float)));

    // glEnableVertexArrayAttrib(VBO, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);

    // glEnableVertexArrayAttrib(VBO, 1);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Slime), (const void *)offsetof(Slime, color));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);

    // glEnableVertexArrayAttrib(VBO, 2);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Slime), (const void *)offsetof(Slime, position));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

    // for (int i = 0; i < slimes.size(); i++)
    // {
    //     float x = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - -1.0f)));
    //     float y = -1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - -1.0f)));
    //     float vx = 0.005f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.01f - 0.005f)));
    //     float vy = 0.005f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.01f - 0.005f)));
    //     float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    //     float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    //     float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    //     float a = 0.5f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (1.0f - 0.5f));
    //     slimes[i] = Slime({x, y}, {vx, vy}, {r, g, b, 0.5f});
    //     auto temp = slimes[i].vertices();
    //     memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
    //     indices[i * 6] = i * 4;
    //     indices[i * 6 + 1] = i * 4 + 2;
    //     indices[i * 6 + 2] = i * 4 + 3;
    //     indices[i * 6 + 3] = i * 4 + 3;
    //     indices[i * 6 + 4] = i * 4 + 1;
    //     indices[i * 6 + 5] = i * 4;
    // }

    uint32_t IBO;
    glCreateBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glUseProgram(display->compute_program);

    int num_slimes_location = glGetUniformLocation(display->compute_program, "num_slimes");
    glUniform1ui(num_slimes_location, num_slimes);

    // uint32_t CS_SB;
    // glCreateBuffers(1, &CS_SB);
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, CS_SB);
    // glBufferData(GL_SHADER_STORAGE_BUFFER, 3 * sizeof(Vec4), nullptr, GL_DYNAMIC_DRAW);

    // GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // invalidate makes a ig difference when re-writting

    // Vec4 *coul;
    // coul = (Vec4 *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * sizeof(Vec4), bufMask);

    Vec2 v1;
    v1.x = 1.0f;
    v1.y = 0.0f;
    // v1.z = 0.0f;
    // v1.w = 0.0f;

    Vec2 v2;
    v2.x = 4.0f;
    v2.y = 0.0f;
    // v2.z = 0.0f;
    // v2.w = 0.0f;

    Vec2 v3;
    v3.x = 2.0f;
    v3.y = 0.0f;
    // v3.z = 1.0f;
    // v3.w = 0.0f;

    // Vec2 slimes[3] = {
    //     v1, v2, v3};

    // uint32_t CS_SB;
    // glCreateBuffers(1, &CS_SB);
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, CS_SB);
    // glBufferData(GL_SHADER_STORAGE_BUFFER, 3 * sizeof(Vec2), coul, GL_DYNAMIC_DRAW);

    // GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // invalidate makes a ig difference when re-writting
    // // coul = (Vec4 *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * sizeof(Vec4), bufMask);

    // uint32_t CS_SB;
    // glCreateBuffers(1, &CS_SB);
    // glBindBuffer(GL_SHADER_STORAGE_BUFFER, CS_SB);
    // glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(slimes), slimes, GL_DYNAMIC_DRAW);

    // GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // invalidate makes a ig difference when re-writting

    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, CS_SB);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, instanceVBO);
    // coul[0].x = 1.0f;
    // coul[0].y = 0.0f;
    // coul[0].z = 0.0f;
    // coul[0].w = 0.0f;

    // coul[1].x = 4.0f;
    // coul[1].y = 0.0f;
    // coul[1].z = 0.0f;
    // coul[1].w = 0.0f;

    // coul[2].x = 2.0f;
    // coul[2].y = 0.0f;
    // coul[2].z = 0.0f;
    // coul[2].w = 0.0f;

    // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    // std::cout << sizeof(slimes) << endl;
    // std::cout << "compute test" << endl;
    // // std::cout << slimes[0].x << " " << slimes[0].y << " " << endl;
    // // std::cout << slimes[1].x << " " << slimes[1].y << " " << endl;
    // // std::cout << slimes[2].x << " " << slimes[2].y << " " << endl;

    // std::cout << slimes[0].position.x << " " << slimes[0].position.y << " " << endl;
    // std::cout << slimes[1].position.x << " " << slimes[1].position.y << " " << endl;
    // std::cout << slimes[2].position.x << " " << slimes[2].position.y << " " << endl;

    // std::cout << "computing" << endl;
    // glDispatchCompute(3, 1, 1);
    // // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    // // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    // glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    // // coul = (Vec4 *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * sizeof(Vec4), bufMask);
    // // memcpy(0, coul, 3 * sizeof(Vec4));
    // // glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(slimes), slimes);
    // // Slime* slimes;
    // Slime *rslimes = (Slime *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
    // memcpy(slimes, rslimes, num_slimes * sizeof(slime));
    // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    // // memcpy(coul, , sizeof(coul));

    // // memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
    // // std::cout << slimes[0].x << " " << slimes[0].y << " " << endl;
    // // std::cout << slimes[1].x << " " << slimes[1].y << " " << endl;
    // // std::cout << slimes[2].x << " " << slimes[2].y << " " << endl;

    // std::cout << slimes[0].position.x << " " << slimes[0].position.y << " " << endl;
    // std::cout << slimes[1].position.x << " " << slimes[1].position.y << " " << endl;
    // std::cout << slimes[2].position.x << " " << slimes[2].position.y << " " << endl;

    // // std::cout << rslimes[0].position.x << " " << rslimes[0].position.y << " " << endl;
    // // std::cout << rslimes[1].position.x << " " << rslimes[1].position.y << " " << endl;
    // // std::cout << rslimes[2].position.x << " " << rslimes[2].position.y << " " << endl;

    // std::cout << "computing" << endl;
    // glDispatchCompute(3, 1, 1);
    // // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    // // glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    // glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
    // // coul = (Vec4 *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * sizeof(Vec4), bufMask);
    // // memcpy(0, coul, 3 * sizeof(Vec4));
    // // glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(slimes), slimes);
    // rslimes = (Slime *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
    // // memcpy(slimes, rslimes, sizeof(rslimes));
    // memcpy(slimes, rslimes, num_slimes * sizeof(slime));
    // // std::cout << rslimes[0].position.x << " " << rslimes[0].position.y << " " << endl;
    // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    // // memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
    // std::cout << slimes[0].position.x << " " << slimes[0].position.y << " " << endl;
    // std::cout << slimes[1].position.x << " " << slimes[1].position.y << " " << endl;
    // std::cout << slimes[2].position.x << " " << slimes[2].position.y << " " << endl;

    // // std::cout << rslimes[0].position.x << " " << rslimes[0].position.y << " " << endl;
    // // std::cout << rslimes[1].position.x << " " << rslimes[1].position.y << " " << endl;
    // // std::cout << rslimes[2].position.x << " " << rslimes[2].position.y << " " << endl;

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

    double previousTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(display->window))
    {
        display->processInput();

        double currentTime = glfwGetTime();
        frameCount++;
        // If a second has passed.
        if (currentTime - previousTime >= 1.0)
        {
            // Display the frame count here any way you want.
            // displayFPS(frameCount);
            std::cout << frameCount << endl;

            frameCount = 0;
            previousTime = currentTime;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // // Vertex vertices[slimes.size() * 4];
        // for (int i = 0; i < num_slimes; i++)
        // {
        // if (slimes[i].position.x <= -1.0f || slimes[i].position.x >= 1.0f)
        // {
        //     slimes[i].velocity.x = -1.0f * slimes[i].velocity.x;
        // }
        // if (slimes[i].position.y <= -1.0f || slimes[i].position.y >= 1.0f)
        // {
        //     slimes[i].velocity.y = -1.0f * slimes[i].velocity.y;
        // }
        //     slimes[i].position = {slimes[i].position.x + slimes[i].velocity.x, slimes[i].position.y + slimes[i].velocity.y};
        //     // auto temp = slimes[i].vertices();
        //     // memcpy(vertices + temp.size() * i, temp.data(), temp.size() * sizeof(Vertex));
        // }

        glUseProgram(display->compute_program);

        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(display->window, &xpos, &ypos);
        float mouseX = (float)(xpos - display->SCREEN_WIDTH / 2) / (display->SCREEN_WIDTH / 2);
        float mouseY = (float)-1 * (ypos - display->SCREEN_HEIGHT / 2) / (display->SCREEN_HEIGHT / 2);
        // cout << "Cursor Position at (" << mouseX << " : " << mouseY << endl;

        Vec2 mouse;
        mouse.x = mouseX;
        mouse.y = mouseY;

        int mouseX_location = glGetUniformLocation(display->compute_program, "mouseX");
        glUniform1f(mouseX_location, mouseX);
        int mouseY_location = glGetUniformLocation(display->compute_program, "mouseY");
        glUniform1f(mouseY_location, mouseY);

        // int mouse_location = glGetUniformLocation(display->compute_program, "mouse_location");
        // // glUniform1ui(num_slimes_location, num_slimes);
        // glUniform2fv(mouse_location, sizeof(mouse), reinterpret_cast<GLfloat *>(&mouse));

        glDispatchCompute(num_slimes / WORK_GROUP_SIZE + 1, 1, 1);
        glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
        // Slime *rslimes = (Slime *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
        // memcpy(slimes, rslimes, num_slimes * sizeof(Slime));
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glUseProgram(display->shader_program);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(slimes), &slimes[0], GL_DYNAMIC_DRAW);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(slimes), &slimes[0]);

        glBindVertexArray(VAO);
        // glDrawArraysInstanced(GL_TRIANGLES, 0, 6, num_slimes * 2);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, num_slimes);
        glBindVertexArray(0);

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
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // slimes.size() * 2 * 3
        // glDrawElements(GL_TRIANGLES, slimes.size() * 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(display->window);
        glfwPollEvents();
    }
}