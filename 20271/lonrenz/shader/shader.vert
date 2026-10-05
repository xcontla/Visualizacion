#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;
out vec2 coordTex;
out vec3 vertpos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    coordTex = tex;

    vec3 pos = position.xyz;
    //pos.y = exp(- (position.x*position.x) - (position.z * position.z));

    vertpos = (model * vec4(pos, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}