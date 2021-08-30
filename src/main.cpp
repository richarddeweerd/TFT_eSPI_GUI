#include <Arduino.h>
#include "TFT_eSPI.h"
//#include "freefonts.h"
#include "TFT_eSPI_GUI.h"
#define TFT_BACKLIGHT 17

TFT_eSPI tft = TFT_eSPI();

uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

uint16_t calData[5] = {280, 3386, 471, 3402, 2};

//GUI_Screen scrn(&tft, 0, 0, -1, -1, (char *)"Screen");
//GUI_Screen scrn(&tft, (char *)"Screen");
GUI_Screen scrn(&tft, rgb2col(200,200,200));
//GUI_Screen scrn(&tft, 0, 0, -1, -1, (char *)"Screen", rgb2col(200, 200, 200));

//GUI_MenuBar menu();
GUI_Container tb(0, 280, 240, 40, (char *)"Taskbar");
GUI_Container mainPage(0, 0, -1, 100, (char *)"MainPage");
GUI_Container mainMenu(0, 100, 100, 130, (char *)"MainMenu");
GUI_Container testmenu(10, 10, -1, -1, (char *)"Test");
GUI_Container testmenu2(10, 10, -1, -1, (char *)"Test2");

void setup()
{
    Serial.begin(115200);
    Serial.println("start");

    // scrn.theme[BACKGROUND] = TFT_LIGHTGREY;
    // scrn.theme[TEXT] = TFT_WHITE;

    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH);

    tft.init();

    tft.setRotation(2);
    tft.setTouch(calData);
    // Calibrate
    tft.fillScreen(TFT_BLACK);

    scrn.addChild(&mainPage);
    scrn.addChild(&tb);
    scrn.addChild(&mainMenu);
    mainMenu.addChild(&testmenu);
    testmenu.addChild(&testmenu2);
    testmenu.setTheme(rgb2col(255, 0, 255), rgb2col(0, 255, 0));
    

    // put your setup code here, to run once:

    scrn.draw();
}

void loop()
{
    // put your main code here, to run repeatedly:
    Serial.println("1");
    testmenu2.setVisible(false);
    delay(2000);

    Serial.println("2");
    testmenu.setVisible(false);
    delay(2000);

    Serial.println("3");
    testmenu2.setVisible(true);
    delay(2000);
    
    Serial.println("4");
    testmenu.setVisible(true);
    delay(2000);

}