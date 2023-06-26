/*
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-22 16:11:57
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-06-26 22:12:57
 * @FilePath: /Menu_SSD1327_S3/menu_obj.cpp
 * @Description:
 */
#include "menuObj.h"
#include "timer.h"
#define DEBUG 0

extern int START_POS_X;
extern int START_POS_Y;
extern int itemOffsetPosX;
extern int itemOffsetPOSY;
// extern void timerReset();

enum ItemType itemtype;

enum ScrollDir
{
    clockwise = 0,
    anticlockwise = 1
} scrollDir;

// TODO:把全局变量放到工作类内

bool endAlert = false;
int mainFun::strOffset = 0;
bool mainFun::strScrollDir = clockwise;
int mainFun::strScrollMaskLength = 0;
String mainFun::currentKeyLebel = "root";
String mainFun::absolutePath = "root";

baseItem::baseItem()
{
    x = 0;
    y = 10;
    itemText = "NULL yet";
    itemKey = "NULL";
    level = 0;
    hide = false;
    type = label;
}

/**
 * @description: 列表项，动态位置
 * @param {int} x
 * @param {int} y
 * @param {String} key
 * @param {String} text
 * @param {bool} hide
 * @param {int} level
 * @param {int} type
 * @param {String} commit
 * @param {String} father
 * @return {*}
 */
listItem::listItem(int sortId, String key, String text, bool hide, int level, int type, String commit, String father)
{
    this->x = START_POS_X + itemOffsetPosX + 10;
    this->y = START_POS_Y + itemOffsetPOSY + (sortId + 1) * 14;
    this->itemKey = key;
    this->itemText = text;
    this->hide = hide;
    this->level = level;
    this->type = type;
    this->commit = commit;
    this->father = father;
    this->haveSon = false;
}

/**
 * @description: 静态标签，位置固定
 * @param {int} x
 * @param {int} y
 * @param {String} key
 * @param {String} text
 * @param {bool} hide
 * @param {int} level
 * @param {int} type
 * @return {*}
 */
labelItem::labelItem(int x, int y, String key, String text, bool hide, int level, int type)
{
    this->x = x;
    this->y = y;
    this->itemKey = key;
    this->itemText = text;
    this->hide = hide;
    this->level = level;
    this->type = type;
}

void mainFun::registerItem(baseItem *ptr)
{
    regTable.insert(pair<String, baseItem *>(ptr->itemKey, ptr));
}

void mainFun::unregisterItem(String itemKey)
{
    regTable.erase(itemKey);
}

void mainFun::updateYCodeRange()
{
    regTableYCodeMax = 0;
    regTableYCodeMin = 100;
    std::map<String, baseItem *>::iterator it;
    for (it = regTable.begin(); it != regTable.end(); it++)
    {
        // 只处理main list，其他不动
        if ((it->second->level == currentLevel) && (it->second->type == list))
        {
            if (regTableYCodeMax < it->second->y)
            {
                regTableYCodeMax = it->second->y;
            }
            if (regTableYCodeMin > it->second->y)
            {
                regTableYCodeMin = it->second->y;
            }
        }
    }
}

void mainFun::updateCoordinate(bool direction)
{
    Serial.printf("Min = %d, Max = %d\n", regTableYCodeMin, regTableYCodeMax);
    if ((direction == 0) && (regTableYCodeMin > 20)) // 列表下移
    {
        endAlert = true;
        return;
    }
    if ((direction == 1) && (regTableYCodeMax < 130))
    {
        // 添加尾部提示
        endAlert = true;
        return;
    }

    /*----------刷新------------*/
    std::map<String, baseItem *>::iterator it;

    if (direction == 0) // 列表下移，选项向条上走
    {
        for (it = regTable.begin(); it != regTable.end(); it++)
        {
            if (it->second->type == list)
            {
                it->second->y += 14;
                if (it->second->y > 20)
                {
                    it->second->hide = false;
                }
            }
        }
        itemSliderOffset--;
        updateYCodeRange();
#if DEBUG
        Serial.printf("itemSliderOffset-- = %d\n", itemSliderOffset);
#endif
    }

    if (direction == 1) // 列表上移，选项向条下走
    {
        for (it = regTable.begin(); it != regTable.end(); it++)
        {
            if (it->second->type == list)
            {
                it->second->y -= 14;
                if (it->second->y < 20)
                {
                    it->second->hide = true;
                }
            }
        }
        itemSliderOffset++;
        updateYCodeRange();
#if DEBUG
        Serial.printf("itemSliderOffset++ = %d\n", itemSliderOffset);
#endif
    }
}

