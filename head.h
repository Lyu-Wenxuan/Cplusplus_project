//豌豆射手左右转图片不变 BOSS投射的石头与普通僵尸相同 豌豆射手和僵尸为boat类 豌豆和石头为bullet类
#define _CRT_SECURE_NO_WARNINGS

#undef UNICODE //防止乱码
#undef _UNICODE //防止乱码

#pragma once
//头文件包含
#include <stdio.h> 
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>

#pragma comment( lib, "MSIMG32.LIB")

#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0) //获取键盘按键状态的宏定义

/* 为提高代码可读性,以下为游戏属性数值的宏定义 */

//相关游戏对象图像的高度, 单位为像素
#define High_Background 600
#define High_Text 24
#define High_Peashooter_up 87
#define High_Peashooter_left 87
#define High_Peashooter_right 87
#define High_Zombie 68
#define High_Pea 50
#define High_Stone 35
#define High_Boss 70

//豌豆射手和僵尸发射时位置的偏移
#define Offset_x_peashooter 32
#define Offset_y_peashooter -32
#define Offset_x_zombie 40
#define Offset_y_zombie 50

//相关游戏对象图像的宽度, 单位为像素
#define Width_Background 450
#define Width_Text 12
#define Width_Peashooter_up 79
#define Width_Peashooter_left 54
#define Width_Peashooter_right 54
#define Width_Zombie 100
#define Width_Pea 50
#define Width_Stone 35
#define Width_Boss 50

//产生相关游戏对象的最小时间间隔
#define Gap_if_generate_zombie 2
#define Gap_if_generate_stone 0.8
#define Gap_if_generate_pea 0.4
#define Boss_bullet_one 1
#define Boss_bullet_two 2
#define Boss_bullet_the 3

//相关游戏对象图像文件的路径
#define Image_peashooter_up "res/peashooter.png"
#define Image_peashooter_left "res/peashooter.png"
#define Image_peashooter_right "res/peashooter.png"
#define Image_zombie "res/zombie.png"
#define Image_pea "res/pea.png"
#define Image_stone "res/stone.png"
#define Gameing_background "res/backdrop.jpg"
#define Image_boss "res/boss.png"

//一些初始化值
#define Init_HP 10
#define Init_Boss_HP 10
#define Init_HP_zombie 1
#define My_peashooter_location_x Width/2
#define My_peashooter_location_y High
#define Init_scores 0
#define Init_zombie 0

//豌豆射手、僵尸和各自发射“子弹”的速度,单位为像素
#define Speed_peashooter 5
#define Speed_zombie 1
#define Speed_Bullet 3

#define Self 0
#define Enemy 1

#define Bullet_Type_Red 0
#define Bullet_Type_Golden 1
#define Bullet_Type_Bule 2

//相关游戏对象数量的最大值
#define MAX_zombie 4
#define MAX_stone 10 //change 15 to 10
#define MAX_enemy_wrecked 10

#define EXISTED 1
#define noEXISTED 0
#define COLLIDED 1
#define noCOLLIDED 0


//在游戏画面显示相关图像
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{

	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

//点,属性有横纵坐标
struct Point {
	int x;
	int y;
};

//“子弹”属性
struct Bullet
{
	char image[20];//图像文件路径
	int type;//“子弹”类型
	bool if_existed;//是否存在
	bool faction;//阵营, Self代表我方, Enemy代表敌方
	struct Point p; //“子弹”图像左上角的点在游戏界面的位置, 用于确定“子弹”的位置
	int high; //高度
	int width;//宽度
	struct Point direction_p;//“子弹”移动的最终位置

	struct Bullet* last;//链表相关属性
	struct Bullet* next;//链表相关属性
};

//Boat属性
struct Boat {
	bool if_existed;//是否存在
	char image[20];//图像文件路径
	int HP;//生命值
	double times_fired[3];//上三次发射“子弹”的时间
	double time_invincibility_started;//开始无敌的时间点
	bool if_collided;//是否发生碰撞
	bool faction;//阵营
	struct Point p;//Boat图像左上角的点在游戏界面的位置, 用于确定Boat的位置
	int high;//高度
	int width;//宽度
	struct Point direction_p;//Boat移动的最终位置

	struct Boat* last;
	struct Boat* next;
};

//BOSS的属性
struct Boss
{
	bool if_existed;//是否存在
	char image[20];//图像文件路径
	int HP;//生命值
	double times_fired_bullet1;//1类子弹上次开火的时间
	double times_fired_bullet2;//2类子弹上次开火的时间
	double times_fired_bullet3;//3类子弹上次开火的时间
};

//全局属性
struct Global_attribute
{
	double time; //从游戏开始到现在的时间
	int scores;//得分 待fix
	int number_zombie;//击毁的僵尸
	int myHP;//豌豆射手生命值
	int bossHP;//BOSS生命值
	int stone_from_zombie;//僵尸已投射的石头数量
	struct Point range_p1, range_p2;//通过左上角和右下角的两个点限定游戏界面的范围
	double time_last_generate_zombie;//上次产生僵尸的时间
};

//输入按键属性, 用于保持输入结果
struct Input_attribute
{
	int if_up;//是否向上
	int if_down;//是否向下
	int if_left;//是否向左
	int if_right;//是否向右
	int if_fire;//是否发生“子弹”
	int if_exit;//是否退出
	int Illegal_inputs;//非法输入
};

//背景属性, 用于实现背景卷动功能
struct Background
{
	bool if_existed;
	char image[20];
	struct Point p;//背景图像左上角点的位置,用于实现背景卷动功能
};
