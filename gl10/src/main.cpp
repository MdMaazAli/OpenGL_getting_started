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
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}

// cameraPos,cameraFront and cameraUp
vec3 cameraPos = vec3(0.0f,0.0f,3.0f);
vec3 cameraFront = vec3(0.0f,0.0f,-1.0f);
vec3 cameraUp = vec3(0.0f,1.0f,0.0f);

// camera rotation
bool mouseFirst = true;
float camYaw = -90.0f;
float camPitch = 0.0f;
float lastX = 800.0f/2.0f;
float lastY = 600.0f/2.0f;
float fov = 45.0f;

void mouse_callback(GLFWwindow* window,double xPosIn,double yPosIn){
    float xPos = (float)xPosIn;
    float yPos = (float)yPosIn;

    // mouse first
    if(mouseFirst){
        xPos = lastX;
        yPos = lastY;
        mouseFirst = false;
    }

    // calculating offset
    float xOffset = xPos-lastX;
    float yOffset = lastY-yPos;
    lastX = xPos;
    lastY = yPos;

    // sensitivity
    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camPitch += yOffset;
    camYaw += xOffset;

    // removing camera flip
    if(camPitch > 89.0f){
        camPitch = 89.0f;
    }
    if(camPitch < -89.0f){
        camPitch = -89.0f;
    }

    vec3 direction;
    direction.x = cos(radians(camYaw))*cos(radians(camPitch));
    direction.y = sin(radians(camPitch));
    direction.z = sin(radians(camYaw))*cos(radians(camPitch));
    cameraFront = normalize(direction);
}

void scroll_callback(GLFWwindow* window,double xOffset,double yOffset){
    fov -= (float)yOffset;
    if(fov < 1.0f){
        fov  = 1.0f;
    }
    if(fov > 45.0f){
        fov = 45.0f;
    }
}

// Time.deltaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }

    // camera movement
    float cameraSpeed = 2.5*deltaTime;
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed*cameraFront;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed*cameraFront;
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= normalize(cross(cameraFront,cameraUp))*cameraSpeed;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += normalize(cross(cameraFront,cameraUp))*cameraSpeed;
    }
}

int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"gl10",NULL,NULL);
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

    Shader ourShader("src/vertexShader.glsl","src/fragShader.glsl");

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
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        cout<<"failed to initialize a texture"<<endl;
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
    // mouse callback
    glfwSetCursorPosCallback(window,mouse_callback);
    // capturing the mouse
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    // scroll callback
    glfwSetScrollCallback(window,scroll_callback);

    ourShader.use();
    ourShader.setInt("ourTex",0);

    vec3 cubePositions[] = {
        vec3( 5.0f,  0.0f,  0.0f),  // Right
        vec3( 3.5f,  0.0f,  3.5f),  // Back-right
        vec3( 0.0f,  0.0f,  5.0f),  // Back
        vec3(-3.5f,  0.0f,  3.5f),  // Back-left
        vec3(-5.0f,  0.0f,  0.0f),  // Left
        vec3(-3.5f,  0.0f, -3.5f),  // Front-left
        vec3( 0.0f,  0.0f, -5.0f),  // Front
        vec3( 3.5f,  0.0f, -3.5f),  // Front-right
        vec3( 0.0f,  4.0f,  0.0f),  // Above
        vec3( 0.0f, -4.0f,  0.0f)   // Below
    };

    // projection matrix
    mat4 projection;
    
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame = currentFrame;
        
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        projection = perspective(radians(fov),800.0f/600.0f,0.1f,100.0f);
        ourShader.setMat4("projection",projection);

        ourShader.use();
        // camera view matrix
        mat4 view  = mat4(1.0f);
        // lookAt matrix
        view = lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
        ourShader.setMat4("view",view);
        
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,TIO);
        
        for(int i=1; i<=10; i++){
            mat4 model = mat4(1.0f);
            model = translate(model,cubePositions[i-1]);
            float angle = 20*i;
            model = rotate(model,(float)glfwGetTime()*radians(angle),vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model",model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}