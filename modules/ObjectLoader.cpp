//
//  ObjectLoader.cpp
//  modules
//
//  Created by Guanlun Zhao on 12/1/17.
//  Copyright © 2017 Guanlun Zhao. All rights reserved.
//

#include "ObjectLoader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ObjectLoader::readObjectFile(const char* filename) {
    ifstream objInput(filename);
    
    string objName;
    
    int vCount = 0, nCount = 0, tCount = 0;
    int vOffset, nOffset, tOffset;

    for (string line; getline(objInput, line); ) {
        stringstream ss(line);
        string part;
        getline(ss, part, ' ');
        
        if (part == "o") {
            vOffset = vCount;
            nOffset = nCount;
            tOffset = tCount;
            
            getline(ss, part, '\n');
            objName = part + ".obj";
            
            printf("parsing: %s\n", part.c_str());
        } else if (part == "v") {
            vCount++;
        } else if (part == "vn") {
            nCount++;
        } else if (part == "vt") {
            tCount++;
        } else if (part == "f") {
            // "part" is the line excluding leading "f"
            getline(ss, part, '\n');
            
            // each vSegment stands for a vertex in the format X/Y/Z
            std::string vSegment;
            
            // create a stringstream to handle "part", a series of vSegment
            std::stringstream vStream(part);
            
            // reset "line" to "f " and later add new face data to it
            line = "";
            std::stringstream newFaceStream;
            newFaceStream << "f ";
            
            while (getline(vStream, vSegment, ' ')) { // find all vertices of the face
                std::string vStr, tStr, nStr;
                
                // a stringstream for each vertex data item X/Y/Z
                std::stringstream segmentStream(vSegment);
                
                getline(segmentStream, vStr, '/');
                getline(segmentStream, tStr, '/');
                getline(segmentStream, nStr, '/');
                
                if (nStr.empty()) { // cannot find normal vector
//                    throw "normal vector not supplied";
                }
                
                int vIndex = atoi(vStr.c_str()) - vOffset;
                int nIndex = atoi(nStr.c_str()) - nOffset;
                int tIndex = -1;
                
                if (!tStr.empty()) { // texture coord provided
                    tIndex = atoi(tStr.c_str()) - tOffset;
                }
                
                newFaceStream << vIndex << '/';
                if (tIndex != -1) { // texture coord provided
                    newFaceStream << tIndex;
                }
                newFaceStream << '/';
                newFaceStream << nIndex << ' ';
            }
            
            line = newFaceStream.str();
        }

    }
}
