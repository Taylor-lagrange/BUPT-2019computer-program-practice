//作者：吴静迪
#include"all.h"

void predict_dsf(deliver man, int deep, int dead);
int is_visit_predict[max_dispose];               //标记数组，防止在predict_dsf的过程中同一节点重复遍历，只有当这个节点的数值为2的时候，才被标记访问
int total_spent_predict;                         //标记predict_dsf的总花费，发现更小的花费更新数组
int visit_sequence_predict[max_dispose * 2 + 2]; //记录遍历的顺序,记录的是顺序遍历要遍历的数组下标（注意：删除元素is_complete置1，该序列不一定连续）
int all_time_predict;                            //记录完成订单的总时间
int min_dead_predict;                            //作为深搜寻找相对最优解的条件，为了应对一定超时的情况，寻找最小超时的方案
int weight_re;
void predict_dsf(deliver man, int deep, int dead)
{
	if (deep == man.num_mission || deep == deep_dsf) //完成了一次完整的递归，找到了一组解
	{
		if (min_dead_predict > dead || (min_dead_predict == dead && total_spent_predict > all_time_predict)) //更新最优解,首先不要超时，其次最短时间
		{
			total_spent_predict = all_time_predict;
			min_dead_predict = dead;
			weight_re = 25 * min_dead_predict + 5 * man.num_mission + total_spent_predict;
		}
		return;
	}
	if (min_dead_predict < dead || (min_dead_predict == dead && total_spent_predict < all_time_predict)) //剪枝，这个时候超时订单超时已经超过最优解，不用再次深搜
		return;
	if (deep == 0) //第一次搜索的距离是从快递员的起始坐标开始
		for (int i = 0; i < max_dispose; i++)
		{
			if (man.task[i].is_complete) //该订单已经完成了，也不用找了
				continue;
			if (is_visit_predict[i] == 2) //送单接单都已经被规划，不用找了
				continue;
			int spent_start = 0; //计算快递员从当前位置到，他任务点的距离
			if (is_visit_predict[i] == 0)
			{
				spent_start = distance_spent(man.x_location, man.task[i].x_start, man.y_location, man.task[i].y_start);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_start; //更新花费的总时间
				predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[i] == 1)
			{
				spent_start = distance_spent(man.x_location, man.task[i].x_terminal, man.y_location, man.task[i].y_terminal);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_start; //更新花费的总时间
				if (all_time_predict - man.task[i].order_time > dead_line)
					predict_dsf(man, deep + 1, dead + 1);
				else
					predict_dsf(man, deep + 1, dead);
			}
			all_time_predict -= spent_start; //回溯时还原状态
			visit_sequence_predict[deep] = -1;
			is_visit_predict[i]--;
		}
	else
		for (int i = 0; i < max_dispose; i++)
		{
			if (man.task[i].is_complete) //该订单已经完成了，也不用找了
				continue;
			if (is_visit_predict[i] == 2) //送单接单都已经被规划，不用找了
				continue;
			int spent_interval = 0;                      //spent_interval为该外卖员从当前位置到达第一个任务点花的时间
			int prev = visit_sequence_predict[deep - 1];         //prev是前一个订单
			if (prev == -1)//之前一单没有，直接返回
				return;
			if (is_visit_predict[prev] == 1 && is_visit_predict[i] == 0) //上一单是取货,这一单是取货
			{
				spent_interval = distance_spent(man.task[prev].x_start, man.task[i].x_start, man.task[prev].y_start, man.task[i].y_start);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //更新花费的总时间
				predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[prev] == 1 && is_visit_predict[i] == 1) //上一单是取货,这一单是送货
			{
				spent_interval = distance_spent(man.task[prev].x_start, man.task[i].x_terminal, man.task[prev].y_start, man.task[i].y_terminal);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //更新花费的总时间
				if (all_time_predict - man.task[i].order_time > dead_line)
					predict_dsf(man, deep + 1, dead + 1);
				else
					predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[prev] == 2 && is_visit_predict[i] == 0) //上一单是送货,这一单是取货
			{
				spent_interval = distance_spent(man.task[prev].x_terminal, man.task[i].x_start, man.task[prev].y_terminal, man.task[i].y_start);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //更新花费的总时间
				predict_dsf(man, deep + 1, dead);
			}
			else if (is_visit_predict[prev] == 2 && is_visit_predict[i] == 1) //上一单是送货,这一单是送货
			{
				spent_interval = distance_spent(man.task[prev].x_terminal, man.task[i].x_terminal, man.task[prev].y_terminal, man.task[i].y_terminal);
				visit_sequence_predict[deep] = i;
				is_visit_predict[i]++;
				all_time_predict += spent_interval; //更新花费的总时间
				if (all_time_predict - man.task[i].order_time > dead_line)
					predict_dsf(man, deep + 1, dead + 1);
				else
					predict_dsf(man, deep + 1, dead);
			}
			all_time_predict -= spent_interval; //回溯时还原状态
			visit_sequence_predict[deep] = -1;
			is_visit_predict[i]--;
		}
}
int predict(mission dispose, deliver man)
{
	weight_re = 0;
	all_time_predict = time;
	memset(visit_sequence_predict, -1, sizeof(visit_sequence_predict));//由于下标里有0，避免歧义，visit_sequence_predict全赋-1
	memset(is_visit_predict, 0, sizeof(is_visit_predict));
	int flag = 1;

	int re = 0;//为特殊情况开小灶
	for (int i = 0; i < max_dispose; i++)//为了预防有同一个地点的订单的机制
	{
		if (man.task[i].is_complete)//订单完成不看
			continue;
		if (man.task[i].fetch_time && man.task[i].x_terminal == dispose.x_start && man.task[i].y_terminal == dispose.y_start)
			re -= 5;//有订单送餐点与该单取餐点相同权值减一些
		if (man.task[i].fetch_time == 0 && man.task[i].x_start == dispose.x_start && man.task[i].y_terminal == dispose.y_terminal)
			re -= 40;//有一模一样的的订单，基本上相当于不花时间
	}
	if (num_deliver_man > 10 && man.num_mission == 0)//如果快递员挺多，还闲着不干事，re再减
		re -= 100;

	for (int i = 0; i < max_dispose; i++)
		if (man.task[i].is_complete == 1)
			man.task[i] = dispose, flag = 0;
	man.num_mission += 2;//把任务推入快递员，任务数加2

	if (flag)
		return inf;

	for (int i = 0; i < max_dispose; i++) //对is_visit_predict数组初始化为全未访问
		is_visit_predict[i] = 2;

	for (int i = 0; i < max_dispose - 1; i++)//dsf时先对task数据库按下单时间进行一个冒泡排序，以下单时间先后升序排列
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
			is_visit_predict[i] = 1, lenth += 1;//取了单，占一个深搜位
		else
			is_visit_predict[i] = 0, lenth +=2;//没取单，占两个深搜位
	}

	total_spent_predict = inf;
	min_dead_predict = inf;
	predict_dsf(man, 0, 0);
	return weight_re+re;//返回结果等于计算权值加开小灶的结果
}
