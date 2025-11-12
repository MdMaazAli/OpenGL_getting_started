// importing stbi
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
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

    GLFWwindow* window = glfwCreateWindow(800,600,"gl6",NULL,NULL);
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
        // vertices         //colors             //texCords
        -0.5f,0.5f,0.0f,    1.0f,0.0f,0.0f,      0.0f,1.0f,     //topLeft
        0.5f,0.5f,0.0f,     0.0f,1.0f,0.0f,      1.0f,1.0f,     //topRight
        0.5f,-0.5f,0.0f,    0.0f,0.0f,1.0f,      1.0f,0.0f,     //bottomRight
        -0.5f,-0.5f,0.0f,   1.0f,1.0f,0.0f,      0.0f,0.0f      //bottomLeft
    };

    unsigned int indices[] = {
        0,1,3,
        1,3,2
    };

    Shader ourShader("src/vertexShader.glsl","src/fragShader.glsl");

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),&indices,GL_STATIC_DRAW);

    // loading and creating textures
    unsigned int TIO;
    glGenTextures(1,&TIO);
    glBindTexture(GL_TEXTURE_2D,TIO);
    // wrapping the texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    // filtering the texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // laoding and generating a texture
    int width,height,nrChannels;
    unsigned char* data = stbi_load("E:/gl6/textures/container.jpg",&width,&height,&nrChannels,0);
    if(data){
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;
        // gen and assign data to the texture
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        cout<<"failed to initialize a texture:"<<stbi_failure_reason()<<endl;
    }
    stbi_image_free(data);
    ourShader.use();
    ourShader.setInt("ourTex",0);

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // vertexAttrib texture
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.1f,0.2f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,TIO);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}