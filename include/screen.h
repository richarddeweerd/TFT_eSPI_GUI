/***************************************************************************************
// GUI_Screen class and helpers
***************************************************************************************/
#include "TFT_eSPI.h"
#include "TFT_eSPI_GUI.h"

class GUI_Screen : public GUI_Base
{
public:
    GUI_Screen();
    GUI_Screen(TFT_eSPI *tft);
    GUI_Screen(TFT_eSPI *tft, uint16_t background_color);
    GUI_Screen(TFT_eSPI *tft, char name[9], uint16_t background_color);
    GUI_Screen(TFT_eSPI *tft, int x, int y, int w, int h, char name[9], uint16_t background_color);

    void drawSelf();

protected:

private:
    uint16_t _background_color;
    // uint16_t totalMargin();
};