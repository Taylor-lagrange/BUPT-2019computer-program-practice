//作者：王宇航

#include"all.h"
void initialize() //初始化的函数
{
	queue_create(&mission_queue);
	innitial_map();
	add_deliver();
	return;
}