#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texColor;
uniform sampler2D ourTex;
void main(){
    FragColor = texture(ourTex,texColor);
}