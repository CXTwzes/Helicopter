#ifndef __WALL_LAYER_H__
#define __WALL_LAYER_H__
#pragma once
#include "cocos2d.h"

class WallLayer :public cocos2d::Layer
{
public:
	WallLayer();
	~WallLayer();
	bool init();
	//���һ���ƶ�����Ϲܵ�
	void addWall(float);
	//ǽ�ƶ�������Ļص�����
	void wallMoveOver(cocos2d::Ref *);
	//ǽֹͣ�ƶ�
	void stopWall();
	//��ʱ��ִ�к���
	void update(float);
	//ǽ��ʼ�ƶ�
	void startWall();

	CREATE_FUNC(WallLayer);
private:
	//�ܵ�����
	cocos2d::Array * wall_arr1;
	cocos2d::Array * wall_arr2;
	float wall_left_speed;      //ǽ�����ٶ�
	float wall_upanddown_speed;   //ǽ�����ƶ��ٶ�
	int random;            //�����
	int Wall_Range;        //ǽ�ƶ��ķ�Χ
	bool btn;
};
#endif

