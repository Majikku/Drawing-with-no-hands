//For console output
#include <stdio.h>
//#include <stdlib.h>

//*magic*
#include <GL/glew.h>

//Window & keyboard manager
#include <GLFW/glfw3.h>

int main(){
    printf("Starting program...\n");

    //Initialise GLFW, you can read what this does
    if( !glfwInit() ){ 
        fprintf( stderr, "Failed to initialise GLFW" ); 
    } else { printf("GLFW initialised!\n"); };

    //Window creation code
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGl 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Don't use old profile

    //Open a window
    GLFWwindow* window = glfwCreateWindow( 1080, 768, "Basic OpenGL Window", NULL, NULL);; //Create window named "Basic OpenGL window"

    //You can read this. If no window = fail
    if(window == NULL){
        fprintf( stderr, "Failed to open GLFW window");
        glfwTerminate();
    } else { printf("Window successfully created!\n"); };

    glfwMakeContextCurrent(window); //initialise GLEW

    //You know this already. If no GLEW = fail
    glewExperimental=true; //Dunno, but its for driver stuff
    if(glewInit() != GLEW_OK){
        fprintf( stderr, "Failed to initialise GLEW\n"); 
    };

    //"Looptime"
    while (!glfwWindowShouldClose(window)) { 
        //Close window when escape key is pressed
        if( glfwGetKey(window, GLFW_KEY_ESCAPE) ){ printf("Closing window...\n"); glfwSetWindowShouldClose(window, true); };

        //Clear the screen before drawing
        glClear( GL_COLOR_BUFFER_BIT );
        
        //Set colour of the background to pastel pink
        glClearColor(1,0.82,0.86,1); //Pastel Pink

        //Buffers
        glfwSwapBuffers(window);
        glfwWaitEvents(); //Update render ONLY when receiving a new event. 
        //glfwPollEvents(); Updates render every frame
    }
};