#include "main.h"
#include "deps/cglm/include/cglm/vec3.h"
float charpos[3] = {0, 0, 3.0};
int forward = 0;
int backword = 0;
int leftword = 0;
int rightword = 0;
float mousex = -M_PI/2;
float mousey;

int main(void)
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    GLFWmonitor * primary = glfwGetPrimaryMonitor();

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow * window = SetupGLFW();

    int width, height, xpos, ypos;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

    printf("%s\n", glGetString(GL_VERSION));

    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
    vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f}, 
        { 2.0f,  5.0f, -15.0f}, 
        {-1.5f, -2.2f, -2.5f},  
        {-3.8f, -2.0f, -12.3f},  
        { 2.4f, -0.4f, -3.5f},  
        {-1.7f,  3.0f, -7.5f},  
        { 1.3f, -2.0f, -2.5f},  
        { 1.5f,  2.0f, -2.5f}, 
        { 1.5f,  0.2f, -1.5f}, 
        {-1.3f,  1.0f, -1.5f}  
    };

    struct VertexBuffer * vb = CreateVertexBuffer(vertices, sizeof(vertices), 8 * sizeof(float));
    struct VertexArray * vao = CreateVertexArray(vb);
    AddAttribPointer(vao, 3);
    AddAttribPointer(vao, 3);
    AddAttribPointer(vao, 2);

    struct VertexArray * lightVao = CreateVertexArray(vb);
    AddAttribPointer(lightVao, 3);

    char * vertexShader = FileToString("res/vert.vs");
    char * fragmentShader = FileToString("res/object.fs");
    char * lightshader = FileToString("res/light.fs");
    struct Material * boxMaterial = CreateMaterial(vertexShader, fragmentShader);
    struct Material * lightMaterial = CreateMaterial(vertexShader, lightshader);

    struct Texture * container_spec = CreateTexture("img/container2_specular.png");
    struct Texture * container = CreateTexture("img/container2.png");
    glUseProgram(boxMaterial->id);
    BindTexture(container, GL_TEXTURE0);
    BindTexture(container_spec, GL_TEXTURE1);
    glUniform1i(glGetUniformLocation(boxMaterial->id, "u_texture"), 0);
    glUniform1i(glGetUniformLocation(boxMaterial->id, "u_texture2"), 1);

    vec3 direction;
    mat4 projection;
    glm_perspective(glm_rad(90.0f), (float)width/(float)height, 0.1f, 100.0f, projection);

    vec3 up = {0.0, 1.0, 0.0};
    /* vec3 objectColor = {1.0f, 0.5f, 0.31f}; */
    vec3 objectColor = {0.3f,0.8f,0.8f};
    vec3 lightColor = {1.0f,1.0f,1.0f};
    /* vec3 lightColor = {245.0f/255.0f,212.0f/255.0f,0.0f}; */
    /* vec3 lightColor = {0.3f,0.8f,0.8f}; */
    vec3 lightPos = { 1.2f, 1.0f, 2.0f};
    /* glm_vec3_scale(lightPos, 2.0f, lightPos); */
    /* vec3 lightPos = { -1.2f, -1.0f, -2.0f}; */
    /* vec3 lightPos = {0.0, 1.0, 0.0}; */
    vec3 axis = {1.0f, 0.3f, 0.5f};
    mat4 model;
    mat4 view;

    struct Object * box = CreateObject(vao, boxMaterial, &model[0][0], &view[0][0], &projection[0][0]);
    struct Object * light = CreateObject(lightVao, lightMaterial, &model[0][0], &view[0][0], &projection[0][0]);

    float offset = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        offset +=0.01f;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm_mat4_identity(model);
        glm_mat4_identity(view);

        calcView(&view, &direction);
        move(direction);

        BindObject(box);
        glUniform3fv(glGetUniformLocation(boxMaterial->id, "lightPos"), 1, lightPos);
        glUniform3fv(glGetUniformLocation(boxMaterial->id, "lightColor"), 1, lightColor);
        glUniform3fv(glGetUniformLocation(boxMaterial->id, "objectColor"), 1, objectColor);
        glUniform1f(glGetUniformLocation(boxMaterial->id, "constant"), 1.0f);
        glUniform1f(glGetUniformLocation(boxMaterial->id, "linear"), 0.09f);
        glUniform1f(glGetUniformLocation(boxMaterial->id, "quadratic"), 0.032f);
        /* for(unsigned int i = 0; i < 10; i++) */
        /* { */
        /*     glm_mat4_identity(model); */

        /*     glm_translate(model, cubePositions[i]); */
        /*     float angle = 20.0f * i; */
        /*     glm_rotate(model, angle + offset, axis); */
        /*     glUniformMatrix4fv(glGetUniformLocation(boxMaterial->id, "model"), 1, GL_FALSE, &model[0][0]); */

        /*     glDrawArrays(GL_TRIANGLES, 0, 36); */
        /* } */
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUniform3fv(glGetUniformLocation(boxMaterial->id, "viewPos"), 1, charpos);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm_vec3_rotate(lightPos, 0.01f, up);
        glm_translate_make(model, lightPos);
        vec3 resizer = {0.3f, 0.3f, 0.3f};
        glm_scale(model, resizer);

        BindObject(light);
        glUniform3fv(glGetUniformLocation(lightMaterial->id, "lightColor"), 1, &lightColor[0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(boxMaterial->id);
    glDeleteProgram(lightMaterial->id);
    glfwTerminate();
    return 0;
}

GLFWwindow * SetupGLFW()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return NULL;
    }

    /* Make the window's context current */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &window_size_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);

    glewInit();
    glDebugMessageCallback(&DebugCallback, NULL);
    glEnable(GL_DEPTH_TEST);

    return window;
}

