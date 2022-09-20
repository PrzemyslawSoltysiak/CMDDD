#ifndef colors_hpp
#define colors_hpp

// colors
enum class COLOR : unsigned char {
    BLACK, DARKBLUE, DARKGREEN, LIGHTBLUE, DARKRED, PURPLE, GOLD, LIGHTGREY,
    DARKGREY, BLUE, LIGHTGREEN, TURQUOISE, LIGHTRED, PINK, YELLOW, WHITE
};

// returns numerical value of given color (for whole cell)
unsigned char colorToUnCh(const COLOR &color);

// returns numerical value of given combination of colors
unsigned char colorToUnChMultiLayer(const COLOR &foregroundColor, const COLOR &backgroundColor);

// returns color of given value, works only with numbers from 0 to 15
COLOR unChToColor(const unsigned char &value);

#endif // colors_hpp

