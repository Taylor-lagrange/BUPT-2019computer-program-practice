//���ߣ��⾲��
#include"all.h"

void predict_dsf(deliver man, int deep, int dead);
int is_visit_predict[max_dispose];               //������飬��ֹ��predict_dsf�Ĺ�����ͬһ�ڵ��ظ�������ֻ�е�����ڵ����ֵΪ2��ʱ�򣬲ű���Ƿ���
int total_spent_predict;                         //���predict_dsf���ܻ��ѣ����ָ�С�Ļ��Ѹ�������
int visit_sequence_predict[max_dispose * 2 + 2]; //��¼������˳��,��¼����˳�����Ҫ�����������±꣨ע�⣺ɾ��Ԫ��is_complete��1�������в�һ��������
int all_time_predict;                            //��¼��ɶ�������ʱ��
int min_dead_predict;                            //��Ϊ����Ѱ��������Ž��������Ϊ��Ӧ��һ����ʱ�������Ѱ����С��ʱ�ķ���
int weight_re;
void predict_dsf(deliver man, int deep, int dead)
{
	if (deep == man.num_mission || deep == deep_dsf) //�����һ�������ĵݹ飬�ҵ���һ���
	{
		if (min_dead_predict > dead || (min_dead_predict == dead && total_spent_predict > all_time_predict)) //�������Ž�,���Ȳ�Ҫ��ʱ��������ʱ��
		{
			total_spent_predict = all_time_predict;
			min_dead_predict = dead;
			weight_re = 25 * min_dead_predict + 5 * man.num_mission + total_spent_predict;
		}
		return;
	}
	if (min_dead_predict < dead || (min_dead_predict == dead && total_spent_predict < all_time_predict)) //��֦�����ʱ��ʱ������ʱ�Ѿ��������Ž⣬�����ٴ�����
		return;
	if (deep == 0) //��һ�������ľ����Ǵӿ��Ա����ʼ���꿪ʼ
		for (int i = 0; i < max_dispose; i++)
		{
			if (man.task[i].is_complete) //�ö����Ѿ�����ˣ�Ҳ��������
				continue;
			if (is_visit_predict[i] == 2) //�͵��ӵ����Ѿ����滮����������
				continue;
			int spent_start = 0; //������Ա�ӵ�ǰλ�õ����������ľ���
			if (is_visit_predict[i] == 0)
			{
				spent_start = distance_spent(man.x_location, man.task[i].x_start, man.y_location, man.task[i].y_start);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_start; //���»��ѵ���ʱ��
				predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[i] == 1)
			{
				spent_start = distance_spent(man.x_location, man.task[i].x_terminal, man.y_location, man.task[i].y_terminal);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_start; //���»��ѵ���ʱ��
				if (all_time_predict - man.task[i].order_time > dead_line)
					predict_dsf(man, deep + 1, dead + 1);
				else
					predict_dsf(man, deep + 1, dead);
			}
			all_time_predict -= spent_start; //����ʱ��ԭ״̬
			visit_sequence_predict[deep] = -1;
			is_visit_predict[i]--;
		}
	else
		for (int i = 0; i < max_dispose; i++)
		{
			if (man.task[i].is_complete) //�ö����Ѿ�����ˣ�Ҳ��������
				continue;
			if (is_visit_predict[i] == 2) //�͵��ӵ����Ѿ����滮����������
				continue;
			int spent_interval = 0;                      //spent_intervalΪ������Ա�ӵ�ǰλ�õ����һ������㻨��ʱ��
			int prev = visit_sequence_predict[deep - 1];         //prev��ǰһ������
			if (prev == -1)//֮ǰһ��û�У�ֱ�ӷ���
				return;
			if (is_visit_predict[prev] == 1 && is_visit_predict[i] == 0) //��һ����ȡ��,��һ����ȡ��
			{
				spent_interval = distance_spent(man.task[prev].x_start, man.task[i].x_start, man.task[prev].y_start, man.task[i].y_start);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //���»��ѵ���ʱ��
				predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[prev] == 1 && is_visit_predict[i] == 1) //��һ����ȡ��,��һ�����ͻ�
			{
				spent_interval = distance_spent(man.task[prev].x_start, man.task[i].x_terminal, man.task[prev].y_start, man.task[i].y_terminal);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //���»��ѵ���ʱ��
				if (all_time_predict - man.task[i].order_time > dead_line)
					predict_dsf(man, deep + 1, dead + 1);
				else
					predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[prev] == 2 && is_visit_predict[i] == 0) //��һ�����ͻ�,��һ����ȡ��
			{
				spent_interval = distance_spent(man.task[prev].x_terminal, man.task[i].x_start, man.task[prev].y_terminal, man.task[i].y_start);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //���»��ѵ���ʱ��
				predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[prev] == 2 && is_visit_predict[i] == 1) //��һ�����ͻ�,��һ�����ͻ�
			{
				spent_interval = distance_spent(man.task[prev].x_terminal, man.task[i].x_terminal, man.task[prev].y_terminal, man.task[i].y_terminal);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //���»��ѵ���ʱ��
				if (all_time_predict - man.task[i].order_time > dead_line)
					predict_dsf(man, deep + 1, dead + 1);
				else
					predict_dsf(man, deep + 1, dead);
			}
			all_time_predict -= spent_interval; //����ʱ��ԭ״̬
			visit_sequence_predict[deep] = -1;
			is_visit_predict[i]--;
		}
}
int predict(mission dispose, deliver man)
{
	weight_re = 0;
	all_time_predict = time;
	memset(visit_sequence_predict, -1, sizeof(visit_sequence_predict));//�����±�����0���������壬visit_sequence_predictȫ��-1
	memset(is_visit_predict, 0, sizeof(is_visit_predict));
	int flag = 1;

	int re = 0;//Ϊ���������С��
	for (int i = 0; i < max_dispose; i++)//Ϊ��Ԥ����ͬһ���ص�Ķ����Ļ���
	{
		if (man.task[i].is_complete)//������ɲ���
			continue;
		if (man.task[i].fetch_time && man.task[i].x_terminal == dispose.x_start && man.task[i].y_terminal == dispose.y_start)
			re -= 5;//�ж����Ͳ͵���õ�ȡ�͵���ͬȨֵ��һЩ
		if (man.task[i].fetch_time == 0 && man.task[i].x_start == dispose.x_start && man.task[i].y_terminal == dispose.y_terminal)
			re -= 40;//��һģһ���ĵĶ������������൱�ڲ���ʱ��
	}
	if (num_deliver_man > 10 && man.num_mission == 0)//������Աͦ�࣬�����Ų����£�re�ټ�
		re -= 100;

	for (int i = 0; i < max_dispose; i++)
		if (man.task[i].is_complete == 1)
			man.task[i] = dispose, flag = 0;
	man.num_mission += 2;//������������Ա����������2

	if (flag)
		return inf;

	for (int i = 0; i < max_dispose; i++) //��is_visit_predict�����ʼ��Ϊȫδ����
		is_visit_predict[i] = 2;

	for (int i = 0; i < max_dispose - 1; i++)//dsfʱ�ȶ�task���ݿⰴ�µ�ʱ�����һ��ð���������µ�ʱ���Ⱥ���������
	{
		for (int j = 0; j < max_dispose - 1 - i; j++)
		{
			if (man.task[j].order_time > man.task[j + 1].order_time)
			{
				mission temp = man.task[j];
				man.task[j] = man.task[j + 1];
				man.task[j + 1] = temp;
			}
		}

	}

	int lenth = 0;
	for (int i = 0; i < max_dispose && lenth < deep_dsf; i++)
	{
		if (man.task[i].is_complete)
			continue;
		if (man.task[i].fetch_time)
			is_visit_predict[i] = 1, lenth += 1;//ȡ�˵���ռһ������λ
		else
			is_visit_predict[i] = 0, lenth +=2;//ûȡ����ռ��������λ
	}

	total_spent_predict = inf;
	min_dead_predict = inf;
	predict_dsf(man, 0, 0);
	return weight_re+re;//���ؽ�����ڼ���Ȩֵ�ӿ�С��Ľ��
}
