/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-24 00:46:37
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-24 12:58:15
 * @FilePath: /Menu_SSD1327_S3/timer2.hpp
 * @Description: 
 */

#include "timer.h"

hw_timer_t *timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

extern mainFun *mainObj;

void ARDUINO_ISR_ATTR onTimer()
{
    portENTER_CRITICAL_ISR(&timerMux);
    mainObj->setScrollFlg(true);
    portEXIT_CRITICAL_ISR(&timerMux);
    xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void timerInit()
{
    timerSemaphore = xSemaphoreCreateBinary();
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 2000000, true);
    timerAlarmEnable(timer);
}

void timerFun()
{
    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
    {
        Serial.println("onTimer");
    }
}

/**
 * @description: 重置计时器
 * @return {*}
 */
void timerReset(){
    mainObj->setScrollFlg(false);
    timerRestart(timer);
}