/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-23 17:28:32
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-07-01 15:01:24
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
    u8g2.setFont(u8g2_font_6x13_mr); //u8g2_font_prospero_nbp_tf这个好看但是不等宽
    //u8g2_font_t0_13_mr 也不错，但是稍微宽了点

    /*-------主列表--------*/
    mainObj->displayMainItem();

    /*-------副列表--------*/
    mainObj->displaySubItem();

    /*-------限位提示--------*/
    if (endAlert)
    {
        u8g2.drawBox(2, mainObj->selectBoxYcode + 3, 3, 8);
        endAlert = false;
    }
    /*-------选择框提示--------*/
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, mainObj->selectBoxYcode, 78, 14); // 主条
#if 1
    u8g2.setDrawColor(1);
    u8g2.drawBox(73, mainObj->selectBoxYcode, 6, 14); // 滚动遮盖
#endif
    /*-------位置滑条提示--------*/
    mainObj->listSlider();
    u8g2.setDrawColor(1);
    u8g2.drawBox(80, mainObj->itemSliderOffset * mainObj->itemSliderZoomRatio + 14,
                 3, mainObj->itemSliderZoomRatio * 8);

    /****************************/
    u8g2.sendBuffer();
}
