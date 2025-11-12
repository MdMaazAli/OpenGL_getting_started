#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;
uniform sampler2D ourTex;
void main(){
    FragColor = texture(ourTex,texCoord)*vec4(ourColor,1.0);
}