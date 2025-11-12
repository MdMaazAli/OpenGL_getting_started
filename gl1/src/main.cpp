#include <iostream>
#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

// 5
void framebuffer_size_callback(GLFWwindow* windown,int height,int width){
    glViewport(0,0,width,height);
}

// 8
void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

int main(){
    
    // 1
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // 2
    GLFWwindow* window = glfwCreateWindow(800,600,"gl1",NULL,NULL);
    if(window == NULL){
        cout<<"failed to create a window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"failed to initialize glad"<<endl;
        return -1;
    }

    // 4
    glViewport(0,0,800,600);

    // 6
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    // 7
    while(!glfwWindowShouldClose(window)){
        // 8.1
        processInput(window);
        // final
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 6.1
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}