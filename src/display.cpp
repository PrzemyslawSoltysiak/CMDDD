#include "display.hpp"

using std::vector, std::string, std::cout, std::endl;

displayBuffer::displayBuffer(const int &xRes, const int &yRes):
    resolution({xRes, yRes}) {
    vector<unsigned char> tempColorsY(yRes, 15);
    vector<string> tempTexturesY(yRes, {'[',']'});
    for (int x = 0; x < xRes; ++x) {
        colors.push_back(tempColorsY);
        textures.push_back(tempTexturesY); }}

bool displayBuffer::changePixel(const int &x, const int &y,
                                const unsigned char &color, const string &texture) {
    if (x < 0 || x >= resolution[0] || y < 0 || y >= resolution[1]) {
        return true; }
    else {
        colors[x][y] = color;
        textures[x][y] = texture; }
    return false; }

void displayBuffer::changeScreenColor(const unsigned char &color) {
    colors = vector<vector<unsigned char>>(resolution[0], vector<unsigned char>(resolution[1], color)); }

void displayBuffer::load(const vector<vector<unsigned char>> &newColors,
                         const vector<vector<string>> &newTextures) {
    colors = newColors;
    textures = newTextures; }

void displayBuffer::display() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = resolution[1]; y > 0; ) {
        --y;
        for (int x = 0; x < resolution[0]; ++x) {
            SetConsoleTextAttribute(consoleHandle, colors[x][y]);
            if (textures[x][y].size() == 2) {
                cout << textures[x][y]; }
            else {
                cout << "  "; }}
        SetConsoleTextAttribute(consoleHandle, 0);
        cout << endl; }
    SetConsoleTextAttribute(consoleHandle, 15); }
