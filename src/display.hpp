#ifndef display_hpp
#define display_hpp

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

// buffer containing screen content currently to display
class displayBuffer {
    // vector containing screen resolution
    const std::vector<int> resolution;
    // vector containing color values
    std::vector<std::vector<unsigned char>> colors;
    // vector containing textures (2 character strings)
    std::vector<std::vector<std::string>> textures;
public:
    // creates new displayBuffer of given resolution
    displayBuffer(const int &xRes, const int &yRes);
    // changes color and texture of given pixel, returns 1 if pixel does not exist
    bool changePixel(const int &x, const int &y,
                     const unsigned char &color, const std::string &texture);
    // changes color of the whole screen
    void changeScreenColor(const unsigned char &color);
    // loads new content to display
    void load(const std::vector<std::vector<unsigned char>> &newColors,
              const std::vector<std::vector<std::string>> &newTextures);
    // displays content of buffer
    void display();
};

#endif // display_hpp
