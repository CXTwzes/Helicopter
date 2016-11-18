#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#pragma once
#include "cocos2d.h"
#include "SpriteHelicopter.h"

class GameLayer :public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	static cocos2d::Scene * createScene();
	bool init();
	//��Ϸ��ʼ
	void startGame();

	CREATE_FUNC(GameLayer);
private:
	SpriteHelicopter * helicopter; 
	//������ײ����
	cocos2d::EventListenerPhysicsContact * contactListener;
};
#endif
