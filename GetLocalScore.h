#ifndef __GET_LOCAL_SCORE_H__
#define __GET_LOCAL_SCORE_H__
#pragma once
#include "cocos2d.h"
class GetLocalScore
{
public:
	GetLocalScore();
	~GetLocalScore();
	static GetLocalScore * getInstance();
	//�ж��Ƿ���ڱ����ļ�
	bool isHaveLocalFile();
	//��ȡ�����ļ��еķ���
	int getHighScore();
	//д�뱾���ļ�����
	void setHighScore(int);
private:

};
#endif