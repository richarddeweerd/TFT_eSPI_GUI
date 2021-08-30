#include "arduino.h"
#include "TFT_eSPI_GUI.h"

uint16_t rgb2col(byte r, byte g, byte b)
{
    uint16_t resp = (r & 0b11111000) << 8;
    resp = resp + ((g & 0b11111100) << 3);
    resp = resp + ((b & 0b11111000) >> 3);
    return resp;
}

GUI_Base::GUI_Base()
{
    _tft = nullptr;
    _xpos = 0;
    _ypos = 0;
    _width = 0;
    _height = 0;
    // name = "\0";
}

GUI_Base::GUI_Base(int x, int y, int w, int h, char name[9])
{
    _xpos = x;
    _ypos = y;
    _width = w;
    _height = h;
    strncpy(_name, name, 9);
}

GUI_Base::~GUI_Base() {}

void GUI_Base::addChild(GUI_Base *child)
{
    if (child->_parentItem != nullptr)
    {
        return; // Item must not be added two times.
    }
    child->_parentItem = this;
    if (this->_firstItem == nullptr)
    {
        this->_firstItem = child;
        return;
    }
    GUI_Base *current = this->_firstItem;
    while (current->_nextItem != nullptr)
    {
        current = current->_nextItem;
    }
    current->_nextItem = child;
}

GUI_Base *GUI_Base::getTopObject()
{
    if (_parentItem == nullptr)
    {
        return this;
    }
    GUI_Base *current = this->_parentItem;
    while (current->_parentItem != nullptr)
    {
        current = current->_parentItem;
    }
    return current;
}

TFT_eSPI *GUI_Base::getTFT()
{
    if (_parentItem == nullptr)
    {
        Serial.println(_name);
        delay(2000);
        return _tft;
    }
    GUI_Base *current = this->_parentItem;
    while (current->_parentItem != nullptr)
    {
        current = current->_parentItem;
    }

    return current->_tft;
}

int GUI_Base::getOffsetX()
{
    if (_parentItem == nullptr)
    {
        return _xpos;
    }
    else
    {
        return (_parentItem->getOffsetX() + _xpos);
    }
}

int GUI_Base::getOffsetY()
{
    if (_parentItem == nullptr)
    {
        return _ypos;
    }
    else
    {
        return (_parentItem->getOffsetY() + _ypos);
    }
}

int GUI_Base::getMaxWidth()
{
    if (_width >= 0)
    {
        return _width;
    }
    if (_parentItem != nullptr)
    {
        return _parentItem->getMaxWidth() - _xpos;
    }
    else
    {
        if (_tft != nullptr)
        {
            return _tft->width();
        }
    }
    return 0;
}

int GUI_Base::getMaxHeight()
{
    if (_height >= 0)
    {
        return _height;
    }
    if (_parentItem != nullptr)
    {
        return _parentItem->getMaxHeight() - _ypos;
    }
    else
    {
        if (_tft != nullptr)
        {
            return _tft->height();
        }
    }
    return 0;
}

void GUI_Base::drawSelf() {}

void GUI_Base::draw()
{
    if (_visible)
    {
        //only draw the object and its childs if it is visible
        drawSelf();

        if (this->_firstItem != nullptr)
        {
            //Object has child object(s) draw them first
            GUI_Base *next = this->_firstItem;
            next->draw();
        }
    }
    if (this->_nextItem != nullptr)
    {
        //Object has sibbeling object(s) draw them now
        GUI_Base *next = this->_nextItem;
        next->draw();
    }
}

void GUI_Base::setVisible(bool val)
{
    _visible = val;
    if (_parentItem != nullptr)
    {
        _parentItem->draw();
    }
}
