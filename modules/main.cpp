// Include standard headers

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "SceneObject.hpp"

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    glm::mat4 projectionMtx = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 viewMtx = glm::lookAt(
        glm::vec3(4, 3, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 modelMtx = glm::mat4(1.0f);
    glm::mat4 mvp = projectionMtx * viewMtx * modelMtx;

    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    static const GLfloat vertexBufferData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    SceneObject sceneObj(vertexBufferData, sizeof(vertexBufferData));
    sceneObj.loadShaders("/Users/guanlun/Workspace/modules/modules/SimpleVertexShader.vertexshader", "/Users/guanlun/Workspace/modules/modules/SimpleFragmentShader.fragmentshader");
    
    vector<SceneObject> sceneObjs;
    sceneObjs.push_back(sceneObj);
    
    do {
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        
        for (auto iter = sceneObjs.begin(); iter != sceneObjs.end(); iter++) {
            SceneObject obj = *iter;
            
            GLuint shaderProgramID = obj.getShaderProgramID();
            GLuint vertexBuffer = obj.getVertexBuffer();
            
            glUseProgram(shaderProgramID);
            
            GLuint mtxID = glGetUniformLocation(obj.getShaderProgramID(), "MVP");
            
            glUniformMatrix4fv(mtxID, 1, GL_FALSE, &mvp[0][0]);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO
//    glDeleteBuffers(1, &vertexbuffer);
//    glDeleteVertexArrays(1, &VertexArrayID);
//    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}


