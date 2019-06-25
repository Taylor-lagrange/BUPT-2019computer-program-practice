//���ߣ�������

#include "all.h"
void state_update()
{
	num_iscompleting = 0;
	num_isovertiming = 0;
	memset(num_completing, -1, sizeof(num_completing));
	memset(num_overtiming, -1, sizeof(num_overtiming));
	for (int i = 0; i < num_deliver_man; i++)
	{
		for (int k = 0; k < deliver_man[i].num_mission / 2; k++)					
		{
			if ((time - deliver_man[i].task[k].order_time >= 60) && (deliver_man[i].task[k].is_complete != 1))
			{
				is_break = 1;
				break;
			}
		}
		if (is_break == 1) 
			break;
		if (deliver_man[i].index_misson > deep_dsf - 2)
			order_dispose(i);
		deliver_man[i].stopflag1 = 0;
		deliver_man[i].stopflag2 = 0;
		if (deliver_man[i].num_mission == 0 || deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].is_complete == 1)//�����������Ѿ������������һ��
			continue;
		int aim_x = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal);//��������һ��ȡ�������͵���ȷ����x����
		int aim_y = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal);//��������һ��ȡ�������͵���ȷ����y����
		int arrive = 0;

		if (abs(deliver_man[i].x_location - aim_x) + abs(deliver_man[i].y_location - aim_y) == 1)//��1���������������պþ��ڿ��Ա����
		{
			arrive = 1;//��Ƕ�������
		}
		else if (deliver_man[i].x_location == 0 || deliver_man[i].x_location == 16)//�������굽�߽ǵ��������ʱ����û��ֱ�ӵ����Ҫһ��������У������
		{
			deliver_man[i].x_location == 0 ? deliver_man[i].x_location += 2 : deliver_man[i].x_location -= 2;
		}
		else if (deliver_man[i].y_location == 0 || deliver_man[i].y_location == 16)//�������굽�߽ǵ��������ʱ����û��ֱ�ӵ����Ҫһ��������У������
		{
			deliver_man[i].y_location == 0 ? deliver_man[i].y_location += 2 : deliver_man[i].y_location -= 2;
		}
		else if (abs(deliver_man[i].x_location - aim_x) == 1 || abs(deliver_man[i].y_location - aim_y) == 1)//��2�������ȡ�����͵���һ�����ϣ���������Ҫת�������ڵ������ͨ��һ��ת��Ĳ���
		{
			if (abs(deliver_man[i].x_location - aim_x) == 1)//x�����Ͽ��Ա��Ŀ���ͬ�򣬸ı�y����ƽ�Ŀ���
				deliver_man[i].y_location > aim_y ? deliver_man[i].y_location -= 2 : deliver_man[i].y_location += 2;
			else if (abs(deliver_man[i].y_location - aim_y) == 1)//y�����Ͽ��Ա��Ŀ���ͬ�򣬸ı�x����ƽ�Ŀ���
				deliver_man[i].x_location > aim_x ? deliver_man[i].x_location -= 2 : deliver_man[i].x_location += 2;

			if (abs(deliver_man[i].x_location - aim_x) + abs(deliver_man[i].y_location - aim_y) == 1)//��������ɺ󶩵�������arrive
				arrive = 1;//��Ƕ�������
		}
		else if (abs(deliver_man[i].x_location - aim_x) <= 2 || abs(deliver_man[i].y_location - aim_y) <= 2)//��3����������Ա��Ҫת�����ƽ�Ŀ�ĵ�
		{
			deliver_man[i].x_location >= aim_x ? deliver_man[i].x_location-- : deliver_man[i].x_location++;
			deliver_man[i].y_location >= aim_y ? deliver_man[i].y_location-- : deliver_man[i].y_location++;
		}
		else //��4����������Ա����ת�����ֱ�ӽӽ����ȱƽ�����
		{
			if (deliver_man[i].x_location % 2 == 0)
				deliver_man[i].x_location >= aim_x ? deliver_man[i].x_location -= 2 : deliver_man[i].x_location += 2;
			else
				deliver_man[i].y_location >= aim_y ? deliver_man[i].y_location -= 2 : deliver_man[i].y_location += 2;
		}
		if (arrive == 1)//����������͵���
		{
			while (abs(deliver_man[i].x_location - aim_x) + abs(deliver_man[i].y_location - aim_y) == 1)//Ϊ�˷�ֹ��ͬ��ʱ����ж������
			{

				int temp = ++put_matrix[aim_x][aim_y].count;//���������������Լ�
				put_matrix[aim_x][aim_y].deliver_man_i[temp] = i;//��¼���Ա��˭
				put_matrix[aim_x][aim_y].is_done[temp] = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? 0 : 1);//��¼��ȡ�������͵�
				put_matrix[aim_x][aim_y].num_deliver[temp] = deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].number;//��¼�������

				if (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0)//һ��ȡ���������
				{
					deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time = 1;
				}											
				else//�͵��������
				{
					deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].is_complete = 1;
					if (time - deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].order_time < dead_line)//�����ڹ涨ʱ�䱻�ʹ�
					{
						num_completing[num_iscompleting] = deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].number;
						num_iscompleting++;
						money += 10;
						deliver_music = 1;
						num_completed++;
						num_iscompleting++;
					}
					else  if (time - deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].order_time >= dead_line && time - deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].order_time <= total_dead_line)//������ʱ�������Ʋ�
					{
						num_overtiming[num_isovertiming] = deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].number;
						num_isovertiming++;
						money -= 40;
						num_overtime++;
						warn_music = 1;//���ų�ʱ����
					}
					else//�Ʋ�����
					{
						num_overtime++;
						is_break = 1;
						warn_music = 1;//���ų�ʱ����
					}

				}
				deliver_man[i].num_mission--, deliver_man[i].index_misson++;//��������1������ָ���1
				if (deliver_man[i].num_mission == 0 || deliver_man[i].mission_queue[deliver_man[i].index_misson] == -1 || deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].is_complete == 1)//���кü���������ʼ����ֹ��ͬ�����ж����ʱ����������������
					break;
				aim_x = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal);//������һ�����꣬�۲��Ƿ���һ���ص��кü�������
				aim_y = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal);
			}
		}
		add_deliver();
		if (money < 0)
			is_break = 1; //��Ǯ��<0�����Ʋ�
	}
}