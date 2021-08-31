#include "TFT_eSPI_GUI.h"

GUI_Container::GUI_Container() {}

GUI_Container::GUI_Container(int x, int y, int w, int h, char name[9]) : GUI_Base(x, y, w, h, name)
{
    //_text = text;
    _backgroundColor = rgb2col(180, 180, 180);
    _borderColor = rgb2col(255, 255, 255);
}
void GUI_Container::drawSelf()
{
    getTFT()->fillRect(_xpos_abs, _ypos_abs, _width_abs, _height_abs, _backgroundColor);
    if (_border)
    {
        getTFT()->drawRect(_xpos_abs, _ypos_abs, _width_abs, _height_abs, _borderColor);
    }

    // dbg
    getTFT()->setTextDatum(TL_DATUM);
    getTFT()->drawString(_name, _xpos_abs, _ypos_abs);
    // dbg
}

void GUI_Container::setTheme(uint16_t background, uint16_t border)
{
    _backgroundColor = background;
    _borderColor = border;
}
