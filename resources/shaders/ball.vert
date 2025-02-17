#version 330 core
layout (location = 0) in vec3 aPos;
out vec2 FragCoords;
uniform mat4 transform;
void main() {
    FragCoords = aPos.xy;
    gl_Position = transform * vec4(aPos, 1.0);
}
