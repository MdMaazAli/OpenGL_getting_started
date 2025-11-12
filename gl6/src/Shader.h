#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <glad/glad.h>
using namespace std;

class Shader{
    public:
        unsigned int ID;
        Shader(const char* vertexShaderPath,const char* fragShaderPath){
            string vertexCode;
            string fragCode;
            ifstream vertexShaderFile;
            ifstream fragShaderFile;

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
            glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
            glCompileShader(vertexShader);
            checkCompileError(vertexShader,"VERTEX");

            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader,1,&fragShaderSource,NULL);
            glCompileShader(fragShader);
            checkCompileError(fragShader,"FRAGMENT");

            ID = glCreateProgram();
            glAttachShader(ID,vertexShader);
            glAttachShader(ID,fragShader);
            glLinkProgram(ID);
            checkCompileError(ID,"PROGRAM");

            glDeleteShader(vertexShader);
            glDeleteShader(fragShader);
        }

        void use(){
            glUseProgram(ID);
        }

        void setBool(const string &name,bool value){
            glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
        }

        void setInt(const string &name,int value){
            glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
        }

        void setFloat(const string &name,float value){
            glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
        }

    private:
        void checkCompileError(unsigned int shader,string type){
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
                }
            }
        }
};