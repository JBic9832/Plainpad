#version 330 core

out vec4 FragColor;

uniform float time;

void main() {
	FragColor = vec4(0.0, 0.0, 0.0, (sin(time * 7.5) + 1) / 2);
}
