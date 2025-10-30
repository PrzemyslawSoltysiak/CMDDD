#include "objects.hpp"

using std::vector, std::string, std::atan, std::cos, std::tan, std::sin, std::round;

double object::degToRad(const double &degAngle) {
    return (degAngle / 180.0) * (4 * atan(1.0)); }

void object::calculateDirection() {
    direction[0] = cos(degToRad(horizontalAngle));
    if (verticalAngle < 90.0) {
        direction[1] = tan(degToRad(verticalAngle)); }
    else if (verticalAngle < 270.0) {
        direction[1] = 1.0 / tan(degToRad(verticalAngle - 90.0)); }
    else if (verticalAngle < 360.0) {
        direction[1] = tan(degToRad(verticalAngle)); }
    direction[2] = sin(degToRad(horizontalAngle)); }

object::object(const vector<double> &newCoord, const double &hAngle, const double &vAngle):
    coordinates(newCoord), horizontalAngle(hAngle), verticalAngle(vAngle) {
    direction.push_back(cos(degToRad(horizontalAngle)));
    if (verticalAngle < 90.0) {
        direction.push_back(tan(degToRad(verticalAngle))); }
    else if (verticalAngle < 270.0) {
        direction.push_back(1.0 / tan(degToRad(verticalAngle - 90.0))); }
    else if (verticalAngle < 360.0) {
        direction.push_back(tan(degToRad(verticalAngle))); }
    direction.push_back(sin(degToRad(horizontalAngle))); }

void object::turnLeft(const double &angle) {
    horizontalAngle += angle;
    if (horizontalAngle >= 360.0) {
        horizontalAngle -= 360.0; }
    calculateDirection(); }

void object::turnRight(const double &angle) {
    horizontalAngle -= angle;
    if (horizontalAngle < 0) {
        horizontalAngle += 360.0; }
    calculateDirection(); }

void object::turnUp(const double &angle) {
    verticalAngle += angle;
    if (verticalAngle >= 360.0) {
        verticalAngle -= 360.0; }
    calculateDirection(); }

void object::turnDown(const double &angle) {
    verticalAngle -= angle;
    if (verticalAngle < 0) {
        verticalAngle += 360.0; }
    calculateDirection(); }

void object::moveForward(const double &distance, cubeMap &map) {
    bool collision = false;
    for (double cDistance = 0.0; cDistance < distance; ) {
        ++cDistance;
        for (double y = coordinates[1] - 8; y <= coordinates[1]; ++y) {
            vector<int> searchPoint;
            searchPoint.push_back(round(coordinates[0] + cDistance * direction[0]));
            searchPoint.push_back(round(y));
            searchPoint.push_back(round(coordinates[2] + cDistance * direction[2]));
            if (map.offLimits(searchPoint)) {
                collision = true;
                break; }
            int id = map.idFrame[searchPoint[0]][searchPoint[1]][searchPoint[2]];
            if (map.cubeSet[id].solid) {
                collision = true;
                break; }}
        if (collision) {
            break; }}
    if (!collision) {
        coordinates[0] += distance * direction[0];
        coordinates[2] += distance * direction[2]; }}

void object::modeBackward(const double &distance, cubeMap &map) {
    bool collision = false;
    for (double cDistance = 0.0; cDistance < distance; ) {
        ++cDistance;
        for (double y = coordinates[1] - 8; y <= coordinates[1]; ++y) {
            vector<int> searchPoint;
            searchPoint.push_back(round(coordinates[0] - cDistance * direction[0]));
            searchPoint.push_back(round(y));
            searchPoint.push_back(round(coordinates[2] - cDistance * direction[2]));
            if (map.offLimits(searchPoint)) {
                collision = true;
                break; }
            int id = map.idFrame[searchPoint[0]][searchPoint[1]][searchPoint[2]];
            if (map.cubeSet[id].solid) {
                collision = true;
                break; }}
        if (collision) {
            break; }}
    if (!collision) {
        coordinates[0] -= distance * direction[0];
        coordinates[2] -= distance * direction[2]; }}

