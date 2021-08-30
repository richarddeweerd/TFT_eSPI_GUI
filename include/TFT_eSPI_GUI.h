#ifndef TFTGUI_H_
#define TFTGUI_H_

#include "TFT_eSPI.h"

uint16_t rgb2col(byte r, byte g, byte b);

class GUI_Base
{
public:
    GUI_Base();
    GUI_Base(int x, int y, int w, int h, char name[9]);
    virtual ~GUI_Base();

    void addChild(GUI_Base *child);
    void draw();
    TFT_eSPI *_tft;
    char _name[9];

    void setVisible(bool);

protected:
    int _xpos;
    int _ypos;
    int _width;
    int _height;

    int getOffsetX();
    int getOffsetY();
    int getMaxWidth();
    int getMaxHeight();

    GUI_Base *_parentItem = nullptr;
    GUI_Base *_nextItem = nullptr;
    GUI_Base *_firstItem = nullptr;

    GUI_Base *getTopObject();
    TFT_eSPI *getTFT();

private:
    virtual void drawSelf();
    bool _visible = true;
};

#include "screen.h"
#include "container.h"

#include "menu.h"
#include "statusbar.h"

#endif
