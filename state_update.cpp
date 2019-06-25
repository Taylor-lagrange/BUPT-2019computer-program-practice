#include "all.h"
void state()
{
	int location[2];			//建立一个数组，用来储存程序员下一个目标点。第一个数据为x坐标，第二个数据为y坐标
	deliver* cur;				//创建一个指针记录当前快递员信息
	missionptr m;				//创建一个指针记录当前任务信息
	num_order = num_completed;  //让接单数先等于当前完成数，便于一会统计总接单数
	for (int i = 0; i < num_deliver_man; i++) //对所有快递员进行遍历
	{
		cur = &deliver_man[i];
		for (int n = 0; n < max_dispose; n++)
		{
			if (cur->task[n].is_complete == 0)
				num_order++;
		} //订单正在途中则接单数加一
		if (cur->num_mission == 0)
			continue; //如果快递员当前没有任务，则对下一个快递员进行操作
		else
		{
			m = &(cur->task[deliver_man[i].mission_queue[deliver_man[i].index_misson]]);
			if (m->fetch_time == 0) //如果还未取单
			{
				location[0] = m->x_start;
				location[1] = m->y_start;
			} //则目标点为接单处
			else
			{
				location[0] = m->x_terminal;
				location[1] = m->y_terminal;
			} //否则目标点为送单处
			if (abs(location[0] - cur->x_location) <= 1) //判断快递员横坐标是否已到达目标点附近
			{
				if (abs(location[1] - cur->y_location) <= 1) //判断快递员纵坐标是否已到达目标点附近
				{
					cur->index_misson++; //若已到达，则进行下一个任务
					cur->num_mission--;  //当前任务数量减一
					if (m->fetch_time == 0)
						m->fetch_time = time; //若到达的是取单处，则当前时间即为取单时间
					else
					{
						m->is_complete += 1; //若到达的是送单点，则任务已被完成
						if (time - (m->order_time) <= dead_line)
						{
							money += 10;
							num_completed += 1;
						} //若送单时间在30以内，则金钱加10，完成数加1
						else if (time - (m->order_time) <= total_dead_line)
						{
							money -= 40;
							num_completed += 1;
							num_overtime += 1;
						} //在30-60之间
						else if (time - (m->order_time) > total_dead_line)
						{
							is_break = 1;
						} //超过60则破产
					}
					m = &(cur->task[deliver_man[i].mission_queue[deliver_man[i].index_misson]]);
					if (m->fetch_time == 0) //如果还未取单
					{
						location[0] = m->x_start;
						location[1] = m->y_start;
					} //则目标点为接单处
					else
					{
						location[0] = m->x_terminal;
						location[1] = m->y_terminal;
					} //否则目标点为送单处
					while (abs(location[1] - cur->x_location) <= 1)
					{
						if (abs(location[1] - cur->y_location) <= 1) //判断快递员纵坐标是否已到达目标点附近
						{
							cur->index_misson++; //若已到达，则进行下一个任务
							cur->num_mission--;  //当前任务数量减一
							if (m->fetch_time == 0)
								m->fetch_time = time; //若到达的是取单处，则当前时间即为取单时间
							else
							{
								m->is_complete += 1; //若到达的是送单点，则任务已被完成
								if (time - (m->order_time) <= dead_line)
								{
									money += 10;
									num_completed += 1;
								} //若送单时间在30以内，则金钱加10，完成数加1
								else if (time - (m->order_time) <= total_dead_line)
								{
									money -= 40;
									num_completed += 1;
									num_overtime += 1;
								} //在30-60之间
								else if (time - (m->order_time) > total_dead_line)
								{
									is_break = 1;
								} //超过60则破产
							}
							m = &(cur->task[deliver_man[i].mission_queue[deliver_man[i].index_misson]]);
							if (m->fetch_time == 0) //如果还未取单
							{
								location[0] = m->x_start;
								location[1] = m->y_start;
							} //则目标点为接单处
							else
							{
								location[0] = m->x_terminal;
								location[1] = m->y_terminal;
							} //否则目标点为送单处
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
				} //若纵坐标未到达附近，则向目标点前进
			}
			else
			{
				if (cur->x_location > location[0])
					cur->x_location -= 2;
				else
					cur->x_location += 2;
			}
		}
	} //若横坐标未到达附近，则向目标点前进
	add_deliver();
	if (money < 0)
		is_break = 1; //若钱数<0，则破产
}