const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
    "}\0";

#include <iostream>
#include <bits/stdc++.h>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
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

    GLFWwindow* window = glfwCreateWindow(800,600,"GL2",NULL,NULL);
    if(window == NULL){
        cout<<"failed to initialize the window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"faild to initialize GLAD"<<endl;
        return -1;
    }

    // vertex data[]
    float vertices[] = {
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.0f,0.5f,0.0f
    };

    
    // creating a VAO
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    // creating a VBO
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    // binding the buffer to a specific type of buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // copying the vertex data to the newly created buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // createing a vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // attaching vertexShaderSource to vertexShader
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    // compiling vertexShader
    glCompileShader(vertexShader);

    // checking if the vertexShader was compiled or not
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED"<<endl;
    }
    
    // creating a fragmentShaderObject
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // attaching the fragmentShaderSource to fragmentShader
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    // compiling fragmentShader
    glCompileShader(fragmentShader);
    
    // checking if the fragmentShader was compiled or not
    int successFrag;
    char infoLogFrag[512];
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&successFrag);

    if(!successFrag){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLogFrag);
        cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED"<<endl;
    }
    
    // creating a shader program so that we can link vertexShader and fragmentShader together
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // attching vertexShader to shaderProgram
    glAttachShader(shaderProgram,vertexShader);
    // attching fragmentShader to shaderProgram
    glAttachShader(shaderProgram,fragmentShader);
    // linking them together
    glLinkProgram(shaderProgram);
    
    // checking if the shaderProgram was compiled or not
    int successProgram;
    char infoLogProgram[512];
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&successProgram);

    if(!successProgram){
        glGetProgramInfoLog(vertexShader,512,NULL,infoLogProgram);
        cout<<"ERROR::SHADER::PROGRAM::COMPILATION_FAILED"<<endl;
    }

    // linking vertex attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.5f,0.7f,0.4f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // using the shaderProgram
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
    
        // drawing a triangle
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}