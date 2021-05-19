#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Shader.h"
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
const GLuint WIDTH = 1600, HEIGHT = 900;

void CopyFromFramebufferToTexture(GLuint fboSrc, GLuint texDest, int xo, int yo, int x, int y, int w, int h)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboSrc);

    glBindTexture(GL_TEXTURE_2D, texDest);

    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, xo, yo, x, y, w, h);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, WIDTH, HEIGHT);

    Shader ourShader("../src/12_texturebuffer/textures.vs", "../src/12_texturebuffer/textures.frag");

    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // Top Right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // Top Left
    };
    GLuint indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    // textureSource 为新图像的来源
    // textureLast   为上次的结果
    // textureResult 为本次合成的图像

    GLuint textureSource;
    glGenTextures(1, &textureSource);
    glBindTexture(GL_TEXTURE_2D, textureSource);                  // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height;
    unsigned char *image = SOIL_load_image("../images/wood1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    GLuint textureLast;
    glGenTextures(1, &textureLast);
    glBindTexture(GL_TEXTURE_2D, textureLast);                    // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    GLuint textureResult;
    glGenTextures(1, &textureResult);
    glBindTexture(GL_TEXTURE_2D, textureResult);                  // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    GLuint textureEmpty;
    glGenTextures(1, &textureEmpty);
    glBindTexture(GL_TEXTURE_2D, textureEmpty);                   // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    GLuint fboSource;
    glGenFramebuffers(1, &fboSource);
    glBindFramebuffer(GL_FRAMEBUFFER, fboSource);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureSource, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLuint fboLast;
    glGenFramebuffers(1, &fboLast);
    glBindFramebuffer(GL_FRAMEBUFFER, fboLast);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureLast, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLuint fboResult;
    glGenFramebuffers(1, &fboResult);
    glBindFramebuffer(GL_FRAMEBUFFER, fboResult);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureResult, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLuint fboEmpty;
    glGenFramebuffers(1, &fboEmpty);
    glBindFramebuffer(GL_FRAMEBUFFER, fboEmpty);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureEmpty, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    int cnt = 0;

    while (!glfwWindowShouldClose(window))
    {
        ++cnt;

        // ----------------------------------------------------------
        // create a new frame buffer and do some stupid image copy
        // ----------------------------------------------------------

        int w0 = 2;

        for (int i = 1; i <= 5; i++)
        {
            CopyFromFramebufferToTexture(fboResult, textureLast, 0, 0, 0, 0, width, height);
            CopyFromFramebufferToTexture(fboLast, textureResult, 0, 0, w0 - 1, 0, width - w0 + 1, height);
            CopyFromFramebufferToTexture(cnt % 2 ? fboSource : fboEmpty, textureResult, width - w0, 0, 0, 0, w0, height);
        }

        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureResult);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}