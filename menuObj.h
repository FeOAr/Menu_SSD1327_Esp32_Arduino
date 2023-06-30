/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-22 13:44:42
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-30 20:17:41
 * @FilePath: /Menu_SSD1327_S3/menu_obj.h
 * @Description:
 */
#ifndef _MENUOBJ_H
#define _MENUOBJ_H

#include <map>
#include <U8g2lib.h>
#include <string>

using namespace std;

extern U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2;
#define seleceBoxStart 17 // select box的起始高低位置

enum ItemType
{
    label = 1,
    list
};

/*-------------base class-------------*/
class baseItem
{
public:
    int x;
    int y;
    string itemText;
    string itemKey;
    bool hide;
    int level;
    int type;

public:
    baseItem();
    virtual string getCommit(){};
    virtual string getFather(){};
    virtual bool getSonFlg(){};
    virtual void setSonFlg(){};
};

/*-------------listItem-------------*/
class listItem : public baseItem
{
public:
    string commit;
    string father; // 指向父条目,直接使用 itemKey
    bool haveSon;  // 是否有子菜单

public:
    listItem(int, string, string, bool, int, int, string, string);
    string getCommit() { return commit; };
    string getFather() { return father; };
    bool getSonFlg() { return haveSon; };
    void setSonFlg() { haveSon = true; };
};

class labelItem : public baseItem
{
public:
    labelItem(int, int, string, string, bool, int, int);
};

/*-------------Main function-------------*/
class mainFun
{
public: // 应该私有
    // 该表存了所有的标签，所以无法排序，导致有一些操作较繁琐
    std::map<string, baseItem *> regTable; // 考虑使用 shared_ptr,
    int selectBoxYcode = seleceBoxStart;   // 选择框的y坐标，注意：selectBoxYcode坐标错误极易导致异常，因为需要通过当前值计算选择项
    static int lastSelectBoxYcode[20];     // 存储进入之前所在的位置
    int regTableYCodeMax;
    int regTableYCodeMin;
    int currentLevel = 0;
    int itemSliderOffset = 0;
    int itemSliderZoomRatio = 0;
    static int strOffset;
    static bool strScrollDir;       // 字符串滚动方向
    static int strScrollMaskLength; // 字符串滚动遮罩长度
    bool startScroll = false;
    static string currentKeyLebel; // 显示所有条目依赖的索引
    static string absolutePath;    // 所有操作依赖的完整路径

public:
    void registerItem(baseItem *);
    void unregisterItem(string);
    void updateYCodeRange();
    void updateCoordinate(bool);
    void updateArrow(bool);
    void updateSelectionBox(bool);
    void listSlider();
    baseItem *getCurrentSelect();
    void displayMainItem();
    void displaySubItem();
    void showAllRegTable();
    string cutStr(string, int);
    void scrollStr(string, int);
    void resetStrOffset();
    void resetDispPrameter(bool);

    void confirmItem();

    void setScrollFlg(bool status) { startScroll = status; }
    bool getScrollFlg() { return startScroll; }
};

#endif