void object::moveLeft(const double &distance, cubeMap &map) {
    turnLeft(90.0);
    bool collision = false;
    for (double cDistance = 0.0; cDistance < distance; ) {
        ++cDistance;
        for (double y = coordinates[1] - 8; y <= coordinates[1]; ++y) {
            vector<int> searchPoint;
            searchPoint.push_back(round(coordinates[0] + cDistance * direction[0]));
            searchPoint.push_back(round(y));
            searchPoint.push_back(round(coordinates[2] + cDistance * direction[2]));
            if (map.offLimits(searchPoint)) {
                collision = true;
                break; }
            int id = map.idFrame[searchPoint[0]][searchPoint[1]][searchPoint[2]];
            if (map.cubeSet[id].solid) {
                collision = true;
                break; }}
        if (collision) {
            break; }}
    if (!collision) {
        coordinates[0] += distance * direction[0];
        coordinates[2] += distance * direction[2]; }
    turnRight(90.0); }

void object::moveRight(const double &distance, cubeMap &map) {
    turnRight(90.0);
    bool collision = false;
    for (double cDistance = 0.0; cDistance < distance; ) {
        ++cDistance;
        for (double y = coordinates[1] - 8; y <= coordinates[1]; ++y) {
            vector<int> searchPoint;
            searchPoint.push_back(round(coordinates[0] + cDistance * direction[0]));
            searchPoint.push_back(round(y));
            searchPoint.push_back(round(coordinates[2] + cDistance * direction[2]));
            if (map.offLimits(searchPoint)) {
                collision = true;
                break; }
            int id = map.idFrame[searchPoint[0]][searchPoint[1]][searchPoint[2]];
            if (map.cubeSet[id].solid) {
                collision = true;
                break; }}
        if (collision) {
            break; }}
    if (!collision) {
        coordinates[0] += distance * direction[0];
        coordinates[2] += distance * direction[2]; }
    turnLeft(90.0); }

void object::moveUp(const double &distance, cubeMap &map) {
    bool collision = false;
    for (double cDistance = 0.0; cDistance < distance; ) {
        ++cDistance;
        for (double y = coordinates[1] - 8; y <= coordinates[1]; ++y) {
            vector<int> searchPoint;
            searchPoint.push_back(round(coordinates[0]));
            searchPoint.push_back(round(y + cDistance));
            searchPoint.push_back(round(coordinates[2]));
            if (map.offLimits(searchPoint)) {
                collision = true;
                break; }
            int id = map.idFrame[searchPoint[0]][searchPoint[1]][searchPoint[2]];
            if (map.cubeSet[id].solid) {
                collision = true;
                break; }}
        if (collision) {
            break; }}
    if (!collision) {
        coordinates[1] += distance; }}

void object::moveDown(const double &distance, cubeMap &map) {
    bool collision = false;
    for (double cDistance = 0.0; cDistance < distance; ) {
        ++cDistance;
        for (double y = coordinates[1] - 8; y <= coordinates[1]; ++y) {
            vector<int> searchPoint;
            searchPoint.push_back(round(coordinates[0]));
            searchPoint.push_back(round(y + cDistance));
            searchPoint.push_back(round(coordinates[2]));
            if (map.offLimits(searchPoint)) {
                collision = true;
                break; }
            int id = map.idFrame[searchPoint[0]][searchPoint[1]][searchPoint[2]];
            if (map.cubeSet[id].solid) {
                collision = true;
                break; }}
        if (collision) {
            break; }}
    if (!collision) {
        coordinates[1] -= distance; }}

unsigned char camera::shadeColor(const unsigned char &oldColor) {
    unsigned char newColor = oldColor;
    if (oldColor == 12) {
        newColor = 4; }
    else if (oldColor == 10) {
        newColor = 2; }
    else if (oldColor == 3) {
        newColor = 9; }
    else if (oldColor == 9) {
        newColor = 1; }
    else if (oldColor == 7) {
        newColor = 8; }
    else if (oldColor == 14) {
        newColor = 6; }
    return newColor; }

