#include "TFT_eSPI_GUI.h"

GUI_Screen::GUI_Screen() {}

GUI_Screen::GUI_Screen(TFT_eSPI *tft) : GUI_Base(0, 0, -1, -1, (char *)"Screen")
{
    _tft = tft;
    _background_color = 0;
}

GUI_Screen::GUI_Screen(TFT_eSPI *tft, uint16_t background_color) : GUI_Base(0, 0, -1, -1, (char *)"Screen")
{
    _tft = tft;
    _background_color = background_color;
}

GUI_Screen::GUI_Screen(TFT_eSPI *tft, char name[9], uint16_t background_color) : GUI_Base(0, 0, -1, -1, name)
{
    _tft = tft;
    _background_color = background_color;
}

GUI_Screen::GUI_Screen(TFT_eSPI *tft, int x, int y, int w, int h, char name[9], uint16_t background_color) : GUI_Base(x, y, w, h, name)
{
    _tft = tft;
    _background_color = background_color;
}

void GUI_Screen::drawSelf()
{
    _tft->fillRect(_xpos, _ypos, getMaxWidth(), getMaxHeight(), _background_color);
}

// uint16_t GUI_Screen::totalMargin()
// {
//     return 0;
// }
