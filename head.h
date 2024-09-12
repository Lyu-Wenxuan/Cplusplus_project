//�㶹��������תͼƬ���� BOSSͶ���ʯͷ����ͨ��ʬ��ͬ �㶹���ֺͽ�ʬΪboat�� �㶹��ʯͷΪbullet��
#define _CRT_SECURE_NO_WARNINGS

#undef UNICODE //��ֹ����
#undef _UNICODE //��ֹ����

#pragma once
//ͷ�ļ�����
#include <stdio.h> 
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>

#pragma comment( lib, "MSIMG32.LIB")

#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0) //��ȡ���̰���״̬�ĺ궨��

/* Ϊ��ߴ���ɶ���,����Ϊ��Ϸ������ֵ�ĺ궨�� */

//�����Ϸ����ͼ��ĸ߶�, ��λΪ����
#define High_Background 600
#define High_Text 24
#define High_Peashooter_up 87
#define High_Peashooter_left 87
#define High_Peashooter_right 87
#define High_Zombie 68
#define High_Pea 50
#define High_Stone 35
#define High_Boss 70

//�㶹���ֺͽ�ʬ����ʱλ�õ�ƫ��
#define Offset_x_peashooter 32
#define Offset_y_peashooter -32
#define Offset_x_zombie 40
#define Offset_y_zombie 50

//�����Ϸ����ͼ��Ŀ��, ��λΪ����
#define Width_Background 450
#define Width_Text 12
#define Width_Peashooter_up 79
#define Width_Peashooter_left 54
#define Width_Peashooter_right 54
#define Width_Zombie 100
#define Width_Pea 50
#define Width_Stone 35
#define Width_Boss 50

//���������Ϸ�������Сʱ����
#define Gap_if_generate_zombie 2
#define Gap_if_generate_stone 0.8
#define Gap_if_generate_pea 0.4
#define Boss_bullet_one 1
#define Boss_bullet_two 2
#define Boss_bullet_the 3

//�����Ϸ����ͼ���ļ���·��
#define Image_peashooter_up "res/peashooter.png"
#define Image_peashooter_left "res/peashooter.png"
#define Image_peashooter_right "res/peashooter.png"
#define Image_zombie "res/zombie.png"
#define Image_pea "res/pea.png"
#define Image_stone "res/stone.png"
#define Gameing_background "res/backdrop.jpg"
#define Image_boss "res/boss.png"

//һЩ��ʼ��ֵ
#define Init_HP 10
#define Init_Boss_HP 10
#define Init_HP_zombie 1
#define My_peashooter_location_x Width/2
#define My_peashooter_location_y High
#define Init_scores 0
#define Init_zombie 0

//�㶹���֡���ʬ�͸��Է��䡰�ӵ������ٶ�,��λΪ����
#define Speed_peashooter 5
#define Speed_zombie 1
#define Speed_Bullet 3

#define Self 0
#define Enemy 1

#define Bullet_Type_Red 0
#define Bullet_Type_Golden 1
#define Bullet_Type_Bule 2

//�����Ϸ�������������ֵ
#define MAX_zombie 4
#define MAX_stone 10 //change 15 to 10
#define MAX_enemy_wrecked 10

#define EXISTED 1
#define noEXISTED 0
#define COLLIDED 1
#define noCOLLIDED 0


//����Ϸ������ʾ���ͼ��
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{

	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// ʹ�� Windows GDI ����ʵ��͸��λͼ
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

//��,�����к�������
struct Point {
	int x;
	int y;
};

//���ӵ�������
struct Bullet
{
	char image[20];//ͼ���ļ�·��
	int type;//���ӵ�������
	bool if_existed;//�Ƿ����
	bool faction;//��Ӫ, Self�����ҷ�, Enemy����з�
	struct Point p; //���ӵ���ͼ�����Ͻǵĵ�����Ϸ�����λ��, ����ȷ�����ӵ�����λ��
	int high; //�߶�
	int width;//���
	struct Point direction_p;//���ӵ����ƶ�������λ��

	struct Bullet* last;//�����������
	struct Bullet* next;//�����������
};

//Boat����
struct Boat {
	bool if_existed;//�Ƿ����
	char image[20];//ͼ���ļ�·��
	int HP;//����ֵ
	double times_fired[3];//�����η��䡰�ӵ�����ʱ��
	double time_invincibility_started;//��ʼ�޵е�ʱ���
	bool if_collided;//�Ƿ�����ײ
	bool faction;//��Ӫ
	struct Point p;//Boatͼ�����Ͻǵĵ�����Ϸ�����λ��, ����ȷ��Boat��λ��
	int high;//�߶�
	int width;//���
	struct Point direction_p;//Boat�ƶ�������λ��

	struct Boat* last;
	struct Boat* next;
};

//BOSS������
struct Boss
{
	bool if_existed;//�Ƿ����
	char image[20];//ͼ���ļ�·��
	int HP;//����ֵ
	double times_fired_bullet1;//1���ӵ��ϴο����ʱ��
	double times_fired_bullet2;//2���ӵ��ϴο����ʱ��
	double times_fired_bullet3;//3���ӵ��ϴο����ʱ��
};

//ȫ������
struct Global_attribute
{
	double time; //����Ϸ��ʼ�����ڵ�ʱ��
	int scores;//�÷� ��fix
	int number_zombie;//���ٵĽ�ʬ
	int myHP;//�㶹��������ֵ
	int bossHP;//BOSS����ֵ
	int stone_from_zombie;//��ʬ��Ͷ���ʯͷ����
	struct Point range_p1, range_p2;//ͨ�����ϽǺ����½ǵ��������޶���Ϸ����ķ�Χ
	double time_last_generate_zombie;//�ϴβ�����ʬ��ʱ��
};

//���밴������, ���ڱ���������
struct Input_attribute
{
	int if_up;//�Ƿ�����
	int if_down;//�Ƿ�����
	int if_left;//�Ƿ�����
	int if_right;//�Ƿ�����
	int if_fire;//�Ƿ������ӵ���
	int if_exit;//�Ƿ��˳�
	int Illegal_inputs;//�Ƿ�����
};

//��������, ����ʵ�ֱ���������
struct Background
{
	bool if_existed;
	char image[20];
	struct Point p;//����ͼ�����Ͻǵ��λ��,����ʵ�ֱ���������
};
