#version 330 core
out vec4 FragColor;
in vec2 FragCoords;

uniform float uBallRadius; // Ball radius in pixels
uniform vec2 uResolution; // Screen resolution

void main() {
    float dist = length(FragCoords);

    if (dist > uBallRadius) {
        discard;
    }

    // Ball color
    FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White ball with smooth edges
}
