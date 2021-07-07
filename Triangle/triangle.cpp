//For file/stream output, e.g printf();
#include <stdio.h>

//OpenGL Extension Wrangler Library, GLEW. For managine opengl extenstions
#include <GL/glew.h>

//OpenGL extension. Handles window creating, rendering and input
#include <GLFW/glfw3.h>

//Change viewport framebuffer size to window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0, width, height);
};

//Input function
void input(GLFWwindow* window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) ){
        glfwSetWindowShouldClose(window, true);
        printf("Closing program...\n");
    }
};


#pragma region "Settings"

    //Window settings
    const unsigned int window_width = 800;
    const unsigned int window_height = 600;


    //Shader source code
    //Vertex shader source code
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    //Fragment shader source code
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColour;\n"
    "void main() {\n"
    "   FragColour = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "};\n";

#pragma endregion


int main(){
    printf("Starting program...\n");

    #pragma region "Initalise and create window"

        //Initialise GLFW, and check if successful. If not, send error
        if( !glfwInit() ){ fprintf( stderr, "Failed to initialise GLFW" ); } else { printf("GLFW initialised\n"); };

        //Window creation parameters
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGL 3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Don't use old profile
        
        //Create window
        GLFWwindow* window = glfwCreateWindow( window_width, window_height, "Triangle", NULL, NULL);

        //Check if window creation was successful, if not send error
        if( window == NULL ){ fprintf( stderr, "failed to create GLFW window"); glfwTerminate(); } else {printf( "GLFW window successfully created\n"); };

        //Push window to foreground
        glfwMakeContextCurrent(window);

        //Initalise GLEW, check if successful. If not, send error
        glewExperimental=true;
        if( glewInit() != GLEW_OK ){ fprintf( stderr, "Failed to initialise GLEW\n" ); } else { printf("GLEW successfully initalised\n"); };

        //Run framebuffer_size_callback() function when user resizes the window
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    #pragma endregion

    #pragma region "Compile shaders and build shader program"

        //Setup success check variables
        int success;
        char infoLog[512];


        //Compile vertex shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        //Check if vertex shaders compilation was successful
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if(!success){
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            printf("GL_VERTEX_SHADER Compilation failed: "); 
            printf(infoLog);
            printf("\n");
        } else { printf("GL_VERTEX_SHADER Compilation successful\n"); };


        //Compile fragment shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        //Check if fragment shader compilation was successful
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if(!success){
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            printf("GL_FRAGMENT_SHADER Compilation failed\n");
            printf(infoLog);
            printf("\n");
        } else { printf("GL_FRAGMENT_SHADER Compilation successful\n"); };


        //Shader program object creation
        unsigned int shaderProgram = glCreateProgram();

        //Attach then link compiled shaders to shader program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        //Check if linking was successful
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            printf("Shader program linking failed\n");
            printf(infoLog);
            printf("\n");
        } else { printf("Shader program linking successful\n"); };


        //Delete shader objects after linking, don't need them anymore
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    #pragma endregion

    #pragma region "Vertex and buffer setup"

        //Triangle points/vertices
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        //Generate Vertex buffer objects(VBO)
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        //Generate and bind vertex array object(VAO)
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);     //Bind VAO before binding VBO

        //Bind Vertex Buffer Objects(VBO) and copy verticies into buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //How the vertex data should be interpreted
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), 0);
        glEnableVertexAttribArray(0);

    #pragma endregion

    //Draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //The loop
    while( !glfwWindowShouldClose(window) ){

        //Call input script
        input(window);

        #pragma region "Render"

            //Clear the screen for the new frame
            glClearColor(1,1,1,1);  //White
            glClear( GL_COLOR_BUFFER_BIT );

            //Set shaders and array
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);

            //Draw array
            glDrawArrays(GL_TRIANGLES, 0, 3);

        #pragma endregion

        //Output render to window
        glfwSwapBuffers(window);
        //Poll input/output events
        glfwPollEvents(); 
    };

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
};