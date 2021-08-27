#include "arduino.h"
#include "TFT_eSPI_GUI.h"

TFT_eSPI_GUI_Base::TFT_eSPI_GUI_Base() {}

TFT_eSPI_GUI_Base::TFT_eSPI_GUI_Base(TFT_eSPI *tft, int x, int y, int w, int h, String id)
{
    _tft = tft;
    _xpos = x;
    _ypos = y;
    _width = w;
    _height = h;
    name = id;
}

TFT_eSPI_GUI_Base::~TFT_eSPI_GUI_Base() {}

void TFT_eSPI_GUI_Base::addChild(TFT_eSPI_GUI_Base *child)
{
    if (child->_parentItem != nullptr)
    {
        return; // Item must not be added two times.
    }
    if (this->_firstItem == nullptr)
    {
        this->_firstItem = child;
        return;
    }
    TFT_eSPI_GUI_Base *current = this->_firstItem;
    while (current->_nextItem != nullptr)
    {
        current = current->_nextItem;
    }
    current->_nextItem = child;
    child->_parentItem = this;
}

TFT_eSPI_GUI_Base *TFT_eSPI_GUI_Base::getTopObject()
{
    if (_parentItem == nullptr)
    {
        return this;
    }
    TFT_eSPI_GUI_Base *current = this->_parentItem;
    while (current->_parentItem != nullptr)
    {
        current = current->_parentItem;
    }
    return current;
}

void TFT_eSPI_GUI_Base::drawSelf() {}

void TFT_eSPI_GUI_Base::draw()
{
    drawSelf();
    if (this->_firstItem != nullptr)
    {
        //Object has child object(s) draw them first
        TFT_eSPI_GUI_Base *next = this->_firstItem;
        next->draw();
    }
    if (this->_nextItem != nullptr)
    {
        //Object has sibbeling object(s) draw them now
        TFT_eSPI_GUI_Base *next = this->_nextItem;
        next->draw();
    }
}

Desktop::Desktop() {}

Desktop::Desktop(TFT_eSPI *tft, int x, int y, int w, int h, String id) : TFT_eSPI_GUI_Base(tft, x, y, w, h, id)
{
    //_text = text;
}

void Desktop::drawSelf()
{
    _tft->fillScreen(theme[BACKGROUND]);
}

Container::Container() {}

Container::Container(TFT_eSPI *tft, int x, int y, int w, int h, String id) : TFT_eSPI_GUI_Base(tft, x, y, w, h, id)
{
    //_text = text;
}
void Container::drawSelf()
{
    _tft->drawRect(_xpos, _ypos, _width, _height, TFT_WHITE);
    _tft->setTextDatum(TL_DATUM);
    _tft->drawString(name, _xpos, _ypos);
}
