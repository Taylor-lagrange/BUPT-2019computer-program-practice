//IMAGE complete;
			//gui_stop();
			//loadimage(&deliver_man[num_deliver_man - 1].driver_image, "complete1.png");   //骑手图片
/*
gui_stop(i, deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time);  //图形输出
stop_count++;



						//loadimage(&complete, "complete1.png");
						//putimage(40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start, 40 * 40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start, &complete);
						/*if ((deliver_man[i].x_location + deliver_man[i].y_location) - (aim_x + aim_y) ==-1)
						{
							if (deliver_man[i].stopflag1 == 0)
								deliver_man[i].stopflag1 = 1;
							else if (deliver_man[i].stopflag1 == 2)
								deliver_man[i].stopflag1 = 3;
						}												//标记该外卖员在左侧/上方取到单
						else
						{
							if (deliver_man[i].stopflag2 == 0)
								deliver_man[i].stopflag2 = 1;
							else if (deliver_man[i].stopflag2 == 2)
								deliver_man[i].stopflag2 = 3;
						}								//标记该外卖员在右侧/下方取到单

						//贴图
					//putimage(40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal, 40 * 40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal, &complete);

					/*if ((deliver_man[i].x_location + deliver_man[i].y_location) - (aim_x + aim_y) == -1)
						{
							if (deliver_man[i].stopflag1 == 0)
								deliver_man[i].stopflag1 = 2;
							else if (deliver_man[i].stopflag1 == 1)
								deliver_man[i].stopflag1 = 3;
						}									//标记该外卖员在左侧/上方送到单
						else
						{
							if (deliver_man[i].stopflag2 == 0)
								deliver_man[i].stopflag2 = 2;
							else if (deliver_man[i].stopflag2 == 1)
								deliver_man[i].stopflag2 = 3;
						}										//标记该外卖员在右侧/下方送到单 


*/

/*
void gui_stop(int i, int flag) //停靠时的动画输出
{
	char timestr5[20] = "停靠：";
	char timestr6[20] = "餐馆：";
	char timestr7[20] = "食客：";
	char str_stop_x[3], str_stop_y[3];
	settextstyle(17, 9, _T("Courier"));
	settextcolor(BLACK);
	outtextxy(885, 90, timestr5);

	if (flag == 0)
	{
		putimage(40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start, 40 * 40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start, &complete1);
		outtextxy(895, 110, timestr6);
		_itoa_s(deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start, str_stop_x, 10);
		_itoa_s(deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start, str_stop_y, 10);
		outtextxy(935, 110 + stop_count * 20, str_stop_x), outtextxy(955, 110 + stop_count * 20, str_stop_y);
		stop_count++;
	}
	else
	{
		putimage(40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal, 40 * 40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal, &complete1);
		outtextxy(895, 90, timestr7);
		_itoa_s(deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal, str_stop_x, 10);
		_itoa_s(deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal, str_stop_y, 10);
		outtextxy(935, 110 + stop_count * 20, str_stop_x), outtextxy(955, 110 + stop_count * 20, str_stop_y);
		stop_count++;
	}
}
*/

/*
/*printf("时间: %d\n", time);
	printf("钱: %d\n", money);
	printf("接单数: %d\n", num_order);
	printf("完成数: %d;	结单: ", num_completed);
	for (int i = 0; i <= num_iscompleting; i++)
		if (num_completing[i] != -1)
			printf("%d ", num_completing[i]);
	printf(";\n超时数: %d; 罚时: ", num_overtime);
	for (int i = 0; i <= num_isovertiming; i++)
		if (num_overtiming[i] != -1)
			printf("%d	", num_overtiming[i]);
	printf(";\n");
	int i = 0; //计数骑手数量
	while (i < num_deliver_man)
	{
		printf("骑手%d位置: %d,%d; 停靠：", i, deliver_man[i].x_location, deliver_man[i].y_location);
		if (deliver_man[i].x_location % 2 == 0)
		{
			if (deliver_man[i].stopflag1 == 1)
				printf("餐馆%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
			else if (deliver_man[i].stopflag1 == 2)
				printf("食客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
			else if (deliver_man[i].stopflag1 == 3)
				printf("餐客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);              //判断上方建筑情况
			if (deliver_man[i].stopflag2 == 1)
				printf("餐馆%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
			else if (deliver_man[i].stopflag2 == 2)
				printf("食客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
			else if (deliver_man[i].stopflag2 == 3)
				printf("餐客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);				//判断下方建筑情况


		}             //当快递员位于两建筑物上下之间时
		else
		{
			if (deliver_man[i].stopflag1 == 1)
				printf("餐馆%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag1 == 2)
				printf("食客%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag1 == 3)
				printf("餐客%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);					//判断左侧建筑物情况
			if (deliver_man[i].stopflag2 == 1)
				printf("餐馆%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag2 == 2)
				printf("食客%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag2 == 3)
				printf("餐客%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);				//判断右侧建筑情况

		}				//当快递员位于两建筑物左右之间时
		i++;
		printf(";\n\n");


	}*/
