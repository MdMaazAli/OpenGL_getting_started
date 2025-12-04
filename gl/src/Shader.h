#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

class Shader{
    private:
        unsigned int ID;
    
    public:
        Shader(const char* vertexShaderPath,const char* fragShaderPath){
            ifstream vertexShaderFile;
            ifstream fragShaderFile;
            string vertexCode;
            string fragCode;

            vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
            fragShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
            try{
                stringstream vertexShaderStream;
                stringstream fragShaderStream;

                vertexShaderFile.open(vertexShaderPath);
                fragShaderFile.open(fragShaderPath);
                vertexShaderStream<<vertexShaderFile.rdbuf();
                fragShaderStream<<fragShaderFile.rdbuf();
                vertexShaderFile.close();
                fragShaderFile.close();

                vertexCode = vertexShaderStream.str();
                fragCode = fragShaderStream.str();
            }
            catch(ifstream::failure& e){
                cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"<<e.what()<<endl;
            }

            const char* vertexShaderSource = vertexCode.c_str();
            const char* fragShaderSource = fragCode.c_str();

            unsigned int vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader,1,&vertexShaderSource,0);
            glCompileShader(vertexShader);
            
            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader,1,&fragShaderSource,0);
            glCompileShader(fragShader);

            ID = glCreateProgram();
            glAttachShader(ID,vertexShader);
            glAttachShader(ID,fragShader);
            glLinkProgram(ID);
        }

        void use(){
            glUseProgram(ID);
        }
};