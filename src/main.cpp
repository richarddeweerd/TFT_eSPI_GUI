#include <Arduino.h>
#include "TFT_eSPI.h"
//#include "freefonts.h"
#include "TFT_eSPI_GUI.h"
#define TFT_BACKLIGHT 17

TFT_eSPI tft = TFT_eSPI();

uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

uint16_t calData[5] = {280, 3386, 471, 3402, 2};

Desktop dt(&tft, 0, 0, 240, 320, "DT");
Container tb(&tft, 0, 280, 240, 40, "Taskbar");
Container mainPage(&tft, 0, 0, 240, 100, "MainPage");
Container mainMenu(&tft, 0, 100, 240, 180, "MainMenu");
Container testmenu(&tft, 50, 120, 50, 50, "Test");

void setup()
{
  Serial.begin(115200);
  Serial.println("start");

  dt.theme[BACKGROUND] = TFT_LIGHTGREY;
  dt.theme[TEXT] = TFT_WHITE;

  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  tft.init();

  tft.setRotation(2);
  tft.setTouch(calData);
  // Calibrate
  //tft.fillScreen(TFT_BLUE);

  dt.addChild(&tb);
  dt.addChild(&mainPage);
  dt.addChild(&mainMenu);
  mainMenu.addChild(&testmenu);
  // put your setup code here, to run once:

  dt.draw();

  TFT_eSPI_GUI_Base *current = dt._firstItem;
  Serial.println(current->name);
  while (current->_nextItem != nullptr)
  {
    current = current->_nextItem;
    Serial.println(current->name);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  //Serial.println("");
}