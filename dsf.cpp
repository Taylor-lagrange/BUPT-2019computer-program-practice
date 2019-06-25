//作者：吴静迪
#include "all.h"

int is_visit[max_dispose];               //标记数组，防止在dsf的过程中同一节点重复遍历，只有当这个节点的数值为2的时候，才被标记访问
int total_spent;                         //标记dsf的总花费，发现更小的花费更新数组
int visit_sequence[max_dispose * 2 + 2]; //记录遍历的顺序,记录的是顺序遍历要遍历的数组下标（注意：删除元素is_complete置1，该序列不一定连续）
int all_time;                            //记录完成订单的总时间
int min_dead;                            //作为深搜寻找相对最优解的条件，为了应对一定超时的情况，寻找最小超时的方案
void dsf(int man, int deep, int dead)
{
	if (deep == deliver_man[man].num_mission||deep==deep_dsf) //完成了一次完整的递归，找到了一组解
	{
		if (min_dead > dead || (min_dead == dead && total_spent > all_time)) //更新最优解,首先不要超时，其次最短时间
		{
			min_dead = dead;
			total_spent = all_time;
			deliver_man[man].index_misson = 0; //任务队列指针置0
			memset(deliver_man[man].mission_queue, -1, sizeof(deliver_man[man].mission_queue));
			for (int i = 0; i < deliver_man[man].num_mission&& visit_sequence[i]!=-1; i++) //重新进行赋值构建任务队列
				deliver_man[man].mission_queue[i] = visit_sequence[i];
		}
		return;
	}
	if (min_dead < dead || (min_dead == dead && total_spent < all_time)) //剪枝，这个时候超时订单超时已经超过最优解，不用再次深搜
		return;
	if (deep == 0) //第一次搜索的距离是从快递员的起始坐标开始
		for (int i = 0; i < max_dispose; i++)
		{
			if (deliver_man[man].task[i].is_complete) //该订单已经完成了，也不用找了
				continue;
			if (is_visit[i] == 2) //送单接单都已经被规划，不用找了
				continue;
			int spent_start = 0; //计算快递员从当前位置到，他任务点的距离
			if (is_visit[i] == 0)
			{
				spent_start = distance_spent(deliver_man[man].x_location, deliver_man[man].task[i].x_start, deliver_man[man].y_location, deliver_man[man].task[i].y_start);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_start; //更新花费的总时间
				dsf(man, deep + 1, dead);
			}
			else if (is_visit[i] == 1)
			{
				spent_start = distance_spent(deliver_man[man].x_location, deliver_man[man].task[i].x_terminal, deliver_man[man].y_location, deliver_man[man].task[i].y_terminal);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_start; //更新花费的总时间
				if (all_time - deliver_man[man].task[i].order_time > dead_line)
					dsf(man, deep + 1, dead + 1);
				else
					dsf(man, deep + 1, dead);
			}
			all_time -= spent_start; //回溯时还原状态
			visit_sequence[deep] = -1;//回溯时填了i，导致错误，设置了机制去预防但是没有发挥深搜的最好效果
			is_visit[i]--;
		}
	else
		for (int i = 0; i < max_dispose; i++)
		{
			if (deliver_man[man].task[i].is_complete) //该订单已经完成了，也不用找了
				continue;
			if (is_visit[i] == 2) //送单接单都已经被规划，不用找了
				continue;
			int spent_interval = 0;                      //spent_interval为该外卖员从当前位置到达第一个任务点花的时间
			int prev = visit_sequence[deep - 1];         //prev是前一个订单
			if (prev == -1)//之前一单没有，直接返回
				return;
			if (is_visit[prev] == 1 && is_visit[i] == 0) //上一单是取货,这一单是取货
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_start, deliver_man[man].task[i].x_start, deliver_man[man].task[prev].y_start, deliver_man[man].task[i].y_start);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //更新花费的总时间
				dsf(man, deep + 1, dead);
			}
			else if (is_visit[prev] == 1 && is_visit[i] == 1) //上一单是取货,这一单是送货
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_start, deliver_man[man].task[i].x_terminal, deliver_man[man].task[prev].y_start, deliver_man[man].task[i].y_terminal);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //更新花费的总时间
				if (all_time - deliver_man[man].task[i].order_time > dead_line)
					dsf(man, deep + 1, dead + 1);
				else
					dsf(man, deep + 1, dead);
			}
			else if (is_visit[prev] == 2 && is_visit[i] == 0) //上一单是送货,这一单是取货
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_terminal, deliver_man[man].task[i].x_start, deliver_man[man].task[prev].y_terminal, deliver_man[man].task[i].y_start);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //更新花费的总时间
				dsf(man, deep + 1, dead);
			}
			else if (is_visit[prev] == 2 && is_visit[i] == 1) //上一单是送货,这一单是送货
			{
				spent_interval = distance_spent(deliver_man[man].task[prev].x_terminal, deliver_man[man].task[i].x_terminal, deliver_man[man].task[prev].y_terminal, deliver_man[man].task[i].y_terminal);
				visit_sequence[deep] = i;
				is_visit[i]++;
				all_time += spent_interval; //更新花费的总时间
				if (all_time - deliver_man[man].task[i].order_time > dead_line)
					dsf(man, deep + 1, dead + 1);
				else
					dsf(man, deep + 1, dead);
			}
			all_time -= spent_interval; //回溯时还原状态
			visit_sequence[deep] = -1;
			is_visit[i]--;
		}
}
void order_dispose(int man)
{
	all_time = time;
	memset(visit_sequence, -1, sizeof(visit_sequence));//由于下标里有0，避免歧义，visit_sequence全赋-1
	memset(is_visit, 0, sizeof(is_visit));
	for (int i = 0; i < max_dispose; i++) //对is_visit数组初始化为全未访问
		is_visit[i] = 2;

	for (int i = 0; i < max_dispose-1; i++)//dsf时先对task数据库按下单时间进行一个冒泡排序，以下单时间先后升序排列
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