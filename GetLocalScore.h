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
	//判断是否存在本地文件
	bool isHaveLocalFile();
	//获取本地文件中的分数
	int getHighScore();
	//写入本地文件分数
	void setHighScore(int);
private:

};
#endif