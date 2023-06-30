/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-22 12:18:11
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-28 22:07:16
 * @FilePath: /Menu_SSD1327_S3/Menu_SSD1327_S3.ino
 * @Description:
 * @todo: 目前滚动条右侧需要处理，完毕后菜单主功能完成60%，下来着重看一下level切换，
 * 逻辑大体通过三个按键完成，上下与确认，返回通过“../”完成；完成后，优化子列表显示信
 * 息。完成后优化动画。
 */
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "menuObj.h"
#include "UIdesign.h"
#include "displayFun.hpp"
#include "timer.h"
// #include "esp_log.h"

#define touchPinA 4
#define touchPinB 5
#define touchPinC 6

U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/10, /* dc=*/16, /* reset=*/17);

bool touchStatusA = false;
bool touchStatusB = false;
bool touchStatusC = false;

touch_value_t touchTreshold = 60000;
mainFun *mainObj = new mainFun;

enum Direction
{
  up = 0,
  down
} dir;

/*--------控制相关----------*/
void touchAFunction()
{
  touchStatusA = true;
}

void touchBFunction()
{
  touchStatusB = true;
}

void touchCFunction()
{
  touchStatusC = true;
}

/*------------主要部分--------------*/
void setup(void)
{
  Serial.begin(115200);

  timerInit();

  mainObj->resetStrOffset(); // 没写构造函数的锅

  listInit();

  u8g2.begin();
  pinMode(touchPinA, INPUT);
  pinMode(touchPinB, INPUT);
  pinMode(touchPinC, INPUT);
  touchAttachInterrupt(touchPinA, touchAFunction, touchTreshold);
  touchAttachInterrupt(touchPinB, touchBFunction, touchTreshold);
  touchAttachInterrupt(touchPinC, touchCFunction, touchTreshold);
  mainDisplayFun();
}

void loop(void)
{
  if (touchStatusA) // 也许有用的消抖
  {
    delayMicroseconds(20);
    if (touchRead(touchPinA) > touchTreshold)
    {
      mainObj->setScrollFlg(false);
      mainObj->resetStrOffset();
      mainObj->updateSelectionBox(up);
      timerReset(); // 滚动字符串触发的定时器
      touchStatusA = false;
    }
  }
  if (touchStatusB)
  {
    delayMicroseconds(20);
    if (touchRead(touchPinB) > touchTreshold)
    {
      mainObj->setScrollFlg(false);
      mainObj->resetStrOffset();
      mainObj->updateSelectionBox(down);
      timerReset();
      touchStatusB = false;
    }
  }
  if (touchStatusC)
  {
    delayMicroseconds(20);
    if (touchRead(touchPinC) > touchTreshold)
    {
      mainObj->confirmItem();
      touchStatusC = false;
    }
  }
  mainDisplayFun();
  // timerFun();  //检查定时器是否正常
  vTaskDelay(100);
}
