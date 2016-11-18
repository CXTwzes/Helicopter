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
	//�ص�����
	void callBack();
	//����һ��
	void gameAgain();
	//������Ϸ
	void gameOver();
	//��ʾ����
	void showScore(float);
	CREATE_FUNC(GameOverLayer);
private:
	//�Ʒ�������
	cocos2d::Sprite * box;
	//���շ���label
	cocos2d::Label * numberLabel;
	int score;       //����
	int highScore;  //��߷�
};
#endif