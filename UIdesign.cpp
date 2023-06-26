/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-22 23:21:36
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-26 21:26:56
 * @FilePath: /Menu_SSD1327_S3/UI_design.hpp
 * @Description:
 */
#include "UIdesign.h"
#define DEBUG 0
#define ListInit_TEST 0
int START_POS_X = 0; // 起始位置
int START_POS_Y = 0;

int itemOffsetPosX = 0; // 列表偏移
int itemOffsetPOSY = 0;

extern enum ItemType itemtype;
extern mainFun *mainObj;

/**
 * @description: 该函数只是定义一个初始布局，可以添加任何项目，坐标
 * @return {*}
 */
void listInit()
{
    /*-------标题栏--------*/
    baseItem *time = new labelItem(0, 12, "time", "21:34", false, 0, label);
    mainObj->registerItem(time);

    baseItem *headLine = new labelItem(50, 12, "headLine", "It's title", false, 0, label);
    mainObj->registerItem(headLine);

    baseItem *level = new labelItem(115, 12, "level", "L0", false, 0, label);
    mainObj->registerItem(level);

    /*-------菜单 L0-------*/
    /*-----------------------------(sortId, key,     val,       hide,level,type,commit, father)*/
    baseItem *item_L0_1 = new listItem(1, "item_L0_1", "List item 1", false, 0, list, "NULL", "NULL"); // sortId是列表位置排序，必须连续，不同层级可以重复
    mainObj->registerItem(item_L0_1);

    baseItem *item_L0_2 = new listItem(2, "item_L0_2", "List item 2", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_2);

    baseItem *item_L0_3 = new listItem(3, "item_L0_3", "List item 3", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_3);

    baseItem *item_L0_4 = new listItem(4, "item_L0_4", "List item 4 test long string", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_4);

    baseItem *item_L0_5 = new listItem(5, "item_L0_5", "List item 5", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_5);

    baseItem *item_L0_6 = new listItem(6, "item_L0_6", "List item 6 test long string", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_6);

    baseItem *item_L0_7 = new listItem(7, "item_L0_7", "List item 7", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_7);

    baseItem *item_L0_8 = new listItem(8, "item_L0_8", "List item 8", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_8);

    baseItem *item_L0_9 = new listItem(9, "item_L0_9", "List item 9", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_9);

    baseItem *item_L0_10 = new listItem(10, "item_L0_10", "List item 10", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_10);

    baseItem *item_L0_11 = new listItem(11, "item_L0_11", "List item 11", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_11);

    baseItem *item_L0_12 = new listItem(12, "item_L0_12", "List item 12", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_12);

    baseItem *item_L0_13 = new listItem(13, "item_L0_13", "List item 13", false, 0, list, "NULL", "NULL");
    mainObj->registerItem(item_L0_13);

    /*-------菜单 L1-------*/
    baseItem *item_L1_1 = new listItem(1, "item_L1_1", "Sub item_L1_1", false, 1, list, "NULL", "item_L0_3");
    mainObj->registerItem(item_L1_1);

    baseItem *item_L1_2 = new listItem(2, "item_L1_2", "Sub item_L1_2", false, 1, list, "NULL", "item_L0_3");
    mainObj->registerItem(item_L1_2);

    baseItem *item_L1_3 = new listItem(2, "item_L1_3", "Sub item_L1_3", false, 1, list, "NULL", "item_L0_3");
    mainObj->registerItem(item_L1_3);

    baseItem *item_L1_4 = new listItem(2, "item_L1_4", "Sub item_L1_4", false, 1, list, "NULL", "item_L0_3");
    mainObj->registerItem(item_L1_4);

    baseItem *item_L1_5 = new listItem(2, "item_L1_5", "Sub item_L1_5", false, 1, list, "NULL", "item_L0_3");
    mainObj->registerItem(item_L1_5);

    baseItem *item_L1_6 = new listItem(2, "item_L1_6", "Sub item_L1_6", false, 1, list, "NULL", "item_L0_3");
    mainObj->registerItem(item_L1_6);

    /*-------菜单 L2-------*/

    /*-------其他-------*/
    // baseItem *selectArrow = new labelItem(START_POS_X + 2, START_POS_Y + 28, "selectArrow", ">", false, 0, label);
    // mainObj->registerItem(selectArrow);
    updateSubInfo();
    mainObj->updateYCodeRange();
    // mainObj->showAllRegTable();
}

/**
 * @description: 这里算法稀烂，复杂度大概n^2，但只会执行一次
 * @return {*}
 */
void updateSubInfo()
{
    String temp;
    std::map<String, baseItem *>::iterator it;
    for (it = mainObj->regTable.begin(); it != mainObj->regTable.end(); it++)
    {
        // 只处理main list，其他不动
        if (it->second->type == list)
        {
            temp = it->second->getFather();
            if (temp != "NULL")
            {
                mainObj->regTable.find(temp)->second->setSonFlg();
            }
        }
    }
}