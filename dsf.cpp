//���ߣ��⾲��
#include "all.h"

int is_visit[max_dispose];               //������飬��ֹ��dsf�Ĺ�����ͬһ�ڵ��ظ�������ֻ�е�����ڵ����ֵΪ2��ʱ�򣬲ű���Ƿ���
int total_spent;                         //���dsf���ܻ��ѣ����ָ�С�Ļ��Ѹ�������
int visit_sequence[max_dispose * 2 + 2]; //��¼������˳��,��¼����˳�����Ҫ�����������±꣨ע�⣺ɾ��Ԫ��is_complete��1�������в�һ��������
int all_time;                            //��¼��ɶ�������ʱ��
int min_dead;                            //��Ϊ����Ѱ��������Ž��������Ϊ��Ӧ��һ����ʱ�������Ѱ����С��ʱ�ķ���
void dsf(int man, int deep, int dead)
{
	if (deep == deliver_man[man].num_mission||deep==deep_dsf) //�����һ�������ĵݹ飬�ҵ���һ���
	{
		if (min_dead > dead || (min_dead == dead && total_spent > all_time)) //�������Ž�,���Ȳ�Ҫ��ʱ��������ʱ��
		{
			min_dead = dead;
			total_spent = all_time;
			deliver_man[man].index_misson = 0; //�������ָ����0
			memset(deliver_man[man].mission_queue, -1, sizeof(deliver_man[man].mission_queue));
			for (int i = 0; i < deliver_man[man].num_mission&& visit_sequence[i]!=-1; i++) //���½��и�ֵ�����������
				deliver_man[man].mission_queue[i] = visit_sequence[i];
		}
		return;
	}
	if (min_dead < dead || (min_dead == dead && total_spent < all_time)) //��֦�����ʱ��ʱ������ʱ�Ѿ��������Ž⣬�����ٴ�����
		return;
	if (deep == 0) //��һ�������ľ����Ǵӿ��Ա����ʼ���꿪ʼ
		for (int i = 0; i < max_dispose; i++)
		{
			if (deliver_man[man].task[i].is_complete) //�ö����Ѿ�����ˣ�Ҳ��������
				continue;
			if (is_visit[i] == 2) //�͵��ӵ����Ѿ����滮����������
				continue;
			int spent_start = 0; //������Ա�ӵ�ǰλ�õ����������ľ���
			if (is_visit[i] == 0)
			{
				spent_start = distance_spent(deliver_man[man].x_location, deliver_man[man].task[i].x_start, deliver_man[man].y_location, deliver_man[man].task[i].y_start);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_start; //���»��ѵ���ʱ��
				dsf(man, deep + 1, dead);
			}
			else if (is_visit[i] == 1)
			{
				spent_start = distance_spent(deliver_man[man].x_location, deliver_man[man].task[i].x_terminal, deliver_man[man].y_location, deliver_man[man].task[i].y_terminal);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_start; //���»��ѵ���ʱ��
				if (all_time - deliver_man[man].task[i].order_time > dead_line)
					dsf(man, deep + 1, dead + 1);
				else
					dsf(man, deep + 1, dead);
			}
			all_time -= spent_start; //����ʱ��ԭ״̬
			visit_sequence[deep] = -1;//����ʱ����i�����´��������˻���ȥԤ������û�з������ѵ����Ч��
			is_visit[i]--;
		}
	else
		for (int i = 0; i < max_dispose; i++)
		{
			if (deliver_man[man].task[i].is_complete) //�ö����Ѿ�����ˣ�Ҳ��������
				continue;
			if (is_visit[i] == 2) //�͵��ӵ����Ѿ����滮����������
				continue;
			int spent_interval = 0;                      //spent_intervalΪ������Ա�ӵ�ǰλ�õ����һ������㻨��ʱ��
			int prev = visit_sequence[deep - 1];         //prev��ǰһ������
			if (prev == -1)//֮ǰһ��û�У�ֱ�ӷ���
				return;
			if (is_visit[prev] == 1 && is_visit[i] == 0) //��һ����ȡ��,��һ����ȡ��
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_start, deliver_man[man].task[i].x_start, deliver_man[man].task[prev].y_start, deliver_man[man].task[i].y_start);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //���»��ѵ���ʱ��
				dsf(man, deep + 1, dead);
			}
			else if (is_visit[prev] == 1 && is_visit[i] == 1) //��һ����ȡ��,��һ�����ͻ�
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_start, deliver_man[man].task[i].x_terminal, deliver_man[man].task[prev].y_start, deliver_man[man].task[i].y_terminal);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //���»��ѵ���ʱ��
				if (all_time - deliver_man[man].task[i].order_time > dead_line)
					dsf(man, deep + 1, dead + 1);
				else
					dsf(man, deep + 1, dead);
			}
			else if (is_visit[prev] == 2 && is_visit[i] == 0) //��һ�����ͻ�,��һ����ȡ��
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_terminal, deliver_man[man].task[i].x_start, deliver_man[man].task[prev].y_terminal, deliver_man[man].task[i].y_start);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //���»��ѵ���ʱ��
				dsf(man, deep + 1, dead);
			}
			else if (is_visit[prev] == 2 && is_visit[i] == 1) //��һ�����ͻ�,��һ�����ͻ�
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_terminal, deliver_man[man].task[i].x_terminal, deliver_man[man].task[prev].y_terminal, deliver_man[man].task[i].y_terminal);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //���»��ѵ���ʱ��
				if (all_time - deliver_man[man].task[i].order_time > dead_line)
					dsf(man, deep + 1, dead + 1);
				else
					dsf(man, deep + 1, dead);
			}
			all_time -= spent_interval; //����ʱ��ԭ״̬
			visit_sequence[deep] = -1;
			is_visit[i]--;
		}
}
void order_dispose(int man)
{
	all_time = time;
	memset(visit_sequence, -1, sizeof(visit_sequence));//�����±�����0���������壬visit_sequenceȫ��-1
	memset(is_visit, 0, sizeof(is_visit));
	for (int i = 0; i < max_dispose; i++) //��is_visit�����ʼ��Ϊȫδ����
		is_visit[i] = 2;

	for (int i = 0; i < max_dispose-1; i++)//dsfʱ�ȶ�task���ݿⰴ�µ�ʱ�����һ��ð���������µ�ʱ���Ⱥ���������
	{
		for (int j = 0; j < max_dispose-1-i; j++)
		{
			if (deliver_man[man].task[j].order_time > deliver_man[man].task[j+1].order_time)
			{
				mission temp = deliver_man[man].task[j];
				deliver_man[man].task[j] = deliver_man[man].task[j + 1];
				deliver_man[man].task[j + 1] = temp;
			}
		}

	}
	int lenth = 0;
	for (int i = 0; i < max_dispose && lenth < deep_dsf; i++)
	{
		if (deliver_man[man].task[i].is_complete)
			continue;
		if (deliver_man[man].task[i].fetch_time==1)
			is_visit[i] = 1, lenth += 1;
		else
			is_visit[i] = 0, lenth += 2;
	}


	total_spent = inf;
	min_dead = inf;
	dsf(man, 0, 0);
}

int distance_spent(int x1, int x2, int y1, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2) - 1) / 2;
}