camera::camera(const vector<double> &newCoord, const double &hAngle, const double &vAngle,
               const int &xRes, const int &yRes, const double &newFOV):
    object(newCoord, hAngle, vAngle), resolution({xRes, yRes}), hFOV(newFOV), vFOV(75.0) {
    depthBuffer = vector<vector<double>>(xRes, vector<double>(yRes, 0.0));
    colorBuffer = vector<vector<unsigned char>>(xRes, vector<unsigned char>(yRes, 0));
    textureBuffer = vector<vector<string>>(xRes, vector<string>(yRes, "  ")); }

void camera::scanMap(cubeMap &map) {
    // create new temporal camera
    camera temp(coordinates, horizontalAngle, verticalAngle, resolution[0], resolution[1], hFOV);
    // set temp camera direction to the upper left corner of FOV
    temp.turnLeft(hFOV / 2);
    temp.turnUp(vFOV / 2);
    // iterate over output lines
    for (int y = resolution[1]; y > 0; ) {
        --y;
        // iterate over pixels - output columns
        for (int x = 0; x < resolution[0]; ++x) {
            // set default output color and texture to sky
            colorBuffer[x][y] = map.cubeSet[0].foregroundColor + map.cubeSet[0].backgroundColor * 16;
            textureBuffer[x][y] = map.cubeSet[0].texture;
            // path-trace for output pixel data
            double depth = 0.0;
            bool transparent = false;
            while (true) {
                // create new int-type coordinates search point
                vector<int> searchpoint(3);
                // move search point in temporal camera direction
                searchpoint[0] = round(coordinates[0] + depth * temp.direction[0]);
                searchpoint[1] = round(coordinates[1] + depth * temp.direction[1]);
                searchpoint[2] = round(coordinates[2] + depth * temp.direction[2]);
                // check if search point is set within cubeMap limits
                if (depth > renderDistance || map.offLimits(vector<int> {searchpoint[0], searchpoint[1], searchpoint[2]})) {
                    // add fog
                    if (fog) {
                        if (searchpoint[1] - fogCounter % 6 < fogHeight) {
                            if (!(fogCounter % 2)) {
                                colorBuffer[x][y] =  7 * 17; }}
                        ++fogCounter;
                        // some pseudo-procedural nonsense
                        if (fogCounter % 3) {
                            fogCounter = fogCounter * 7 + 16; }
                        if (fogCounter % 4) {
                            fogCounter = fogCounter / 2 + 14; }}
                    break; }
                else {
                    // get id of search point cube
                    unsigned char id = map.idFrame[searchpoint[0]][searchpoint[1]][searchpoint[2]];
                    // check if first founded cube is transparent
                    if (!transparent && map.cubeSet[id].transparent) {
                        // get foreground color and texture
                        colorBuffer[x][y] = map.cubeSet[id].foregroundColor + map.cubeSet[0].backgroundColor * 16;
                        textureBuffer[x][y] = map.cubeSet[id].texture;
                        // set flag
                        transparent = true;
                        // go to next iteration
                        continue; }
                    // check if cube is solid and is not transparent
                    if (map.cubeSet[id].solid && !map.cubeSet[id].transparent) {
                        // if transparent flag is set, only update color
                        if (transparent) {
                            colorBuffer[x][y] -= map.cubeSet[0].backgroundColor * 16;
                            colorBuffer[x][y] += map.cubeSet[id].backgroundColor * 16; }
                        // if it's not, get texture and start shading
                        else {
                            textureBuffer[x][y] = map.cubeSet[id].texture;
                            unsigned char foregroundColor = map.cubeSet[id].foregroundColor;
                            unsigned char backgroundColor = map.cubeSet[id].backgroundColor;
                            // shading begins
                            if (shading) {
                                double shadeDepth = 0.0;
                                // path-trace for shading data
                                while (true) {
                                    ++shadeDepth;
                                    // create new search point from founded cube in sun direction
                                    searchpoint[0] += round(shadeDepth * sunDirection[0]);
                                    searchpoint[1] += round(shadeDepth * sunDirection[1]);
                                    searchpoint[2] += round(shadeDepth * sunDirection[2]);
                                    // check if search point is set within cubeMap limits
                                    if (shadeDepth > shadeDistance || map.offLimits(vector<int> {searchpoint[0], searchpoint[1], searchpoint[2]})) {
                                        break; }
                                    // get id of cube between sun and cube founded for pixel output
                                    unsigned char shadeId = map.idFrame[searchpoint[0]][searchpoint[1]][searchpoint[2]];
                                    // check if new cube is solid and is not transparent
                                    if (map.cubeSet[shadeId].solid && !map.cubeSet[shadeId].transparent) {
                                        // change colors
                                        backgroundColor = shadeColor(backgroundColor);
                                        foregroundColor = shadeColor(foregroundColor);
                                        break; }}}
                            // update pixel color
                            colorBuffer[x][y] = foregroundColor + backgroundColor * 16;
                        break; }}}
                ++depth; }
            // get depth
            depthBuffer[x][y] = depth;
            // move temporal camera to next pixel
            temp.turnRight(hFOV / resolution[0]); }
        // set camera to the left side of FOV
        temp.turnLeft(hFOV);
        // move camera down to next line
        temp.turnDown(vFOV / resolution[1]); }}

