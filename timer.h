/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-24 11:41:48
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-24 12:55:33
 * @FilePath: /Menu_SSD1327_S3/timer.h
 * @Description:
 */
#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "menuObj.h"

void ARDUINO_ISR_ATTR onTimer();
void timerInit();
void timerFun();
void timerReset();