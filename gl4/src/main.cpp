const char* vertexShaderSource = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform vec3 dynPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos+dynPos,1.0f);\n"
    "}\0";

const char* fragShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 dynColor;\n"
    "void main(){\n"
    "   FragColor = dynColor;\n"
    "}\0";

#include <iostream>
#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}

int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"gl4",NULL,NULL);
    if(window == NULL){
        cout<<"failed to initialize a window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"failed to initialize GLAD"<<endl;
        return -1;
    }

    float vertices[] = {
        0.0f,0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
    };

    int indices[] ={
        0,1,2
    };

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader,1,&fragShaderSource,NULL);
    glCompileShader(fragShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILLED"<<infoLog<<endl;
    }

    glGetShaderiv(fragShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragShader,512,NULL,infoLog);
        cout<<"ERROR::SHADER::FRAGMENT::CCOMPILATION_FIALED"<<infoLog<<endl;
    }

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        cout<<"ERROE:;:SHADER::PROGRAM::LINKING_FAILED"<<infoLog<<endl;
    }

    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.1f,0.2f,0.4f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        int timeValue = glfwGetTime();
        float move = sin(timeValue);
        float intensityR = (sin(timeValue)/2.0f)+0.5f;
        float intensityG = (sin(timeValue)/2.0f)+0.2f;
        int vertexPosLocation = glGetUniformLocation(shaderProgram,"dynPos");
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"dynColor");

        glUniform3f(vertexPosLocation,move,0.0f,0.0f);
        glUniform4f(vertexColorLocation,intensityR,intensityG,0.0f,1.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}