void camera::celShade() {
    for (int x = 0; x < resolution[0]; ++x) {
        for (int y = 0; y < resolution[1]; ++y) {
            bool celShade = false;
            for (int scanX = x - 1; scanX < x + 1 && !celShade; ++scanX) {
                if (scanX < 0 || scanX >= depthBuffer.size()) {
                    continue; }
                for (int scanY = y - 1; scanY < y + 1 && !celShade; ++scanY) {
                    if (scanY < 0 || scanY >= depthBuffer[x].size()) {
                        continue; }
                    if (std::abs(depthBuffer[x][y] - depthBuffer[scanX][scanY]) > 8.0) {
                        colorBuffer[x][y] = 0;
                        textureBuffer[x][y] = "  ";
                        celShade = true; }}}}}}

autumnLeave::autumnLeave(const vector<double> &newCoord, const string &newMaterial):
    object(newCoord, 0.0, 0.0), material(newMaterial) {
    counter = coordinates[0] * 3 - coordinates[1] * 2 + coordinates[2]; }

void autumnLeave::addToMap(cubeMap &map) {
    map.idFrame[round(coordinates[0])][round(coordinates[1])][round(coordinates[2])] = map.getID(material); }

void autumnLeave::fall(cubeMap &map) {
    direction = map.windDirection;
    vector<double> groundTestCoord = coordinates;
    if (!map.cubeSet[map.idFrame[round(coordinates[0])][round(coordinates[1]) - 1][round(coordinates[2])]].solid) {
        coordinates[1] -= 2.0 + map.windSpeed / 2.0; }
    else {
        ++onGroundCounter;
        if (onGroundCounter > maxFramesOnGround) {
            toClean = true; }}
    /* moveDown(30.0 + map.windSpeed / 2.0, map);
    if (coordinates == groundTestCoord) {
        for (double distance = 5.0; distance > 0; distance -= 0.5) {
            moveDown(distance, map);
            if (coordinates != groundTestCoord) {
                break; }}
        if (coordinates == groundTestCoord) {
            ++onGroundCounter;
            if (onGroundCounter > maxFramesOnGround) {
                toClean = true; }}} */
    moveForward(map.windSpeed, map);
    if (counter % 8 == 0 || counter % 8 == 4) {
        moveLeft(map.windSpeed / 3.0, map); }
    else if (counter % 8 == 2 || counter % 8 == 6) {
        moveRight(map.windSpeed / 3.0, map); }
    ++counter;
    if (counter > 1024) {
        counter /= 512; }}
