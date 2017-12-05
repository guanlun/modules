//
//  ObjectLoader.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/1/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "ObjectLoader.hpp"

glm::vec3 parseVector(string vecStr) {
    string segment;
    stringstream segmentStream(vecStr);
    
    glm::vec3 vertexPos;
    
    int index = 0;
    
    while (getline(segmentStream, segment, ' ')) {
        vertexPos[index++] = stod(segment);
    }
    
    return vertexPos;
}

vector<GLfloat> ObjectLoader::readObjectFile(const char* filename) {
    vector<GLfloat> vertexBufferData;
    
    ifstream objInput(filename);
    
    string objName;
    
    int vCount = 0, nCount = 0, tCount = 0;
    
    vector<glm::vec3> vertexPositions;
    vector<glm::vec3> vertexNormals;
    vector<glm::vec3> vertexTexCoords;

    for (string line; getline(objInput, line); ) {
        stringstream ss(line);
        string part;
        getline(ss, part, ' ');
        
        if (part == "o") {
            getline(ss, part, '\n');
            objName = part + ".obj";
            
            printf("parsing: %s\n", part.c_str());
        } else if (part == "v") {
            vCount++;
            // "part" is the line excluding leading "v"
            getline(ss, part, '\n');
            vertexPositions.push_back(parseVector(part));

        } else if (part == "vn") {
            nCount++;
            getline(ss, part, '\n');
            vertexNormals.push_back(parseVector(part));

        } else if (part == "vt") {
            tCount++;
            getline(ss, part, '\n');
            vertexTexCoords.push_back(parseVector(part));
            
        } else if (part == "f") {
            // "part" is the line excluding leading "f"
            getline(ss, part, '\n');
            
            // each vSegment stands for a vertex in the format X/Y/Z
            string vSegment;
            
            // create a stringstream to handle "part", a series of vSegment
            stringstream vStream(part);
            
            // reset "line" to "f " and later add new face data to it
            line = "";
            
            while (getline(vStream, vSegment, ' ')) { // find all vertices of the face
                string vStr = "", tStr = "", nStr = "";
                
                // a stringstream for each vertex data item X/Y/Z
                stringstream segmentStream(vSegment);
                
                getline(segmentStream, vStr, '/');
                getline(segmentStream, tStr, '/');
                getline(segmentStream, nStr, '/');
                
                int vIndex = atoi(vStr.c_str()) - 1;
                int tIndex = atoi(tStr.c_str()) - 1;
                int nIndex = atoi(nStr.c_str()) - 1;
                
                glm::vec3 vertexPos = vertexPositions[vIndex];
                
                vertexBufferData.push_back(vertexPos[0]);
                vertexBufferData.push_back(vertexPos[1]);
                vertexBufferData.push_back(vertexPos[2]);
                
                glm::vec3 vertexNormal = vertexNormals[nIndex];
                
            }
        }
    }
    
    return vertexBufferData;
}
