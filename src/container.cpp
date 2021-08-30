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
    int x_offset = getOffsetX();
    int y_offset = getOffsetY();
    getTFT()->fillRect(x_offset, y_offset, getMaxWidth(), getMaxHeight(), _backgroundColor);
    getTFT()->drawRect(x_offset, y_offset, getMaxWidth(), getMaxHeight(), _borderColor);

    // dbg
    getTFT()->setTextDatum(TL_DATUM);
    getTFT()->drawString(_name, x_offset, y_offset);
    // dbg
}

void GUI_Container::setTheme(uint16_t background, uint16_t border)
{
    _backgroundColor = background;
    _borderColor = border;
}
