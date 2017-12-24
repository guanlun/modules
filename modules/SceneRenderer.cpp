//
//  Renderer.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/23/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "SceneRenderer.hpp"

SceneRenderer::SceneRenderer() {
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
}

void SceneRenderer::render(const GameState* currGameState) {
    glm::mat4 viewMatrix = currGameState->mainCam.getViewMatrix();
    glm::mat4 viewProjectionMatrix = currGameState->mainCam.getViewProjectionMatrix();
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto iter = currGameState->sceneObjects.begin(); iter != currGameState->sceneObjects.end(); iter++) {
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
        glUniform3f(glGetUniformLocation(shaderProgramID, "lightPos"), currGameState->lightPos[0], currGameState->lightPos[1], currGameState->lightPos[2]);
        
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
    
    
}
