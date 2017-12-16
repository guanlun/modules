// Include standard headers

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "SceneObject.hpp"
#include "Camera.hpp"
#include "ObjectData.hpp"

Camera mainCam(glm::vec3(10, 10, 10));

double lastXPos = -1;
double lastYPos = -1;

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    if (lastXPos != -1 || lastYPos != -1) {
        double deltaX = xPos - lastXPos;
        double deltaY = yPos - lastYPos;
        
        glm::mat4 viewMatrix = mainCam.getViewMatrix();
        viewMatrix[0][0] += 0.01;
        
        mainCam.setViewMatrix(viewMatrix);
    }
    
    lastXPos = xPos;
    lastYPos = yPos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    mainCam.moveCamera(key);
}

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
    
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, keyCallback);
    
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
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    SceneObject sceneObj(ObjectData("/Users/guanlun/Workspace/modules/modules/data/cube.obj"));
    sceneObj.loadShaders("/Users/guanlun/Workspace/modules/modules/SimpleVertexShader.vertexshader", "/Users/guanlun/Workspace/modules/modules/SimpleFragmentShader.fragmentshader");
    
    vector<SceneObject> sceneObjs;
    sceneObjs.push_back(sceneObj);
    
    glm::vec3 lightPos(6, 8, 10);
    
    do {
        glm::mat4 viewMatrix = mainCam.getViewMatrix();
        glm::mat4 viewProjectionMatrix = mainCam.getViewProjectionMatrix();
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (auto iter = sceneObjs.begin(); iter != sceneObjs.end(); iter++) {
            SceneObject obj = *iter;
            
            glm::mat4 modelMtx = obj.getModelMatrix();
            glm::mat4 mvp = viewProjectionMatrix * obj.getModelMatrix();
            
            GLuint shaderProgramID = obj.getShaderProgramID();
            GLuint vertexBuffer = obj.getVertexBuffer();
            GLuint vertexNormalBuffer = obj.getVertexNormalBuffer();
            GLuint vertexTexCoordBuffer = obj.getVertexTexCoordBuffer();
            
            glUseProgram(shaderProgramID);
            
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "MVP"), 1, GL_FALSE, &mvp[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "viewMtx"), 1, GL_FALSE, &viewMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "modelMtx"), 1, GL_FALSE, &modelMtx[0][0]);
            glUniform3f(glGetUniformLocation(shaderProgramID, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, vertexNormalBuffer);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, vertexTexCoordBuffer);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
            glDrawArrays(GL_TRIANGLES, 0, obj.getBufferSize());
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
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

