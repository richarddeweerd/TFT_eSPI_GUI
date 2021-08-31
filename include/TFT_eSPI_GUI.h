#ifndef TFTGUI_H_
#define TFTGUI_H_

#include "TFT_eSPI.h"

uint16_t rgb2col(byte r, byte g, byte b);

struct ScreenWindow
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};

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

    void setVisible(bool val);
    void setBorder(bool val);
    void setMargin(uint16_t val);

    ScreenWindow getClientWindow();

protected:
    int _xpos;
    int _ypos;
    int _width;
    int _height;

    int _xpos_abs;
    int _ypos_abs;
    int _width_abs;
    int _height_abs;

    int getOffsetX();
    int getOffsetY();
    int getMaxWidth();
    int getMaxHeight();

    void setAbsValues(ScreenWindow parentWindow);

    void updateChildAbsValues();

    GUI_Base *_parentItem = nullptr;
    GUI_Base *_nextItem = nullptr;
    GUI_Base *_firstItem = nullptr;
    bool _border = true;

    GUI_Base *getTopObject();
    TFT_eSPI *getTFT();

private:
    virtual void drawSelf();
    virtual uint16_t totalMargin();

    bool _visible = true;
    int _margin = 0;
};

#include "screen.h"
#include "container.h"

#include "menu.h"
#include "statusbar.h"

#endif
