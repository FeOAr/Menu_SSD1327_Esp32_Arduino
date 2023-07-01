<!--
 * @Author: feoar feoar@outlook.com
 * @Date: 2023-06-30 22:54:03
 * @LastEditors: feoar feoar@outlook.com
 * @LastEditTime: 2023-07-01 17:47:44
 * @FilePath: /Menu_SSD1327_S3/README.md
 * @Description: 
-->
# 概述
用C++的软件思想写了一个Menu，我的评价是思路过于迂回，其中因为依赖Mep容器导致非常多的地方需要不停遍历整个容器，十分低效，字符串处理也是非常的不优雅，总之会抽时间不断优化。

用户移植这个Menu只需要在UIdesign.cpp中的listInit()函数内根据规律添加条目即可。

# 预览
![预览](https://imgforfeoar-1312132618.cos.ap-shanghai.myqcloud.com/Blog_update/202307011745068.jpg)

# B站
[链接](https://www.bilibili.com/video/BV1Ph411A7j6)