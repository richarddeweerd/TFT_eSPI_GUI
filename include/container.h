/***************************************************************************************
// GUI Container class and helpers
***************************************************************************************/

class GUI_Container : public GUI_Base
{
public:
    GUI_Container();
    GUI_Container(int x, int y, int w, int h, char name[9]);

    void drawSelf();

    void setTheme(uint16_t background, uint16_t border);

protected:
private:
    uint16_t _backgroundColor;
    uint16_t _borderColor;
};
