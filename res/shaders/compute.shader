#shader compute
#version 430
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct Slime{
    vec2 position;
    vec2 velocity;
    vec4 color;
};

layout(std430, binding=0) buffer slimes{
   Slime s[];
};

uniform uint num_slimes;

layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;
void main(){
    uint gid = gl_GlobalInvocationID.x;

    if(gid <= maxParticles){
        Slime slime = p[gid];

        slime.position = position + velocity;
        p[gid] = part;
    }
};