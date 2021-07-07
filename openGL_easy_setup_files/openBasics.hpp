#include <iostream>
#include <GL/eglew.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0, width, height);
};

class openGLBasics {
    #pragma region "Settings"

    public:
        unsigned int windowWidth = 800;
        unsigned int windowHeight = 600;
        int windowEscapeKey = GLFW_KEY_ESCAPE;

    #pragma endregion
    private:

};