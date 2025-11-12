const char* vertexShaderSource = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
    "}\0";

const char* fragShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;"
    "void main(){\n"
    "   FragColor = ourColor;\n"
    "}\n";

const char* vertexShaderSource1 = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;"
    "void main(){\n"
    "   gl_Position = vec4(aPos,1.0);\n"
    "   vertexColor = vec4(1.0f,1.0f,1.0f,1.0f);\n"
    "}\0";

const char* fragShaderSource1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;\n"
    "void main(){\n"
    "   FragColor = vertexColor;\n"
    "}\n";

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

    GLFWwindow* window = glfwCreateWindow(800,600,"GL3",NULL,NULL);
    if(window == NULL){
        cout<<"failed to initialize a window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cout<<"failed to initialize GLAD"<<endl;
        return -1;
    }

    float vertices[] = {
        0,0,0,
        -0.5f,0.4f,0,
        -0.5f,0.8f,0,
        -0.7f,0.8f,0,
        -0.7f,0.4f,0,
        -0.7f,-0.8f,0,
        -0.5f,-0.8f,0
    };
    
    unsigned int indices[] = {
        0,1,2,
        1,2,3,
        1,3,4,
        1,4,5,
        1,5,6
    };
    
    float vertices1[] = {
        0,0,0,
        0.5f,0.4f,0,
        0.5f,0.8f,0,
        0.7f,0.8f,0,
        0.7f,0.4f,0,
        0.7f,-0.8f,0,
        0.5f,-0.8f,0
    };
    
    unsigned int indices1[] = {
        0,1,2,
        1,2,3,
        1,3,4,
        1,4,5,
        1,5,6
    };

    unsigned int VAO1;
    glGenVertexArrays(1,&VAO1);
    glBindVertexArray(VAO1);

    // right side
    unsigned int VBO1;
    glGenBuffers(1,&VBO1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO1);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),&vertices1,GL_STATIC_DRAW);
    
    // right side
    unsigned int EBO1;
    glGenBuffers(1,&EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices1),&indices1,GL_STATIC_DRAW);

    // right side
    unsigned int vertexShader1;
    vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader1,1,&vertexShaderSource1,NULL);
    glCompileShader(vertexShader1);

    // right side
    unsigned int fragShader1;
    fragShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader1,1,&fragShaderSource1,NULL);
    glCompileShader(fragShader1);
    
    // right side
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1,vertexShader1);
    glAttachShader(shaderProgram1,fragShader1);
    glLinkProgram(shaderProgram1);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

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
    
    int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.1f,0.2f,0.3f,1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue)/2.0)+0.5;
        
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,15,GL_UNSIGNED_INT,0);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES,15,GL_UNSIGNED_INT,0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}