//作者：蒋明君

#include"all.h"


void mission_allocate(mission dispose)  
{
	int weight[100];
	int index = 0;// rand() % num_deliver_man;
	for (int i = 0; i < num_deliver_man; i++)
	{
		weight[i] = predict(dispose, deliver_man[i]);     //依据权重得出每位骑手的送单便捷程度
		index = (weight[i] < weight[index] ? i : index);  //得出最优骑手的下标
	}
	for (int i = 0; i < max_dispose; i++)
	{
		if (deliver_man[index].task[i].is_complete == 1)  //新订单替换掉空订单或已经完成的订单
		{
			deliver_man[index].task[i] = dispose;
			deliver_man[index].is_allocate_new = 1;   //状态更新
			deliver_man[index].num_mission += 2;
			break;
		}
	}
	return;
}