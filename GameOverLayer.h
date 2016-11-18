#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__
#pragma once
#include "cocos2d.h"

class GameOverLayer:public cocos2d::Layer
{
public:
	GameOverLayer();
	~GameOverLayer();
	bool init();
	//回调函数
	void callBack();
	//再来一次
	void gameAgain();
	//结束游戏
	void gameOver();
	//显示分数
	void showScore(float);
	CREATE_FUNC(GameOverLayer);
private:
	//计分区域精灵
	cocos2d::Sprite * box;
	//最终分数label
	cocos2d::Label * numberLabel;
	int score;       //分数
	int highScore;  //最高分
};
#endif