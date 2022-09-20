#include "geometry.hpp"

using std::vector, std::string;

cube::cube(const std::string &newName, const unsigned char &fColor, const unsigned char &bColor,
           const std::string &newTexture, const bool &isTransparent, const bool &isSolid):
    name(newName), foregroundColor(fColor), backgroundColor(bColor),
    texture(newTexture), transparent(isTransparent), solid(isSolid)  {}

cube::cube(const std::string &newName, const unsigned char &color):
    name(newName), foregroundColor(color), backgroundColor(color),
    texture("  "), transparent(false), solid(true) {}

cubeMap::cubeMap(const std::vector<int> &newLimits, const cube &cAir):
    limits(newLimits) {
    cubeSet.push_back(cAir);
    vector<vector<unsigned char>> tempYOZ(limits[1] + 1, vector<unsigned char>(limits[2] + 1, 0));
    for (int x = 0; x <= limits[0]; ++x) {
        idFrame.push_back(tempYOZ); }}

cubeMap::cubeMap(const std::vector<int> &newLimits, const cube &cAir,
                 const cube &cGround, const int &groundLevel):
    limits(newLimits) {
    cubeSet.push_back(cAir);
    cubeSet.push_back(cGround);
    vector<vector<unsigned char>> tempYOZ(limits[1] + 1, vector<unsigned char>(limits[2] + 1, 0));
    for (int x = 0; x <= limits[0]; ++x) {
        idFrame.push_back(tempYOZ); }
    for (int x = 0; x <= limits[0]; ++x) {
        for (int z = 0; z <= limits[2]; ++z) {
            for (int y = 0; y < groundLevel; ++y) {
                idFrame[x][y][z] = 1; }}}}

bool cubeMap::offLimits(const std::vector<int> &coordinates) {
    if (coordinates[0] < 0 || coordinates[0] > limits[0] ||
        coordinates[1] < 0 || coordinates[1] > limits[1] ||
        coordinates[2] < 0 || coordinates[2] > limits[2]) {
        return true; }
    return false; }

int cubeMap::getID(const string &name) {
    for (int index = 0; index < cubeSet.size(); ++index) {
        if (cubeSet[index].name == name) {
            return index; }}
    return 0; }

void cubeMap::plantTree(const int &xPos, const int &yPos, const int &zPos, const string &leavesType) {
    for (int x = xPos - 2; x < xPos + 2; ++x) {
        for (int z = zPos - 2; z < zPos + 2; ++z) {
            for (int y = yPos; y < yPos + 30; ++y) {
                idFrame[x][y][z] = getID("Wood"); }}}
    for (int x = xPos - 10; x < xPos + 10; ++x) {
        for (int z = zPos - 10; z < zPos + 10; ++z) {
            for (int y = yPos + 30; y < yPos + 50; ++y) {
                idFrame[x][y][z] = getID(leavesType); }}}}

void cubeMap::plantBush(const int &xPos, const int &yPos, const int &zPos) {
    int counter = 0;
    for (int x = xPos - 5; x < xPos + 5; ++x) {
        for (int z = zPos - 5; z < zPos + 5; ++z) {
            for (int y = yPos; y < yPos + 5; ++y) {
                if (!(counter % 8)) {
                    idFrame[x][y][z] = getID("Bush A"); }
                else {
                    idFrame[x][y][z] = getID("Bush B"); }
                ++counter; }}}
    for (int x = xPos - 3; x < xPos + 3; ++x) {
        for (int z = zPos - 3; z < zPos + 3; ++z) {
            for (int y = yPos + 5; y < yPos + 8; ++y) {
                if (!(counter % 16)) {
                    idFrame[x][y][z] = getID("Bush A"); }
                else {
                    idFrame[x][y][z] = getID("Bush B"); }
                ++counter; }}}}

void cubeMap::putStone(const int &xPos, const int &yPos, const int &zPos) {
    for (int x = xPos - 1; x < xPos + 1; ++x) {
        for (int z = zPos - 1; z < zPos + 1; ++z) {
            for (int y = yPos; y < yPos + 1; ++y) {
                idFrame[x][y][z] = getID("Stone"); }}}}