#if 0
/**
 * @description: 更新箭头位置,注意0,1可能有些混乱
 * @param {bool} direction :0 = up; 1 = down
 * @return {*}
 */
void mainFun::updateArrow(bool direction)
{
    int codeY = this->regTable.find("selectArrow")->second->y;
    if (!direction) // up, 0
    {
        // 尺寸间距以及步进，暂时没有修改的必要，直接写死
        if (codeY > 28)
        {
            codeY -= 14;
        }
        else
        {
            this->updateCoordinate(direction);
        }
    }
    if (direction) // down, 1
    {
        if (codeY < 126)
        {
            codeY += 14;
        }
        else
        {
            this->updateCoordinate(direction);
        }
    }
    this->regTable.find("selectArrow")->second->y = codeY;
}
#endif

/**
 * @description: 反色选择框
 * @param {bool} direction
 * @return {*}
 */
void mainFun::updateSelectionBox(bool direction)
{
    if (!direction) // up, 0
    {
        // 尺寸间距以及步进，暂时没有修改的必要，直接写死
        if (SelectBoxYcode > SeleceBoxStart)
        {
            SelectBoxYcode -= 14;
        }
        else
        {
            this->updateCoordinate(direction);
        }
    }

    if (direction) // down, 1
    {

        if (SelectBoxYcode < min(regTableYCodeMax - 14, 112)) //+14因为字符串与box的定位点不一样
        {

            SelectBoxYcode += 14;
        }
        else
        {

            this->updateCoordinate(direction);
        }
    }
    baseItem *temp = getCurrentSelect();
    if (temp != nullptr)
    {
        Serial.printf("Current Select = %s\n", temp->itemKey.c_str());
    }
}

/**
 * @description: 菜单位置滚动条
 * @return {*}
 */
void mainFun::listSlider()
{
    int itemSum = 0;
    int rate = 0;
    std::map<String, baseItem *>::iterator it;
    for (it = regTable.begin(); it != regTable.end(); it++)
    {
        if ((it->second->type == list) && (it->second->level == currentLevel))
        {
            itemSum++;
        }
    }
    itemSliderZoomRatio = (114 / itemSum);
}

/**
 * @description: 返回当前光标所在的选项
 * @return {*}
 */
baseItem *mainFun::getCurrentSelect()
{
    std::map<String, baseItem *>::iterator it;
    for (it = regTable.begin(); it != regTable.end(); it++)
    {
        // 只处理main list，其他不动
        if ((it->second->level == currentLevel) &&
            (it->second->type == list) &&
            (SelectBoxYcode + (28 - SeleceBoxStart + 1) > it->second->y) &&
            (SelectBoxYcode + (28 - SeleceBoxStart - 1) < it->second->y)) // 让box的y坐标夹逼，判断选的谁
        {
            return it->second;
        }
    }
    return nullptr;
}

void mainFun::confirmItem()
{
    baseItem *temp = getCurrentSelect();
    int subStrStartPos = 0;
    if (temp != nullptr)
    {
        if (temp->itemKey == "..")
        {
            // subStrStartPos = this->absolutePath.
            this->absolutePath = "/" + temp->itemKey;
            this->currentKeyLebel = temp->itemKey;
        }
        else
        {
            this->absolutePath = "/" + temp->itemKey;
            this->currentKeyLebel = temp->itemKey;
        }
    }
}

/**
 * @description: 动态裁减字符串，辅助字符串滚动
 * @return {*}
 */
#if 1
String mainFun::cutStr(String input, int maxStrDispLength)
{
    String temp = input.substring(0, this->strScrollMaskLength + maxStrDispLength + 1);
    if (this->strOffset % 5 == 0)
    {
        if (this->strScrollDir == clockwise)
        {
            this->strScrollMaskLength++;
        }
        else if (this->strScrollDir == anticlockwise)
        {
            this->strScrollMaskLength--;
        }
    }
#if 0
    Serial.printf("Offset = %d , maxOffset = %d ,Substr =%s\n",this->strOffset, this->strScrollMaskLength, temp.c_str());
#endif
    return temp;
}
#endif

/**
 * @description: 这里offset两端的值会多循环一次，本是bug，但是恰好实现了字符串换向前的停顿效果
 * @param {String} input
 * @param {int} maxStrDispLength
 * @return {*}
 */
