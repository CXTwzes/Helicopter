#ifndef __GAME_BEGIN_H__
#define __GAME_BEGIN_H__
#pragma once
#include "cocos2d.h"
class GameBegin:public cocos2d::Layer
{
public:
	GameBegin();
	~GameBegin();
	static cocos2d::Scene * createScene();
	bool init();
	void startGame();
	CREATE_FUNC(GameBegin);
};

#endif