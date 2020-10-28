//
// Created by zqlxt on 2020/10/2.
//

#include "TriangleRender.h"
#include "../gl/GLHelper.h"


void TriangleRender::processShader() {
    glVertexShader = glHelper->loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    glFragmentShader = glHelper->loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
}

void TriangleRender::processProgram() {
    glShaderProgram = glHelper->loadProgram(glVertexShader, glFragmentShader);
}

void TriangleRender::draw() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    glUseProgram(glShaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, sizeof(float) * 6, vertices);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                          vertices + 3);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

TriangleRender::TriangleRender() = default;

TriangleRender::~TriangleRender() = default;

void TriangleRender::release() {
    glDeleteShader(glVertexShader);
    glDeleteShader(glFragmentShader);
    glDeleteProgram(glShaderProgram);
}
