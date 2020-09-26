//
// Created by zqlxt on 2020/9/26.
//

#include <EGL/egl.h>
#include "GLHelper.h"
#include "../log/LogUtil.h"

void GLHelper::singleDrawColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLHelper::singleDrawTriangle() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    const char *vertexShaderSource =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 vPosition;    \n"
            "void main()                                \n"
            "{                                          \n"
            " gl_Position = vPosition;                  \n"
            "}                                          \n";

    const char *fragmentShaderSource =
            "#version 300 es                            \n"
            "precision mediump float;                   \n"
            "out vec4 fragColor;                        \n"
            "void main()                                \n"
            "{                                          \n"
            " fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                          \n";
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = loadProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteProgram(shaderProgram);
}

GLHelper::GLHelper() {

}

GLHelper::~GLHelper() {

}

GLuint GLHelper::loadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    // create the shader object
    shader = glCreateShader(type);
    if (shader == 0) {
        //create the shader error
        return 0;
    }

    // load the shader source
    glShaderSource(shader, 1, &shaderSrc, nullptr);

    //compile the shader
    glCompileShader(shader);

    // check the compile state
    if (checkShaderCompiled(shader)) {
        return shader;
    } else {
        return 0;
    }
}

GLint GLHelper::checkShaderCompiled(GLuint shader) {
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char *infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
            LOGE("gl: error compile shader:\n %s \n", infoLog);
            delete[]infoLog;
        }
        glDeleteShader(shader);
        return 0;
    }
    return 1;
}

GLuint GLHelper::loadProgram(GLuint vertextShader, GLuint fragmentShader) {
    GLuint program;
    program = glCreateProgram();
    if (program == 0) {
        return 0;
    }
    glAttachShader(program, vertextShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    if (checkProgramLinked(program)) {
        return program;
    } else {
        return 0;
    }
}

GLint GLHelper::checkProgramLinked(GLuint program) {
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = new char[infoLen];
            glGetProgramInfoLog(program, infoLen, nullptr, infoLog);
            LOGE("gl: error link program:\n %s \n", infoLog);
            delete[]infoLog;
        }
        glDeleteProgram(program);
        return 0;
    }
    return 1;
}
