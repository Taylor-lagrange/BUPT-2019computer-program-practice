#include "all.h"
void state()
{
	int location[2];			//����һ�����飬�����������Ա��һ��Ŀ��㡣��һ������Ϊx���꣬�ڶ�������Ϊy����
	deliver* cur;				//����һ��ָ���¼��ǰ���Ա��Ϣ
	missionptr m;				//����һ��ָ���¼��ǰ������Ϣ
	num_order = num_completed;  //�ýӵ����ȵ��ڵ�ǰ�����������һ��ͳ���ܽӵ���
	for (int i = 0; i < num_deliver_man; i++) //�����п��Ա���б���
	{
		cur = &deliver_man[i];
		for (int n = 0; n < max_dispose; n++)
		{
			if (cur->task[n].is_complete == 0)
				num_order++;
		} //��������;����ӵ�����һ
		if (cur->num_mission == 0)
			continue; //������Ա��ǰû�����������һ�����Ա���в���
		else
		{
			m = &(cur->task[deliver_man[i].mission_queue[deliver_man[i].index_misson]]);
			if (m->fetch_time == 0) //�����δȡ��
			{
				location[0] = m->x_start;
				location[1] = m->y_start;
			} //��Ŀ���Ϊ�ӵ���
			else
			{
				location[0] = m->x_terminal;
				location[1] = m->y_terminal;
			} //����Ŀ���Ϊ�͵���
			if (abs(location[0] - cur->x_location) <= 1) //�жϿ��Ա�������Ƿ��ѵ���Ŀ��㸽��
			{
				if (abs(location[1] - cur->y_location) <= 1) //�жϿ��Ա�������Ƿ��ѵ���Ŀ��㸽��
				{
					cur->index_misson++; //���ѵ���������һ������
					cur->num_mission--;  //��ǰ����������һ
					if (m->fetch_time == 0)
						m->fetch_time = time; //���������ȡ��������ǰʱ�伴Ϊȡ��ʱ��
					else
					{
						m->is_complete += 1; //����������͵��㣬�������ѱ����
						if (time - (m->order_time) <= dead_line)
						{
							money += 10;
							num_completed += 1;
						} //���͵�ʱ����30���ڣ����Ǯ��10���������1
						else if (time - (m->order_time) <= total_dead_line)
						{
							money -= 40;
							num_completed += 1;
							num_overtime += 1;
						} //��30-60֮��
						else if (time - (m->order_time) > total_dead_line)
						{
							is_break = 1;
						} //����60���Ʋ�
					}
					m = &(cur->task[deliver_man[i].mission_queue[deliver_man[i].index_misson]]);
					if (m->fetch_time == 0) //�����δȡ��
					{
						location[0] = m->x_start;
						location[1] = m->y_start;
					} //��Ŀ���Ϊ�ӵ���
					else
					{
						location[0] = m->x_terminal;
						location[1] = m->y_terminal;
					} //����Ŀ���Ϊ�͵���
					while (abs(location[1] - cur->x_location) <= 1)
					{
						if (abs(location[1] - cur->y_location) <= 1) //�жϿ��Ա�������Ƿ��ѵ���Ŀ��㸽��
						{
							cur->index_misson++; //���ѵ���������һ������
							cur->num_mission--;  //��ǰ����������һ
							if (m->fetch_time == 0)
								m->fetch_time = time; //���������ȡ��������ǰʱ�伴Ϊȡ��ʱ��
							else
							{
								m->is_complete += 1; //����������͵��㣬�������ѱ����
								if (time - (m->order_time) <= dead_line)
								{
									money += 10;
									num_completed += 1;
								} //���͵�ʱ����30���ڣ����Ǯ��10���������1
								else if (time - (m->order_time) <= total_dead_line)
								{
									money -= 40;
									num_completed += 1;
									num_overtime += 1;
								} //��30-60֮��
								else if (time - (m->order_time) > total_dead_line)
								{
									is_break = 1;
								} //����60���Ʋ�
							}
							m = &(cur->task[deliver_man[i].mission_queue[deliver_man[i].index_misson]]);
							if (m->fetch_time == 0) //�����δȡ��
							{
								location[0] = m->x_start;
								location[1] = m->y_start;
							} //��Ŀ���Ϊ�ӵ���
							else
							{
								location[0] = m->x_terminal;
								location[1] = m->y_terminal;
							} //����Ŀ���Ϊ�͵���
						}
						else
							break;
					}
				}
				else
				{
					if (cur->y_location > location[1])
						cur->y_location -= 2;
					else
						cur->y_location += 2;
				} //��������δ���︽��������Ŀ���ǰ��
			}
			else
			{
				if (cur->x_location > location[0])
					cur->x_location -= 2;
				else
					cur->x_location += 2;
			}
		}
	} //��������δ���︽��������Ŀ���ǰ��
	add_deliver();
	if (money < 0)
		is_break = 1; //��Ǯ��<0�����Ʋ�
}