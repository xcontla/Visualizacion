#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;
out vec2 coordTex;
out vec3 vertpos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


// ruido

float hash(vec2 p) {
    return fract(cos(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    //f = f * f * (3.0 - 2.0 * f); // Smoothstep
    return mix(mix(hash(i), hash(i + vec2(1.0, 0.0)), f.x),
               mix(hash(i + vec2(0.0, 1.0)), hash(i + vec2(1.0, 1.0)), f.x), f.y);
}   


void main()
{
    coordTex = tex;

    vec3 pos = position;

    pos.y = noise(pos.xz);

    vertpos = (model * vec4(pos, 1.0)).xyz;

    gl_Position = projection * view * model * vec4(pos, 1.0);
}