//���ߣ�������

#include "all.h"
void solve()
{
	do
	{
		int flag = 0; //һ����Ǳ��������whileѭ���Ƿ����У��������Ƿ��������·���Ż�
		/*while (!queue_isempty(&mission_queue))
		{
			flag = 1;
			num_order++;  //�ӵ�����һ
			mission_allocate(*queue_top(&mission_queue));
			queue_pop(&mission_queue);  //����ͷԪ�س���
		}
		if (flag) //��flag==1���¹滮·��*/

		for (int i = 0; i < num_deliver_man; i++)
			if (deliver_man[i].is_allocate_new)
			{
					deliver_man[i].is_allocate_new = 0;
					order_dispose(i);
			}
		Sleep(2000);  //ÿ�α仯λ��ǰ���2s
		state_update();
		map_print();
		//print();ע�͵�print������output�ļ�
		if (is_break)
			break;
	} while (++time); //ÿ�θ���ʱ��,ע���ԼӲ���˳��
}
