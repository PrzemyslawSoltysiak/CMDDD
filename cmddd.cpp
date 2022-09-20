#include "colors.hpp"
#include <conio.h>
#include "display.hpp"
#include "objects.hpp"

using namespace std;

int main() {
    const int scale = 4;
    const int xRes = 21 * scale;
    const int yRes = 9 * scale;
    // leaves
    const bool bLeaves = true;
    bool bGenerateLeavesBeforeFirstFrame = false;
    const int leavesGenerationDistance = 128;
    // cel-shading
    const bool bCelShading = false;

    displayBuffer newDisplay(xRes, yRes);

    const vector<int> limits {1000, 500, 1000};
    cube cAir("Air", colorToUnCh(COLOR::LIGHTBLUE), colorToUnCh(COLOR::LIGHTBLUE), "  ", false, false);
    cube cGround("Ground", colorToUnCh(COLOR::DARKGREEN), colorToUnCh(COLOR::LIGHTGREEN), ",\'", false, true);

    cubeMap newMap(limits, cAir, cGround, 100);

    cube cWood("Wood", colorToUnCh(COLOR::GOLD), colorToUnCh(COLOR::BLACK), " |", false, true);
    newMap.cubeSet.push_back(cWood);
    cube cLeaves("Leaves", colorToUnCh(COLOR::LIGHTGREEN), colorToUnCh(COLOR::DARKGREEN), "@@", false, true);
    newMap.cubeSet.push_back(cLeaves);

    cube cALeavesG("Autumn Leaves Green", colorToUnCh(COLOR::LIGHTGREEN), colorToUnCh(COLOR::DARKGREEN), "@@", false, true);
    newMap.cubeSet.push_back(cALeavesG);
    cube cALeavesY("Autumn Leaves Yellow", colorToUnCh(COLOR::LIGHTGREEN), colorToUnCh(COLOR::YELLOW), "@@", false, true);
    newMap.cubeSet.push_back(cALeavesY);
    cube cALeavesR("Autumn Leaves Red", colorToUnCh(COLOR::YELLOW), colorToUnCh(COLOR::LIGHTRED), "@@", false, true);
    newMap.cubeSet.push_back(cALeavesR);

    cube cBushA("Bush A", colorToUnCh(COLOR::DARKRED), colorToUnCh(COLOR::DARKGREEN), "* ", false, true);
    newMap.cubeSet.push_back(cBushA);
    cube cBushB("Bush B", colorToUnCh(COLOR::DARKGREEN));
    newMap.cubeSet.push_back(cBushB);
    cube cStone("Stone", colorToUnCh(COLOR::DARKGREY));
    newMap.cubeSet.push_back(cStone);

    newMap.plantForest({100, 100, 100}, {900, 100, 900});

    vector<double> coord {500, 110, 500};
    camera newCamera(coord, 90.0, 0.0, xRes, yRes, 105.0);

    // main loop
    bool loop = true;
    vector<autumnLeave> leaves;

    while (loop) {
        cubeMap frameMap = newMap;
        // add falling leaves
        if (bLeaves) {
            for (int i = 0; i < 255 * bGenerateLeavesBeforeFirstFrame + 1; ++i) {
                for (int y = 125; y < 155; ++y) {
                    bool nextY = false;
                    int heightTest = 0;
                    for (int x = newCamera.coordinates[0] - leavesGenerationDistance; !nextY && x <= newCamera.coordinates[0] + leavesGenerationDistance; x += 5) {
                        for (int z = newCamera.coordinates[2] - leavesGenerationDistance; !nextY && z <= newCamera.coordinates[2] + leavesGenerationDistance; z += 5) {
                            if (newMap.idFrame[x][y][z] == 0) {
                                unsigned char id = newMap.idFrame[x][y + 1][z];
                                if (newMap.cubeSet[id].name == "Autumn Leaves Red") {
                                    leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Red")); }
                                else if (newMap.cubeSet[id].name == "Autumn Leaves Green") {
                                    leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Green")); }
                                else if (newMap.cubeSet[id].name == "Autumn Leaves Yellow") {
                                    leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Yellow")); }
                                // write function
                                else {
                                    id = newMap.idFrame[x + 1][y][z];
                                    if (newMap.cubeSet[id].name == "Autumn Leaves Red") {
                                        leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Red")); }
                                    else if (newMap.cubeSet[id].name == "Autumn Leaves Green") {
                                        leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Green")); }
                                    else if (newMap.cubeSet[id].name == "Autumn Leaves Yellow") {
                                        leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Yellow")); }
                                    else {
                                        id = newMap.idFrame[x][y][z + 1];
                                        if (newMap.cubeSet[id].name == "Autumn Leaves Red") {
                                            leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Red")); }
                                        else if (newMap.cubeSet[id].name == "Autumn Leaves Green") {
                                            leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Green")); }
                                        else if (newMap.cubeSet[id].name == "Autumn Leaves Yellow") {
                                            leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Yellow")); }
                                        else {
                                            id = newMap.idFrame[x - 1][y][z];
                                            if (newMap.cubeSet[id].name == "Autumn Leaves Red") {
                                                leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Red")); }
                                            else if (newMap.cubeSet[id].name == "Autumn Leaves Green") {
                                                leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Green")); }
                                            else if (newMap.cubeSet[id].name == "Autumn Leaves Yellow") {
                                                leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Yellow")); }
                                            else {
                                                id = newMap.idFrame[x][y][z - 1];
                                                if (newMap.cubeSet[id].name == "Autumn Leaves Red") {
                                                    leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Red")); }
                                                else if (newMap.cubeSet[id].name == "Autumn Leaves Green") {
                                                    leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Green")); }
                                                else if (newMap.cubeSet[id].name == "Autumn Leaves Yellow") {
                                                    leaves.push_back(autumnLeave({x, y, z}, "Autumn Leaves Yellow")); }
                                                // end of duplicates
                                                else {
                                                    ++heightTest; }}}}}
                                if (heightTest > 1024) {
                                    nextY = false; }}}}}}
            for (int i = 0; i < 1023 * bGenerateLeavesBeforeFirstFrame + 1; ++i) {
                vector<autumnLeave> leavesAfterCleaning;
                for (int i = 0; i < leaves.size(); ++i) {
                    leaves[i].addToMap(frameMap);
                    leaves[i].fall(frameMap);
                    if (!leaves[i].toClean &&
                        leaves[i].coordinates[0] > newCamera.coordinates[0] - leavesGenerationDistance &&
                        leaves[i].coordinates[0] < newCamera.coordinates[0] + leavesGenerationDistance &&
                        leaves[i].coordinates[2] > newCamera.coordinates[2] - leavesGenerationDistance &&
                        leaves[i].coordinates[2] < newCamera.coordinates[2] + leavesGenerationDistance) {
                        leavesAfterCleaning.push_back(leaves[i]); }}
                leaves = leavesAfterCleaning; }
            if (bGenerateLeavesBeforeFirstFrame) {
                bGenerateLeavesBeforeFirstFrame = false; }}
        // generate and display image
        newCamera.scanMap(frameMap);
        if (bCelShading) {
            newCamera.celShade(); }
        newDisplay.load(newCamera.colorBuffer, newCamera.textureBuffer);
        system("cls");
        newDisplay.display();

        // keyboard input
        if (kbhit()) {
            char input = getch(); {
            switch (input) {
                case 'w':
                    newCamera.moveForward(10, frameMap);
                    break;
                case 'a':
                    newCamera.moveLeft(10, frameMap);
                    break;
                case 's':
                    newCamera.modeBackward(10, frameMap);
                    break;
                case 'd':
                    newCamera.moveRight(10, frameMap);
                    break;
                case 'i':
                    if (newCamera.verticalAngle <= 75.0 || newCamera.verticalAngle >= 300.0) {
                        newCamera.turnUp(15); }
                    break;
                case 'j':
                    newCamera.turnLeft(15);
                    break;
                case 'k':
                    if (newCamera.verticalAngle <= 225.0 || newCamera.verticalAngle >= 315.0) {
                        newCamera.turnDown(15); }
                    break;
                case 'l':
                    newCamera.turnRight(15);
                    break;
                case 'p':
                    loop = false;
                    break; }}}

        // debug data output
        cout << "Camera horizontal angle: " << newCamera.horizontalAngle << " degrees, " <<
                "vertical angle: " << newCamera.verticalAngle << " degrees" << endl;
        cout << "Camera direction vector: [" << newCamera.direction[0] << ", " << newCamera.direction[1] << ", " << newCamera.direction[2] << "]" << endl;
        cout << "Camera coordinates: " << newCamera.coordinates[0] << ", " << newCamera.coordinates[1] << ", " << newCamera.coordinates[2] << endl; }
}
