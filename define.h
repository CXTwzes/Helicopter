#ifndef __DEFINE_H__
#define __DEFINE_H__
#pragma once

#define HELICOPTERANIMATION						        "helicopterAnimation"					//直升机动画
#define HELICOPTER_FRE									0.05f									//直升机旋转频率
#define LOADING_NUM										2										//loading 动画次数
#define LOADING_FRE										0.5f									//loading 动画频率
#define GRAVITY											Point(0,-980)							//重力加速度
#define VELOCITY										Point(0,350)							//点击向上飞速度
#define THROUGH_HEIGHT									160									    //通过两个墙子间的缝隙
#define WALL_UP											1									    //向上墙的tag
#define WALL_DOWN										2									    //向下墙的tag
#define WALL_X											320									    //墙开始移动的X值
#define WALL_Y											-270									//墙开始移动的最小Y值
#define WALL_TIME										3.6f									//墙运动的时间
#define HELICOPTER_DIE_ROTATION							90										//直升机死亡后的角度
#define SCORECARD_SHOW_TIME								0.3f									//计分板出现动画时间
#define ADDSCORE_FRE									0.05f									//加分频率
#define CHANGESCENE_TIME								0.5f									//场景切换时间
#define LAYER                                          "layer.png"                              //场景名称

#endif