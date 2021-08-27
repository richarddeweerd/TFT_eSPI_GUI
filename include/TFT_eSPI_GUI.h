#ifndef TFTGUI_H_
#define TFTGUI_H_

#include "TFT_eSPI.h"

enum ThemeColors
{
    BACKGROUND,
    TEXT,
    WINDOW,
    THEME_COLORS
};

class TFT_eSPI_GUI_Base
{
public:
    TFT_eSPI_GUI_Base();
    TFT_eSPI_GUI_Base(TFT_eSPI *tft, int x, int y, int w, int h, String id);
    virtual ~TFT_eSPI_GUI_Base();

    void addChild(TFT_eSPI_GUI_Base *child);
    TFT_eSPI_GUI_Base *_parentItem = nullptr;
    TFT_eSPI_GUI_Base *_nextItem = nullptr;
    TFT_eSPI_GUI_Base *_firstItem = nullptr;
    TFT_eSPI_GUI_Base *getTopObject();
    String name;

    virtual void drawSelf();
    void draw();

protected:
    int _xpos;
    int _ypos;
    int _width;
    int _height;
    TFT_eSPI *_tft;

private:
};

class Desktop : public TFT_eSPI_GUI_Base
{
public:
    Desktop();
    Desktop(TFT_eSPI *tft, int x, int y, int w, int h, String id);
    int theme[THEME_COLORS];

    void drawSelf();

protected:
    String _text;
};

class Container : public TFT_eSPI_GUI_Base
{
public:
    Container();
    Container(TFT_eSPI *tft, int x, int y, int w, int h, String id);

    void drawSelf();

protected:
    String _text;
};

#endif
