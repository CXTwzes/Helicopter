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
	//加分
	void addScore();
	//初始化分数
	void initScore();
	//获得分数
	int getScore();
	//获得单例对象
	static NumberLayer * getInstance();

private:
	cocos2d::Label * numberLabel;
	int score;
};

#endif