void cubeMap::plantForest(const vector<int> &A, const vector<int> &B) {
    // help reduce amount generated of objects
    int counter = 0;
    int leavesRandomizer = 0;
    string leavesType = "Autumn Leaves Green";
    // first set of tree
    for (int x = A[0]; x < B[0]; x += 30) {
        for (int z = A[2]; z < B[2]; z += 30) {
            if (!(counter % 3)) {
                if (season == 4) {
                    plantTree(x, A[1], z, leavesType);
                    ++leavesRandomizer;
                    if (leavesRandomizer % 5 == 0 || leavesRandomizer % 5 == 3) {
                        leavesType = "Autumn Leaves Yellow";
                        leavesRandomizer = leavesRandomizer / 3 + 16; }
                    else if (leavesRandomizer % 5 == 1 || leavesRandomizer % 5 == 4) {
                        leavesType = "Autumn Leaves Red";
                        leavesRandomizer = leavesRandomizer / 2 + 32; }
                    else {
                        leavesType= "Autumn Leaves Green"; }}
                else {
                    plantTree(x, A[1], z, "Leaves"); }}
            ++counter; }}
    // bushes
    for (int x = A[0] + 10; x < B[0]; x += 30) {
        for (int z = A[2] + 10; z < B[2] + 10; z += 30) {
            if (!(counter % 4)) {
                plantBush(x, A[1], z); }
            ++counter; }}
    // second set of tree
    for (int x = A[0] + 20; x < B[0]; x += 30) {
        for (int z = A[2] + 20; z < B[2] + 20; z += 30) {
            if (!(counter % 5)) {
                 if (season == 4) {
                    plantTree(x, A[1], z, leavesType);
                    ++leavesRandomizer;
                    if (leavesRandomizer % 5 == 0 || leavesRandomizer % 5 == 3) {
                        leavesType = "Autumn Leaves Yellow";
                        leavesRandomizer = leavesRandomizer / 3 + 16; }
                    else if (leavesRandomizer % 5 == 1 || leavesRandomizer % 5 == 4) {
                        leavesType = "Autumn Leaves Red";
                        leavesRandomizer = leavesRandomizer / 2 + 32; }
                    else {
                        leavesType= "Autumn Leaves Green"; }}
                else {
                    plantTree(x, A[1], z, "Leaves"); }}
            ++counter; }}
    // stones
    for (int x = A[0]; x < B[0]; x += 30) {
        for (int z = A[2]; z < B[2]; z += 30) {
            if (!(counter % 6)) {
                putStone(x, A[1], z); }
            ++counter; }}
    // ground leaves
    if (season == 4) {
        int groundLeavesRandomizer = 0;
        for (int x = A[0] + 10; x < B[0]; ++x) {
            for (int z = A[2]; z < B[2]; ++z) {
                ++groundLeavesRandomizer;
                if (groundLeavesRandomizer % 8 == 0 || groundLeavesRandomizer % 8 == 5 || groundLeavesRandomizer % 8 == 6) {
                    idFrame[x][A[1]][z] = getID("Autumn Leaves Yellow");
                    groundLeavesRandomizer = groundLeavesRandomizer * 5;  }
                else if (groundLeavesRandomizer % 8 == 1 || groundLeavesRandomizer % 8 == 2) {
                    idFrame[x][A[1]][z] = getID("Autumn Leaves Red");
                    groundLeavesRandomizer = groundLeavesRandomizer * 4; }
                else if (groundLeavesRandomizer % 8 == 3 || groundLeavesRandomizer % 8 == 4) {
                    idFrame[x][A[1]][z] = getID("Autumn Leaves Green");
                    groundLeavesRandomizer = groundLeavesRandomizer * 3; }}}}}

cuboid::cuboid(const vector<int> &newA, const vector<int> &newB, const string &newMaterial):
    A(newA), B(newB), materialName(newMaterial) {}

void cuboid::addToMap(cubeMap &map) {
    unsigned char id = map.getID(materialName);
    for (int x = A[0]; x < B[0]; ++x) {
        for (int y = A[1]; y < B[1]; ++y) {
            for (int z = A[2]; z < B[2]; ++z) {
                map.idFrame[x][y][z] = id; }}}}
