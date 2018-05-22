//
//  Renderer.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "Application.hpp"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

double lastXPos = -1;
double lastYPos = -1;


vector<SceneObject> sceneObjs;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//        float screenSpaceY = -((float)lastYPos / WINDOW_HEIGHT - 0.5) * 2;
//        float screenSpaceX = ((float)lastXPos / WINDOW_WIDTH - 0.5) * 2 * ((float)WINDOW_WIDTH / WINDOW_HEIGHT);
//
//        const float projRatio = tan(45.0 / 2 / 180 * 3.1416);
//        float cameraSpaceY = screenSpaceY * projRatio;
//        float cameraSpaceX = screenSpaceX * projRatio;
//
//        glm::vec4 cameraSpaceRayVec(cameraSpaceX, cameraSpaceY, -1, 1);
//        glm::mat4 inverseViewMtx = glm::inverse(mainCam.getViewMatrix());
//
//        // ignore the translation performed by the world -> camera space transformation
//        inverseViewMtx[3][0] = .0f;
//        inverseViewMtx[3][1] = .0f;
//        inverseViewMtx[3][2] = .0f;
//
//        glm::vec3 worldSpaceRayVec(inverseViewMtx * cameraSpaceRayVec);
//
//        glm::vec3 cameraPos = mainCam.getCameraPos();
//
//        float minT = INT_MAX;
//        SceneObject* intersectedObj = NULL;
//
//        for (auto &obj : sceneObjs) {
//            glm::mat4 inverseModelMtx = glm::inverse(obj.getModelMatrix());
//            glm::vec3 modelSpaceRayStartPoint(inverseModelMtx * glm::vec4(cameraPos, 1));
//
//            inverseModelMtx[3][0] = .0f;
//            inverseModelMtx[3][1] = .0f;
//            inverseModelMtx[3][2] = .0f;
//            glm::vec3 modelSpaceRayDir(inverseModelMtx * glm::vec4(worldSpaceRayVec, 1));
//
//            float t = obj.intersectRay(modelSpaceRayStartPoint, modelSpaceRayDir);
//
//            if (t > 0 && t < minT) {
//                minT = t;
//                intersectedObj = &obj;
//            }
//        }
//
//        if (intersectedObj) {
//            cout << intersectedObj->getBufferSize() << endl;
//        }
//    }
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    if (lastXPos != -1 || lastYPos != -1) {
        double deltaX = xPos - lastXPos;
        double deltaY = yPos - lastYPos;
        
//        mainCam.rotateCamera(deltaX, deltaY);
    }
    
    lastXPos = xPos;
    lastYPos = yPos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    mainCam.moveCamera(key);
}

Application::Application() {
    this->initWindow();
    
    this->sceneRenderer = new SceneRenderer();
    this->gameState = new GameState();
}

bool Application::initWindow() {
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Modules", NULL, NULL);
    
    if (this->window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, keyCallback);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    return true;
}

void Application::start() {
    do {
        StateManager::updateState(this->gameState);
        this->sceneRenderer->render(this->gameState);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    
    // Cleanup VBO
    //    glDeleteBuffers(1, &vertexbuffer);
    //    glDeleteVertexArrays(1, &VertexArrayID);
    //    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