/*
//当没有新订单输入且所有订单完成，跳出循环
		/*int over = 1;
		for (int i = 0; i < num_deliver_man; i++)
		{
			for (int j = 0; j < max_dispose; j++)
			{
				if (deliver_man[i].task[j].is_complete == 0)
				{
					over = 0;
					break;
				}
			}
			if (over == 0)
				break;
		}
		if (queue_isempty(&mission_queue) && over&&time> mission_queue.rear->data->order_time)//特判队尾元素
			break;//一直到这，正式运行可以注释掉
		//printf("time:%d\n\n", time);*/
		/*if (thread_lock == 0)
		{
			if (!_kbhit())
				thread_lock = 1;
		}*/
/*
		/*for (int i = 0; i < num_deliver_man; i++)
		{
			setfillcolor(RGB(207, 169, 114));     //背景黄 207 269 114
			//擦除原来的方块，用与背景相同的颜色
			solidrectangle(40 * deliver_man[i].x_location, 40 * deliver_man[i].y_location, 40 * deliver_man[i].x_location + 40, 40 * deliver_man[i].y_location + 40);
		}*/

		/*int unique = 0;
		if (mission_queue.rear->data->order_time == time && unique==0)//特判队尾元素
		{
			flag = 1;
			unique = 1;
			num_order++;  //接单数加一
			mission_allocate(*(mission_queue.rear->data));
		}*/

		/*missionptr m = NULL; //创建一个任务结构体 指针
		FILE* fptr = NULL;   //创建文件指针
		int flag = 0;
		if (fopen_s(&fptr, "3.in", "r") != 0)
		{
			printf("File could not be opened\n"); //若打开失败，则输出错误提示
			do
			{
				m = (missionptr)malloc(sizeof(mission)); //读取完一组数据后，创建新的结构体，分配新的储存空间
				if (m != NULL)
				{
					m->fetch_time = 0;//设置状态
					m->is_complete = 0;
					scanf_s("%d %d %d %d %d %d", &(m->number), &(m->order_time), &(m->x_start), &(m->y_start), &(m->x_terminal), &(m->y_terminal));
					queue_push(&mission_queue, m);//将新的任务进入队列
				}
				else
					printf("wrong on malloc m!!");
			} while (getchar() != EOF);
		}
		else
		{
			if (fptr != NULL)//如果文件指针合法，进行文件读入
			{
				while (!feof(fptr)) //检测文件是否结束
				{
					m = (missionptr)malloc(sizeof(mission)); //每读取到换行符时则创建一个新的结构体，分配新的储存空间
					if (m != NULL)//分配不成功输出提示信息
					{
						m->fetch_time = 0;//设置状态
						m->is_complete = 0;
						fscanf_s(fptr, "%d %d %d %d %d %d", &(m->number), &(m->order_time), &(m->x_start), &(m->y_start), &(m->x_terminal), &(m->y_terminal));//读取数据
						queue_push(&mission_queue, m);			 //将新的任务进入队列
					}
					else
						printf("wrong on malloc m!!");
				}
				fclose(fptr);
			}
			else
				printf("wrong on fptr != NULL");
		}*/