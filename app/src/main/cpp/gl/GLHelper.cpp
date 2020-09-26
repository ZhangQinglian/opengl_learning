//
// Created by zqlxt on 2020/9/26.
//

#include <EGL/egl.h>
#include "GLHelper.h"

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


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, 3 * sizeof(float), vertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLHelper::GLHelper() {

}

GLHelper::~GLHelper() {

}

GLuint GLHelper::loadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);
    return shader;
}
