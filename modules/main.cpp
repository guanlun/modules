#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "SceneObject.hpp"
#include "Camera.hpp"
#include "ObjectData.hpp"

GLFWwindow* window;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

//Camera mainCam(glm::vec3(10, 10, 10));
Camera mainCam(glm::vec3(0, 0, 0));

double lastXPos = -1;
double lastYPos = -1;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        float screenSpaceY = -((float)lastYPos / WINDOW_HEIGHT - 0.5) * 2;
        float screenSpaceX = ((float)lastXPos / WINDOW_WIDTH - 0.5) * 2 * ((float)WINDOW_WIDTH / WINDOW_HEIGHT);
        
        const float projRatio = tan(45.0 / 2 / 180 * 3.1416);
        float cameraSpaceY = screenSpaceY * projRatio;
        float cameraSpaceX = screenSpaceX * projRatio;
        
        glm::vec4 cameraSpaceRayVec(cameraSpaceX, cameraSpaceY, -1, 1);
        glm::mat4 inverseViewMtx = glm::inverse(mainCam.getViewMatrix());
        inverseViewMtx[3][0] = .0f;
        inverseViewMtx[3][1] = .0f;
        inverseViewMtx[3][2] = .0f;
        
        cout << "inverse view matrix: " << endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << inverseViewMtx[j][i] << "\t";
            }
            
            cout << endl;
        }
        cout << endl;
        
        glm::vec3 worldSpaceRayVec(inverseViewMtx * cameraSpaceRayVec);
        
        glm::vec3 cameraPos = mainCam.getCameraPos();
        float camZ = cameraPos[2];
        float rayZ = worldSpaceRayVec[2];
        
        float rayT = (-4 - camZ) / rayZ;
        
        glm::vec3 intersectionPoint = cameraPos + worldSpaceRayVec * rayT;
        
        cout << cameraSpaceRayVec[0] << "\t" << cameraSpaceRayVec[1] << "\t" << cameraSpaceRayVec[2] << endl;
        cout << worldSpaceRayVec[0] << "\t" << worldSpaceRayVec[1] << "\t" << worldSpaceRayVec[2] << endl;
        cout << intersectionPoint[0] << "\t" << intersectionPoint[1] << "\t" << intersectionPoint[2] << endl;
        cout << endl;
    }
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    if (lastXPos != -1 || lastYPos != -1) {
        double deltaX = xPos - lastXPos;
        double deltaY = yPos - lastYPos;
        
        mainCam.rotateCamera(deltaX, deltaY);
    }
    
    lastXPos = xPos;
    lastYPos = yPos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    mainCam.moveCamera(key);
}

int main() {
    // Initialise GLFW
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Modules", NULL, NULL);
    
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, keyCallback);
    
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
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
    
    vector<SceneObject> sceneObjs;
    
//    SceneObject teapot(ObjectData("/Users/guanlun/Workspace/modules/modules/data/teapot.obj"), glm::vec3(2, 0, 0));
//    teapot.loadShaders("/Users/guanlun/Workspace/modules/modules/SimpleVertexShader.vertexshader", "/Users/guanlun/Workspace/modules/modules/SimpleFragmentShader.fragmentshader");
//    sceneObjs.push_back(teapot);
    
    SceneObject cube(ObjectData("/Users/guanlun/Workspace/modules/modules/data/cube.obj"), glm::vec3(0, 0, -5));
    cube.loadShaders("/Users/guanlun/Workspace/modules/modules/SimpleVertexShader.vertexshader", "/Users/guanlun/Workspace/modules/modules/SimpleFragmentShader.fragmentshader");
    sceneObjs.push_back(cube);
    
    glm::vec3 lightPos(6, 8, 10);
    
    do {
        glm::mat4 viewMatrix = mainCam.getViewMatrix();
        glm::mat4 viewProjectionMatrix = mainCam.getViewProjectionMatrix();
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (auto iter = sceneObjs.begin(); iter != sceneObjs.end(); iter++) {
            SceneObject obj = *iter;
            
            glm::mat4 modelMtx = obj.getModelMatrix();
            glm::mat4 inverseTransposeModelMtx = glm::transpose(glm::inverse(modelMtx));
            glm::mat4 mvp = viewProjectionMatrix * obj.getModelMatrix();
            
            GLuint shaderProgramID = obj.getShaderProgramID();
            GLuint vertexBuffer = obj.getVertexBuffer();
            GLuint vertexNormalBuffer = obj.getVertexNormalBuffer();
            GLuint vertexTexCoordBuffer = obj.getVertexTexCoordBuffer();
            
            glUseProgram(shaderProgramID);
            
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "MVP"), 1, GL_FALSE, &mvp[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "viewMtx"), 1, GL_FALSE, &viewMatrix[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "modelMtx"), 1, GL_FALSE, &modelMtx[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "invTransModelMtx"), 1, GL_FALSE, &inverseTransposeModelMtx[0][0]);
            glUniform3f(glGetUniformLocation(shaderProgramID, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, vertexNormalBuffer);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
//            glEnableVertexAttribArray(2);
//            glBindBuffer(GL_ARRAY_BUFFER, vertexTexCoordBuffer);
//            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            
            glDrawArrays(GL_TRIANGLES, 0, obj.getBufferSize());
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
//            glDisableVertexAttribArray(2);
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

