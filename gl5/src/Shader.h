#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h> // include glad to get all the required OpenGL headers
using namespace std;

class Shader{
    public:
        // shaderProgram ID
        unsigned int ID;
        Shader(const char* vertexShaderPath,const char* fragShaderPath){
            // declaring variables to store the shder source code
            string vertexCode;
            string fragCode;
            ifstream vertexShaderFile;
            ifstream fragShaderFile;

            // exception handling
            vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
            fragShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

            // try to fetch the data from the source code
            try{
                // open the vertexShader.glsl and fragShader.glsl
                vertexShaderFile.open(vertexShaderPath);
                fragShaderFile.open(fragShaderPath);

                // reading the buffer (reading the whole glsl file using a stram and rdbuf() a stream)
                stringstream vertexShaderStream;
                stringstream fragShaderStream;
                vertexShaderStream<<vertexShaderFile.rdbuf();
                fragShaderStream<<fragShaderFile.rdbuf();

                // closing the opened glsl files
                vertexShaderFile.close();
                fragShaderFile.close();

                // coverting stringstream to string
                vertexCode = vertexShaderStream.str();
                fragCode = fragShaderStream.str();
            }
            catch(ifstream::failure& e){
                cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "<<e.what()<<endl;
            }

            // converting vertexCode(c++) to vertexShaderSource(c)
            const char* vertexShaderSource = vertexCode.c_str();
            const char* fragShaderSource = fragCode.c_str();

            unsigned int vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
            glCompileShader(vertexShader);
            checkCompileErrors(vertexShader,"VERTEX");

            unsigned int fragShader;
            fragShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragShader,1,&fragShaderSource,NULL);
            glCompileShader(fragShader);
            checkCompileErrors(fragShader,"FRAGMENT");

            ID = glCreateProgram();
            glAttachShader(ID,vertexShader);
            glAttachShader(ID,fragShader);
            glLinkProgram(ID);
            checkCompileErrors(ID,"PROGRAM");

            glDeleteShader(vertexShader);
            glDeleteShader(fragShader);
        }

        // utitlity functions
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
        // utility function for checking shader compilation/linking errors.
        void checkCompileErrors(unsigned int shader, string type)
        {
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
  
#endif