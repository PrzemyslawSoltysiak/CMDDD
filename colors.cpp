#include "colors.hpp"

unsigned char colorToUnCh(const COLOR &color) {
    return (unsigned char)color; }

unsigned char colorToUnChMultiLayer(const COLOR &foregroundColor, const COLOR &backgroundColor) {
    return (unsigned char)((int)foregroundColor + (int)backgroundColor * 16); }

COLOR unChToColor(const unsigned char &value) {
    if (value < 16) {
        return COLOR(value); }
    else {
        return COLOR::BLACK; }}
