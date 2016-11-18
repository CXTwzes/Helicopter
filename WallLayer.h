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
	//添加一个移动的组合管道
	void addWall(float);
	//墙移动结束后的回调函数
	void wallMoveOver(cocos2d::Ref *);
	//墙停止移动
	void stopWall();
	//计时器执行函数
	void update(float);
	//墙开始移动
	void startWall();

	CREATE_FUNC(WallLayer);
private:
	//管道数组
	cocos2d::Array * wall_arr1;
	cocos2d::Array * wall_arr2;
	float wall_left_speed;      //墙左移速度
	float wall_upanddown_speed;   //墙上下移动速度
	int random;            //随机数
	int Wall_Range;        //墙移动的范围
	bool btn;
};
#endif

