//���ߣ����

#include"all.h"
void initialize() //��ʼ���ĺ���
{
	queue_create(&mission_queue);
	innitial_map();
	add_deliver();
	return;
}