/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-23 17:28:32
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-27 23:07:45
 * @FilePath: /Menu_SSD1327_S3/displayFun.hpp
 * @Description:
 */
#include <U8g2lib.h>
#include "menuObj.h"

extern U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2;
extern mainFun *mainObj;
extern bool endAlert;

/*-----------显示------------*/
void mainDisplayFun()
{
    u8g2.clearBuffer();
    /****************************/
    u8g2.drawHLine(0, 14, 128);
    u8g2.drawVLine(80, 14, 120);
    u8g2.drawVLine(83, 14, 120);
    /****************************/
    u8g2.setFont(u8g2_font_prospero_nbp_tf); // u8g2_font_7x14_tf  u8g2_font_prospero_nbp_tf
    // u8g2.setCursor(0,90);
    // u8g2.print("TEST");
    // u8g2.drawBox(0, 0,128,128);

    /*-------主列表--------*/
    mainObj->displayMainItem();

    /*-------副列表--------*/
    mainObj->displaySubItem();
    // Serial.printf("\n\n[BBB]\n");

    /*-------限位提示--------*/
    if (endAlert)
    {
        u8g2.drawBox(3, mainObj->SelectBoxYcode + 5, 4, 4);
        endAlert = false;
    }
    // Serial.printf("\n\n[123]\n");
    /*-------选择框提示--------*/
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, mainObj->SelectBoxYcode, 72, 14); // 主条
#if 1
    u8g2.setDrawColor(1);
    u8g2.drawBox(67, mainObj->SelectBoxYcode, 5, 14); // 滚动遮盖
    u8g2.drawBox(0, mainObj->SelectBoxYcode, 2, 14);  // 滚动遮盖
#endif
    /*-------位置滑条提示--------*/
    mainObj->listSlider();
    // Serial.printf("\n\n[DDD]\n");
    u8g2.setDrawColor(1);
    u8g2.drawBox(80, mainObj->itemSliderOffset * mainObj->itemSliderZoomRatio + 14,
                 3, mainObj->itemSliderZoomRatio * 8);
    // Serial.printf("itemSliderLength = %d\n", mainObj->itemSliderLength);

    /****************************/
    u8g2.sendBuffer();
    // Serial.printf("\n\n[ggg]\n");
}
