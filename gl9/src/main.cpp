#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <bits/stdc++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "stb_image.h"
using namespace std;

static float moveX = 0.0f;
static float moveY = 0.0f;
static float moveZ = -3.0f;
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}

float processMoveZ(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        moveZ+=0.001f;
        return moveZ;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        moveZ-=0.001f;
        return moveZ;
    }
    return moveZ;
}

float processMoveX(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        moveX-=0.001f;
        return moveX;
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        moveX+=0.001f;
        return moveX;
    }
    return moveX;
}

float processMoveY(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS){
        moveY-=0.001f;
        return moveY;
    }
    if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS){
        moveY+=0.001f;
        return moveY;
    }
    return moveY;
}

int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"gl9",NULL,NULL);
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

    Shader ourShader("src/vertShader.glsl","src/fragShader.glsl");

    float vertices[] = {
        // vertices             // color                // texCoord
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,       0.0f, 0.0f, // Face 1 (Red)
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,       1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,       0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,       0.0f, 0.0f, // Face 2 (Green)
        0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,       0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,       0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,       1.0f, 0.0f, // Face 3 (Blue)
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,       0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,       0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,       1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,       1.0f, 0.0f, // Face 4 (Yellow)
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,       1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,       0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,       1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,       0.0f, 1.0f, // Face 5 (Cyan)
        0.5f, -0.5f, -0.5f,     0.0f, 1.0f, 1.0f,       1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 1.0f,       1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 1.0f,       1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f,       0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,       0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,       0.0f, 1.0f, // Face 6 (Magenta)
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 1.0f,       1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f, 1.0f,       1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 1.0f,       0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,       0.0f, 1.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    unsigned int TIO;
    glGenTextures(1,&TIO);
    glBindTexture(GL_TEXTURE_2D,TIO);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    int width,height,nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("src/diamonddd.png",&width,&height,&nrChannels,0);
    if(data){
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        cout<<"failed to initialize an image texture"<<endl;
    }
    stbi_image_free(data);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    ourShader.use();
    ourShader.setInt("ourTex",0);

    vec3 cubePositions[] = {
        vec3( 0.0f,  0.0f,  0.0f), 
        vec3( 2.0f,  5.0f, -15.0f), 
        vec3(-1.5f, -2.2f, -2.5f),  
        vec3(-3.8f, -2.0f, -12.3f),  
        vec3( 2.4f, -0.4f, -3.5f),  
        vec3(-1.7f,  3.0f, -7.5f),  
        vec3( 1.3f, -2.0f, -2.5f),  
        vec3( 1.5f,  2.0f, -2.5f), 
        vec3( 1.5f,  0.2f, -1.5f), 
        vec3(-1.3f,  1.0f, -1.5f)  
    };

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.15f,0.15f,0.15f,1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // view and projection matrices
        mat4 view = mat4(1.0f);
        mat4 projection;
        view = translate(view,vec3(processMoveX(window),processMoveY(window),processMoveZ(window)));
        projection = perspective(radians(45.0f),800.0f/600.0f,0.1f,100.0f);
        ourShader.setMat4("view",view);
        ourShader.setMat4("projection",projection);
        
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,TIO);

        // rendering the cubes
        for(int i=1; i<=10; i++){
            mat4 model = mat4(1.0f);
            model = translate(model,cubePositions[i-1]);
            float angle = 20*i;
            if(i == 1 || i%3 == 1){
                model = rotate(model,(float)glfwGetTime()*radians(angle),vec3(1.0f, 0.3f, 0.5f));
            }
            ourShader.setMat4("model",model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}