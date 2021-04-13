#shader compute
#version 460 core
// #extension GL_ARB_compute_shader : enable
// #extension GL_ARB_shader_storage_buffer_object : enable

// struct slime{
//     vec4 position;
//     vec4 velocity;
//     vec4 color;
// };

struct slime
{
    vec2 position;
    vec2 velocity;
    vec4 vcolor;
    // float size;
};

layout(std430, binding=0) buffer SlimeBuffer
{
   slime slimes[];
};

uniform uint num_slimes;
// uniform vec2 mouse_location;
uniform float mouseX;
uniform float mouseY;


layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;
void main()
{
    uint gid = gl_GlobalInvocationID.x;
    // uint gid = gl_WorkGroupID.x;

    if(gid <= num_slimes){
        slime sl = slimes[gid];

        if (sl.position.x <= -1.0f || sl.position.x >= 1.0f)
        {
            sl.velocity.x = -1.0f * sl.velocity.x;
        }
        if (sl.position.y <= -1.0f || sl.position.y >= 1.0f)
        {
            sl.velocity.y = -1.0f * sl.velocity.y;
        }
        // sl.position = sl.position + sl.velocity;
        float x_diff = mouseX - sl.position.x;
        float y_diff = mouseY - sl.position.y;
        float angle = atan(y_diff, x_diff);
        float c = sqrt(sl.velocity.x * sl.velocity.x + sl.velocity.y * sl.velocity.y);
        sl.position.x = sl.position.x + c * cos(angle) + sl.velocity.x + c * sin(angle) + sl.velocity.y;
        sl.position.y = sl.position.y + sl.velocity.y + mouseY * cos(angle);

        slimes[gid] = sl;
    }
};