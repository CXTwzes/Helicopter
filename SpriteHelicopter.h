#ifndef __SPRITE_HELICOPTER_H__
#define __SPRITE_HELICOPTER_H__
#pragma once
#include "cocos2d.h"
//直升机的两种状态
typedef enum ActionState
{
	ACTION_STATE_IDLE,					//空闲状态
	ACTION_STATE_FLY,					//飞行状态
	ACTION_STATE_DIE					//死亡状态
};

class SpriteHelicopter :public cocos2d::Layer
{
public:
	SpriteHelicopter();
	~SpriteHelicopter();
	static SpriteHelicopter * createHelicopter();
	//状态转换函数
	void changeState(ActionState);
	//转换成飞行状态
	void stateFly();
	//转换成空闲状态
	void stateIdle();
	//转换成死亡状态
	void stateDie();
	bool init();
	void update(float);
	static SpriteHelicopter * getInstance();
	CREATE_FUNC(SpriteHelicopter);
private:
	//直升机精灵
	cocos2d::Sprite * sprite_helicopter;
	//当前状态
	ActionState helicopter_state;
	//侦听对象
	cocos2d::EventListenerTouchOneByOne * listener;
	

};
#endif
