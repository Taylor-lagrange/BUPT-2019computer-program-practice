//作者：蒋明君

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
		if (deliver_man[i].num_mission == 0 || deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].is_complete == 1)//如果这个订单已经被完成跳过这一单
			continue;
		int aim_x = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal);//决定这是一个取单还是送单，确定其x坐标
		int aim_y = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal);//决定这是一个取单还是送单，确定其y坐标
		int arrive = 0;

		if (abs(deliver_man[i].x_location - aim_x) + abs(deliver_man[i].y_location - aim_y) == 1)//第1种情况，这个订单刚好就在快递员附近
		{
			arrive = 1;//标记订单到达
		}
		else if (deliver_man[i].x_location == 0 || deliver_man[i].x_location == 16)//修正坐标到边角的情况，此时订单没有直接到达，需要一个倒车来校正方向
		{
			deliver_man[i].x_location == 0 ? deliver_man[i].x_location += 2 : deliver_man[i].x_location -= 2;
		}
		else if (deliver_man[i].y_location == 0 || deliver_man[i].y_location == 16)//修正坐标到边角的情况，此时订单没有直接到达，需要一个倒车来校正方向
		{
			deliver_man[i].y_location == 0 ? deliver_man[i].y_location += 2 : deliver_man[i].y_location -= 2;
		}
		else if (abs(deliver_man[i].x_location - aim_x) == 1 || abs(deliver_man[i].y_location - aim_y) == 1)//第2种情况，取单和送单在一条街上，后面的情况要转化成现在的情况，通过一个转向的操作
		{
			if (abs(deliver_man[i].x_location - aim_x) == 1)//x方向上快递员与目标点同向，改变y坐标逼近目标点
				deliver_man[i].y_location > aim_y ? deliver_man[i].y_location -= 2 : deliver_man[i].y_location += 2;
			else if (abs(deliver_man[i].y_location - aim_y) == 1)//y方向上快递员与目标点同向，改变x坐标逼近目标点
				deliver_man[i].x_location > aim_x ? deliver_man[i].x_location -= 2 : deliver_man[i].x_location += 2;

			if (abs(deliver_man[i].x_location - aim_x) + abs(deliver_man[i].y_location - aim_y) == 1)//若操作完成后订单到达，标记arrive
				arrive = 1;//标记订单到达
		}
		else if (abs(deliver_man[i].x_location - aim_x) <= 2 || abs(deliver_man[i].y_location - aim_y) <= 2)//第3种情况，快递员需要转向来逼近目的地
		{
			deliver_man[i].x_location >= aim_x ? deliver_man[i].x_location-- : deliver_man[i].x_location++;
			deliver_man[i].y_location >= aim_y ? deliver_man[i].y_location-- : deliver_man[i].y_location++;
		}
		else //第4种情况，快递员无需转向或者直接接近，先逼近坐标
		{
			if (deliver_man[i].x_location % 2 == 0)
				deliver_man[i].x_location >= aim_x ? deliver_man[i].x_location -= 2 : deliver_man[i].x_location += 2;
			else
				deliver_man[i].y_location >= aim_y ? deliver_man[i].y_location -= 2 : deliver_man[i].y_location += 2;
		}
		if (arrive == 1)//如果订单被送到了
		{
			while (abs(deliver_man[i].x_location - aim_x) + abs(deliver_man[i].y_location - aim_y) == 1)//为了防止相同的时间点有多个任务
			{

				int temp = ++put_matrix[aim_x][aim_y].count;//这个点的任务数量自加
				put_matrix[aim_x][aim_y].deliver_man_i[temp] = i;//记录快递员是谁
				put_matrix[aim_x][aim_y].is_done[temp] = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? 0 : 1);//记录是取单还是送单
				put_matrix[aim_x][aim_y].num_deliver[temp] = deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].number;//记录订单编号

				if (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0)//一个取单操作完成
				{
					deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time = 1;
				}											
				else//送单操作完成
				{
					deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].is_complete = 1;
					if (time - deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].order_time < dead_line)//订单在规定时间被送达
					{
						num_completing[num_iscompleting] = deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].number;
						num_iscompleting++;
						money += 10;
						deliver_music = 1;
						num_completed++;
						num_iscompleting++;
					}
					else  if (time - deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].order_time >= dead_line && time - deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].order_time <= total_dead_line)//订单超时但不至破产
					{
						num_overtiming[num_isovertiming] = deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].number;
						num_isovertiming++;
						money -= 40;
						num_overtime++;
						warn_music = 1;//播放超时提醒
					}
					else//破产结算
					{
						num_overtime++;
						is_break = 1;
						warn_music = 1;//播放超时提醒
					}

				}
				deliver_man[i].num_mission--, deliver_man[i].index_misson++;//任务数减1，任务指针加1
				if (deliver_man[i].num_mission == 0 || deliver_man[i].mission_queue[deliver_man[i].index_misson] == -1 || deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].is_complete == 1)//若有好几个订单起始和终止相同，不判定这个时候的任务数量会出错
					break;
				aim_x = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal);//更新下一个坐标，观察是否是一个地点有好几个任务
				aim_y = (deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time == 0 ? deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start : deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal);
			}
		}
		add_deliver();
		if (money < 0)
			is_break = 1; //若钱数<0，则破产
	}
}