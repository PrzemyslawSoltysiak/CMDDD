#ifndef geometry_hpp
#define geometry_hpp

#include <string>
#include <vector>

// basic cube class
class cube {
public:
    const std::string name;
    const unsigned char foregroundColor;
    const unsigned char backgroundColor;
    const std::string texture;
    const bool transparent;
    const bool solid;
    cube(const std::string &newName, const unsigned char &fColor, const unsigned char &bColor,
         const std::string &newTexture, const bool &isTransparent, const bool &isSolid);
    cube(const std::string &newName, const unsigned char &color);
};

// cube map class
class cubeMap {
    const std::vector<int> limits;
public:
    // environmental variables
    unsigned char season = 4;
    std::vector<double> windDirection {1.0, 0.0, 0.0};
    double windSpeed = 5.0;
    // contains all cubes that are available to place on the map
    std::vector<cube> cubeSet;
    // three-dimensional matrix containing ids of cubes
    std::vector<std::vector<std::vector<unsigned char>>> idFrame;
    cubeMap(const std::vector<int> &newLimits, const cube &cAir);
    cubeMap(const std::vector<int> &newLimits, const cube &cAir,
            const cube &cGround, const int &groundLevel);
    // checks if given point is set within map limits
    bool offLimits(const std::vector<int> &coordinates);
    int getID(const std::string &name);
    // add environment
    void plantTree(const int &xPos, const int &yPos, const int &zPos, const std::string &leavesType);
    void plantBush(const int &xPos, const int &yPos, const int &zPos);
    void putStone(const int &xPos, const int &yPos, const int &zPos);
    // three above combined
    void plantForest(const std::vector<int> &A, const std::vector<int> &B);
};

// cuboid class
class cuboid {
    const std::vector<int> A;
    const std::vector<int> B;
    const std::string materialName;
public:
    cuboid(const std::vector<int> &newA, const std::vector<int> &newB, const std::string &newMaterial);
    void addToMap(cubeMap &map);
};

#endif // geometry_hpp

