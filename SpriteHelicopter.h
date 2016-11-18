#ifndef __SPRITE_HELICOPTER_H__
#define __SPRITE_HELICOPTER_H__
#pragma once
#include "cocos2d.h"
//ֱ����������״̬
typedef enum ActionState
{
	ACTION_STATE_IDLE,					//����״̬
	ACTION_STATE_FLY,					//����״̬
	ACTION_STATE_DIE					//����״̬
};

class SpriteHelicopter :public cocos2d::Layer
{
public:
	SpriteHelicopter();
	~SpriteHelicopter();
	static SpriteHelicopter * createHelicopter();
	//״̬ת������
	void changeState(ActionState);
	//ת���ɷ���״̬
	void stateFly();
	//ת���ɿ���״̬
	void stateIdle();
	//ת��������״̬
	void stateDie();
	bool init();
	void update(float);
	static SpriteHelicopter * getInstance();
	CREATE_FUNC(SpriteHelicopter);
private:
	//ֱ��������
	cocos2d::Sprite * sprite_helicopter;
	//��ǰ״̬
	ActionState helicopter_state;
	//��������
	cocos2d::EventListenerTouchOneByOne * listener;
	

};
#endif
