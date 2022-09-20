#ifndef objects_hpp
#define objects_hpp

#include "geometry.hpp"
#include <cmath>
#include <vector>

// object class
class object {
    double degToRad(const double &degAngle);
    void calculateDirection();
public:
    std::vector<double> coordinates;
    double horizontalAngle, verticalAngle;
    std::vector<double> direction;
    object(const std::vector<double> &newCoord, const double &hAngle, const double &vAngle);
    void turnLeft(const double &angle);
    void turnRight(const double &angle);
    void turnUp(const double &angle);
    void turnDown(const double &angle);
    void moveForward(const double &distance, cubeMap &map);
    void modeBackward(const double &distance, cubeMap &map);
    void moveLeft(const double &distance, cubeMap &map);
    void moveRight(const double &distance, cubeMap &map);
    void moveUp(const double &distance, cubeMap &map);
    void moveDown(const double &distance, cubeMap &map);
};

// camera class
class camera : public object {
    const std::vector<int> resolution;
    double hFOV, vFOV;
    const double renderDistance = 256.0;
    const bool shading = true;
    const double shadeDistance = 128.0;
    const std::vector<double> sunDirection {0.7, 0.7, 0.0};
    const bool fog = true;
    const double fogHeight = 130.0;
    int fogCounter = 0;
    // return value of given color shaded
    unsigned char shadeColor(const unsigned char &oldColor);
public:
    std::vector<std::vector<double>> depthBuffer;
    std::vector<std::vector<unsigned char>> colorBuffer;
    std::vector<std::vector<std::string>> textureBuffer;
    camera(const std::vector<double> &newCoord, const double &hAngle, const double &vAngle,
           const int &xRes, const int &yRes, const double &newFOV);
    // scans map to collect data for buffers
    void scanMap(cubeMap &map);
    // adds cel-shading
    void celShade();
};

class autumnLeave : public object {
    std::string material;
    int counter;
    int maxFramesOnGround = 30;
    int onGroundCounter = 0;
public:
    bool toClean = false;
    autumnLeave(const std::vector<double> &newCoord, const std::string &newMaterial);
    void addToMap(cubeMap &map);
    void fall(cubeMap &map);

};

#endif // objects_hpp
