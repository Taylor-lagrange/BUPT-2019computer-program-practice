//作者：蒋明君
#include "all.h"

IMAGE map;
IMAGE time1, money1, complete1, overtime1, arrive;   //图片对象素材

void innitial_map()   //地图及右侧文字输出的初始化
{
	initgraph(1030, 680);          //初始化图形窗口
	char timestr1[20] = "时间单位：", moneystr1[20] = "金钱数：  ", completestr1[20] = "完成单数：", overtimestr1[20] = "超时单数:";
	setbkcolor(RGB(151, 192, 192));
	cleardevice();     //用背景色填充窗口
	loadimage(NULL, _T("map.png"));  //加载地图对象

	loadimage(&time1, "time1.png");         //加载图片：时间
	loadimage(&money1, "money1.png");       //加载图片：钱袋
	loadimage(&complete1, "complete1.png"); //加载图片：对号
	loadimage(&overtime1, "overtime1.png"); //加载图片：错叉
	//将图片贴到指定位置
	putimage(685, 30, &time1);
	putimage(685, 130, &money1);
	putimage(685, 230, &complete1);
	putimage(685, 330, &overtime1);
	//右侧文字输出部分
	settextstyle(17, 9, _T("Courier"));
	settextcolor(BLACK);
	outtextxy(685, 90, timestr1);
	outtextxy(685, 190, moneystr1);
	outtextxy(685, 290, completestr1);
	outtextxy(685, 390, overtimestr1);
	for (int i = 0; i < 19; i++)//对该矩阵做初始化，初始为都没有订单
		for (int j = 0; j < 19; j++)
			put_matrix[i][j].count = 0;
}


void map_print()  //地图、骑手等图片元素的刷新
{
	char timestr[20], moneystr[20], completestr[20], overtimestr[20];  //字符数组用以存储待输出数字信息
	IMAGE map;
	loadimage(NULL, _T("map.png"));  //地图加载
	Linkqueue q = mission_queue; //遍历队列，补上未出队订单的线
	if (!queue_isempty(&mission_queue))
		while (q.front->next != q.rear->next)
		{
			mission task = *q.front->next->data;
			setlinecolor(RED);
			line(task.x_start * 40 + 20, task.y_start * 40 + 20, task.x_terminal * 40 + 20, task.y_terminal * 40 + 20);
			q.front = q.front->next; 
		}
	for (int m = 0; m < num_deliver_man; m++)
	{
		for (int n = 0; n < max_dispose; n++)
		{
			if (deliver_man[m].task[n].is_complete == 0)
			{
				setlinecolor(RED);
				line(deliver_man[m].task[n].x_start * 40 + 20, deliver_man[m].task[n].y_start * 40 + 20, deliver_man[m].task[n].x_terminal * 40 + 20, deliver_man[m].task[n].y_terminal * 40 + 20);
			}
		}
	}
	for (int i = 0; i < num_deliver_man; i++)
	{
		//绘制快递员新位置
		putimage(40 * deliver_man[i].x_location, 40 * deliver_man[i].y_location, &deliver_man[i].driver_image);
	}

	//把数字转化为字符串
	_itoa_s(time, timestr, 10);
	_itoa_s(money, moneystr, 10);
	_itoa_s(num_completed, completestr, 10);
	_itoa_s(num_overtime, overtimestr, 10);
	//实时输出各项数目
	outtextxy(785, 90, timestr);
	setfillcolor(RGB(151, 192, 192));   
	solidrectangle(785, 190, 820, 210); //填充矩形覆盖旧信息
	outtextxy(785, 190, moneystr);
	outtextxy(785, 290, completestr);
	outtextxy(785, 390, overtimestr);
	setfillcolor(RGB(151, 192, 192));
	solidrectangle(865, 90, 1030, 680); //填充矩形覆盖旧信息
	int tot = 0;  //计数待输出停靠信息
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
		{
			for (int k = 1; k <= put_matrix[i][j].count; k++)  //遍历当前待输出停靠信息
			{
				tot++;//tot从一开始
				stop_print(tot, put_matrix[i][j].deliver_man_i[k], put_matrix[i][j].num_deliver[k], put_matrix[i][j].is_done[k], i, j);
			}
			put_matrix[i][j].count = 0;//该点结束后count置0
		}
}


void stop_print(int total, int deliver_man_i, int num_deliver, int is_done, int x, int y)  //停靠时图片及文字信息的输出
{
	char timestr5[20] = "停靠：";
	char timestr6[20] = "餐馆：";
	char timestr7[20] = "食客：";
	char timestr8[20] = "骑手编号：";
	char timestr9[20] = "订单号：";
	char str_stop_x[3], str_stop_y[3];
	char str_deliver[3], str_order[3];  //创建字符数组储存数字信息
	settextstyle(17, 9, _T("Courier"));
	settextcolor(BLACK);

	loadimage(&arrive, "arrive.jpg"); //加载“停靠”图片
	putimage(40 * x, 40 * y, &arrive);

	outtextxy(865, 90, timestr5);  //输出文字“停靠”
	_itoa_s(deliver_man_i, str_deliver, 10);
	outtextxy(865, 90 * total+20, timestr8);  //输出骑手号
	outtextxy(960, 90 * total + 20, str_deliver);
	_itoa_s(num_deliver, str_order, 10);
	outtextxy(865, 90 * total+40, timestr9);  //输出单号
	outtextxy(940, 90 * total + 40, str_order);
	if(is_done == 0)   //若停靠点为餐馆
		outtextxy(865, 90*total +60, timestr6);
	else     //若停靠点为食客
		outtextxy(865, 90*total +60, timestr7);
	//若停靠点为餐客，则会同时输出两个信息
	_itoa_s(x, str_stop_x, 10);
	_itoa_s(y, str_stop_y, 10);
	outtextxy(940, 90 * total + 60, str_stop_x), outtextxy(995, 90 * total + 60, str_stop_y);
}


