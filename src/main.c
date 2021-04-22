#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

#include "fileToString.h"
#include "Buffer.h"

void DebugCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam){
    printf("type: %x ", type);
    printf("id: %d ", id);
    printf("severity: %x\n", severity);
    printf("%s\n", message);
    printf("\n");

    if(severity == GL_DEBUG_SEVERITY_HIGH){
        exit(2);
    }
}

static unsigned int CompileShader(unsigned int type, const char * source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char * message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf("%s %s\n", type == GL_VERTEX_SHADER ? "vertex\n" : "fragment\n" , message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const char * vertexShader, const char * fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glDebugMessageCallback(&DebugCallback, NULL);

    printf("%s\n", glGetString(GL_VERSION));

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    float positions2[] = {
        -0.5f, -1.0f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    CreateVertexBuffer(&buffer, 4 * 2 * sizeof(float), positions);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);


    unsigned int vao2;
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);

    unsigned int buffer2;
    CreateVertexBuffer(&buffer2, 4 * 2 * sizeof(float), positions2);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);


    unsigned int ibo;
    CreateIndexBuffer(&ibo, 6, indices);


    char * vertexShaderPath = "/home/liam/dev/gratest/res/vertex.shader";
    char * fragmentShaderPath = "/home/liam/dev/gratest/res/fragment.shader";
    unsigned int shader = CreateShader( FileToString(vertexShaderPath), FileToString(fragmentShaderPath));
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    float colorChange = 0;

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.3, 0.2, 0.7, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform4f(location, colorChange, 0.8f, 0.3f, 1.0f);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        if( colorChange > 1) {
            colorChange = 0;
        } else {
            colorChange += 0.01f;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}