void mainFun::scrollStr(String input, int maxStrDispLength)
{
    int strLengthPix = u8g2.getStrWidth(input.c_str()) + 10; // 12是字符像素宽度
    int maxOffset = strLengthPix - maxStrDispLength * 5;

    if (this->strScrollDir == clockwise && this->strOffset < maxOffset)
    {
        this->strOffset++;
    }
    else if (this->strScrollDir == anticlockwise && 0 <= this->strOffset)
    {
        this->strOffset--;
    }

    if (this->strOffset >= maxOffset || this->strOffset < 0)
    {
        if (this->strScrollDir == clockwise)
        {
            this->strOffset--; // 多加了一次， -1才能回到上边的循环
        }
        else if (this->strScrollDir == anticlockwise)
        {
            this->strOffset++; // 多减一次成负数了，+1才能回到上边的循环
        }
        this->strScrollDir = !this->strScrollDir;
    }
#if 0
    Serial.printf("Offset = %d , maxOffset = %d\n", this->strOffset, maxOffset);
#endif
}

void mainFun::resetStrOffset()
{
    this->strOffset = 0;
    this->strScrollDir = clockwise;
    this->strScrollMaskLength = 0;
}

/**
 * @description: 主列表绘制
 * @todo:参考子列表绘制函数，本地更新y坐标，去掉构造函数里的sortId
 * @return {*}
 */
void mainFun::displayMainItem()
{
    int maxStrDispLength = 12;
    int finalX = 0;
    std::map<String, baseItem *>::iterator it;
    for (it = regTable.begin(); it != regTable.end(); it++)
    {
        if ((!it->second->hide) && (it->second->level == currentLevel))
        {
            // 处理超长字符串
            String temp;
            if (it->second->itemText.length() > maxStrDispLength)
            {
                if (it->first == this->getCurrentSelect()->itemKey && this->startScroll)
                {
                    // 超长选中
                    temp = cutStr(it->second->itemText, maxStrDispLength);
                    scrollStr(it->second->itemText, maxStrDispLength);
                    finalX = 10 - this->strOffset;
                    u8g2.setCursor(finalX, it->second->y);
                }
                else
                {
                    // 超长非选中
                    temp = it->second->itemText.substring(0, maxStrDispLength);
                    temp += "...";
                    u8g2.setCursor(it->second->x, it->second->y);
                }
            }
            else
            {
                temp = it->second->itemText; // 正常字符串
                u8g2.setCursor(it->second->x, it->second->y);
            }

            u8g2.print(temp);

            /*----------- 处理有子菜单的项目 -------------*/
            if (it->second->type == list && it->second->getSonFlg())
            {
                u8g2.drawStr(it->second->x + 64, it->second->y, ">");
            }
#if DEBUG
            Serial.println("-----------------------------");
            Serial.printf("x = %d, y = %d\n", it->second->x, it->second->y);
            Serial.println(it->second->itemKey);
            Serial.println(it->second->itemText);
            Serial.println("-----------------------------");
#endif
        }
    }
}

/**
 * @description: 显示子菜单
 * @todo: 顺序显示，当前是随机
 * @return {*}
 */
void mainFun::displaySubItem()
{
    int subMenuX = 90;
    int subMenuY = 28;
    int sum = 0;
    int maxLengthStr = 6;
    std::map<String, baseItem *>::iterator it;
    for (it = regTable.begin(); it != regTable.end(); it++)
    {
        if ((!it->second->hide) &&
            (it->second->level == currentLevel + 1) &&
            (it->second->getFather() == getCurrentSelect()->itemKey))
        {
            u8g2.setCursor(subMenuX, subMenuY + sum * 14);

            // 超长字符串
            String temp;
            if (it->second->itemText.length() > maxLengthStr)
            {
                temp = it->second->itemText.substring(0, maxLengthStr);
                temp += "...";
            }
            else
            {
                temp = it->second->itemText;
            }
            u8g2.print(temp);
            sum++;
        }
    }
}

void mainFun::showAllRegTable()
{
    std::map<String, baseItem *>::iterator it;
    for (it = regTable.begin(); it != regTable.end(); it++)
    {
        if (it->second->type == list)
        {
            Serial.println("----------------------------------");
            Serial.printf("cood x = %d, y = %d\n", it->second->x, it->second->y);
            Serial.printf("itemKey = %s, itemText = %s\n", it->second->itemKey.c_str(), it->second->itemText.c_str());
            Serial.printf("hide = %d, level = %d, type = %d\n", it->second->hide, it->second->level, it->second->type);
            Serial.printf("father = %s\n", it->second->getFather().c_str());
            Serial.printf("have son = %d\n", it->second->getSonFlg());
        }
    }
}