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

void GUI_Base::setAbsValues(ScreenWindow parentWindow)
{
    _xpos_abs = parentWindow.x + _xpos;
    _ypos_abs = parentWindow.y + _ypos;
    if ((parentWindow.width - _xpos < _width) || _width < 0)
    {
        _width_abs = parentWindow.width - _xpos;
    }
    else
    {
        _width_abs = _width;
    }
    if ((parentWindow.height - _ypos < _height) || _height < 0)
    {
        _height_abs = parentWindow.height - _ypos;
    }
    else
    {
        _height_abs = _height;
    }
}

void GUI_Base::updateChildAbsValues()
{
    if (this->_firstItem != nullptr)
    {
        //has childs
        GUI_Base *current = this->_firstItem;
        current->setAbsValues(getClientWindow());
        current->updateChildAbsValues();
        while (current->_nextItem != nullptr)
        {
            current = current->_nextItem;
            current->setAbsValues(getClientWindow());
            current->updateChildAbsValues();
        }
    }
}

void GUI_Base::addChild(GUI_Base *child)
{
    if (child->_parentItem != nullptr)
    {
        return; // Item must not be added two times.
    }
    child->_parentItem = this;
    child->setAbsValues(getClientWindow());
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
            _firstItem->draw();
        }
    }
    if (this->_nextItem != nullptr)
    {
        //Object has sibbeling object(s) draw them now
        _nextItem->draw();
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

void GUI_Base::setBorder(bool val)
{
    _border = val;
    updateChildAbsValues();
    if (_parentItem != nullptr)
    {
        _parentItem->draw();
    }
}

void GUI_Base::setMargin(uint16_t val)
{
    _margin = val;
    updateChildAbsValues();
    if (_parentItem != nullptr)
    {
        _parentItem->draw();
    }
}

uint16_t GUI_Base::totalMargin()
{
    return _margin;
}

ScreenWindow GUI_Base::getClientWindow()
{
    ScreenWindow clientWindow;
    int offset = _margin;
    if (_border)
    {
        offset += 1;
    }
    clientWindow.x = _xpos_abs + offset;
    clientWindow.y = _ypos_abs + offset;
    clientWindow.width = _width_abs - (offset * 2);
    clientWindow.height = _height_abs - (offset * 2);
    return clientWindow;
}
