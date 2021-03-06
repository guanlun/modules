//
//  ObjectLoader.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/1/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "ObjectData.hpp"

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

ObjectData::ObjectData(string filename) {    
    ifstream objInput(filename.c_str());
    
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
                glm::vec3 vertexPos = vertexPositions[vIndex];
                
                vertexPositionData.push_back(vertexPos[0]);
                vertexPositionData.push_back(vertexPos[1]);
                vertexPositionData.push_back(vertexPos[2]);
                
                if (tStr.length() > 0) {
                    int tIndex = atoi(tStr.c_str()) - 1;
                    
                    glm::vec3 vertexTexCoord = vertexTexCoords[tIndex];
                    
                    vertexTexCoordData.push_back(vertexTexCoord[0]);
                    vertexTexCoordData.push_back(vertexTexCoord[1]);
                    vertexTexCoordData.push_back(vertexTexCoord[2]);
                }
                
                if (nStr.length() > 0) {
                    int nIndex = atoi(nStr.c_str()) - 1;
                    glm::vec3 vertexNormal = vertexNormals[nIndex];
                    
                    vertexNormalData.push_back(vertexNormal[0]);
                    vertexNormalData.push_back(vertexNormal[1]);
                    vertexNormalData.push_back(vertexNormal[2]);
                }
            }
        }
    }
}