void calcView(mat4 * view, vec3 * direction)
{
    vec3 up = {0.0, 1.0, 0.0};
    vec3 center = {0.0f,0.0f,0.0f};

    vec3 newDir = {
        cos(mousex) * cos(mousey),
        -sin(mousey),
        sin(mousex) * cos(mousey)
    };

    glm_vec3_copy(newDir, *direction);

    glm_vec3_add(charpos, newDir, center);
    glm_lookat(charpos, center, up, *view);
}

void move(float direction[3])
{
    float movedir[3] = {0.0f,0.0f,0.0f};
    float up[3] = {0.0f,1.0f,0.0f};
    if(forward && backword){}
    else if(forward)
    {
        glm_vec3_add(direction, movedir, movedir);
    }else if(backword) {
        glm_vec3_add(direction, movedir, movedir);
        glm_vec3_scale(movedir, -1, movedir);
    }

    float strafeDir[3];
    glm_vec3_copy(direction, strafeDir);
    if(leftword && rightword){}
    else if (leftword) 
    {
        glm_vec3_rotate(strafeDir, glm_rad(90.0f), up);
        glm_vec3_divs(strafeDir, cos(mousey), strafeDir);
        strafeDir[1] = 0;
    }
    else if(rightword) 
    {
        glm_vec3_rotate(strafeDir, glm_rad(270.0f), up);
        glm_vec3_divs(strafeDir, cos(mousey), strafeDir);
        strafeDir[1] = 0;
    }

    if(leftword || rightword) glm_vec3_add(movedir, strafeDir, movedir);

    glm_vec3_normalize(movedir);
    glm_vec3_divs(movedir, 40, movedir);
    glm_vec3_add(movedir, charpos, charpos);
}

void window_size_callback(GLFWwindow * window, int width, int height){
    glViewport(0, 0, width, height);
}

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

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_W:
            if(action == GLFW_PRESS) forward = true;
            else if(action == GLFW_RELEASE) forward = false;
            break;
        case GLFW_KEY_S:
            if(action == GLFW_PRESS) backword = true;
            else if(action == GLFW_RELEASE) backword = false;
            break;
        case GLFW_KEY_A:
            if(action == GLFW_PRESS) leftword = true;
            else if(action == GLFW_RELEASE) leftword = false;
            break;
        case GLFW_KEY_D:
            if(action == GLFW_PRESS) rightword = true;
            else if(action == GLFW_RELEASE) rightword = false;
            break;
        default:
            break;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, (float)width/2, (float)height/2);

    mousex+=xpos/(float)width-0.5f;

    if((mousey +(ypos/height -0.5f)/3) < -3.14/2){
        mousey = -3.14/2;
    } else if((mousey +(ypos/height -0.5f)/3) > 3.14/2){
        mousey = 3.14/2;
    } else {
        mousey+= (ypos/height -0.5f)/3;
    }
}
