//���ߣ�������

#include"all.h"


void mission_allocate(mission dispose)  
{
	int weight[100];
	int index = 0;// rand() % num_deliver_man;
	for (int i = 0; i < num_deliver_man; i++)
	{
		weight[i] = predict(dispose, deliver_man[i]);     //����Ȩ�صó�ÿλ���ֵ��͵���ݳ̶�
		index = (weight[i] < weight[index] ? i : index);  //�ó��������ֵ��±�
	}
	for (int i = 0; i < max_dispose; i++)
	{
		if (deliver_man[index].task[i].is_complete == 1)  //�¶����滻���ն������Ѿ���ɵĶ���
		{
			deliver_man[index].task[i] = dispose;
			deliver_man[index].is_allocate_new = 1;   //״̬����
			deliver_man[index].num_mission += 2;
			break;
		}
	}
	return;
}