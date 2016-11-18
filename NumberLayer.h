//NumberLayer.h
#ifndef __NUMBER_LAYER_H__
#define __NUMBER_LAYER_H__
#pragma once
#include "cocos2d.h"
class NumberLayer:public cocos2d::Layer
{
public:
	NumberLayer();
	~NumberLayer();
	bool init();
	//�ӷ�
	void addScore();
	//��ʼ������
	void initScore();
	//��÷���
	int getScore();
	//��õ�������
	static NumberLayer * getInstance();

private:
	cocos2d::Label * numberLabel;
	int score;
};

#endif