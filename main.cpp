//作者 吴静迪

#include "all.h"
unsigned __stdcall getInput(void* pArguments)
//线程函数的返回值是指定类型，形参也只能有一个
{
	missionptr temp = NULL;
	int x = 0, y = 0;
	temp = (missionptr)malloc(sizeof(mission));
	temp->is_complete = 0;
	temp->fetch_time = 0;
	int key = 0;
	char str_1[20] = "已生成新订单！", str_2[20] = "餐馆位置： ", str_3[20] = "食客位置： ", str_4[20] = "新订单编号：";
	char str_x_start[3], str_y_start[3], str_x_terminal[3], str_y_terminal[3], str_count[3];
	MOUSEMSG m;
	while (!is_break)//破产信号不发出进程不终止
	{
		temp->number = cartoon_count;
		while (MouseHit())//有鼠标消息进入循环
		{
			m = GetMouseMsg();

			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN://左键按下消息。
				x = m.x / 40;
				y = m.y / 40;
				if (x % 2 == 0 && y % 2 == 0 && 0 <= x && x <= 16 && 0 <= y && y <= 16) //订单合法且不越界
				{
					temp->x_start = x;
					temp->y_start = y;
					temp->order_time = time;
					key = 1;
				}
				break;
			case WM_LBUTTONUP://左键弹起消息
				x = m.x / 40;
				y = m.y / 40;
				if (x % 2 == 0 && y % 2 == 0 && 0 <= x && x <= 16 && 0 <= y && y <= 16 && key == 1) //订单合法且不越界
				{
					temp->x_terminal = x;
					temp->y_terminal = y;
					//queue_push(&mission_queue, temp); //将新的任务进入队列
					mission_allocate(*temp);
					cartoon_count++;
					key = 0;
					setfillcolor(RGB(151, 192, 192));
					solidrectangle(780, 470, 850, 490); //擦除上一次输出的字符串
					solidrectangle(685, 490, 850, 530); //擦除“已生成新订单！”
					solidrectangle(685, 440, 850, 460); //擦除“新订单编号”
					_itoa_s(cartoon_count, str_count, 10);
					settextstyle(17, 9, _T("Courier"));
					settextcolor(BLACK);
					outtextxy(685, 440, str_4);
					outtextxy(780, 440, str_count),


					_itoa_s(temp->x_start, str_x_start, 10), _itoa_s(temp->y_start, str_y_start, 10);
					settextstyle(17, 9, _T("Courier"));
					settextcolor(BLACK);
					outtextxy(685, 470, str_2);
					outtextxy(780, 470, str_x_start), outtextxy(810, 470, str_y_start); //输出餐馆位置
					_itoa_s(temp->x_terminal, str_x_terminal, 10), _itoa_s(temp->y_terminal, str_y_terminal, 10);

					setlinecolor(RED);	//立即在餐馆和食客间画线
					line(temp->x_start * 40 + 20, temp->y_start * 40 + 20, temp->x_terminal * 40 + 20, temp->y_terminal * 40 + 20);

					settextstyle(17, 9, _T("Courier"));
					settextcolor(BLACK);
					outtextxy(685, 490, str_3);
					outtextxy(685, 510, str_1);
					outtextxy(780, 490, str_x_terminal), outtextxy(810, 490, str_y_terminal); //输出食客位置
					mission_music = 1;
					temp->x_start = -1;
					temp->y_start = -1;
					temp->x_terminal= -1;
					temp->y_terminal = -1;
				}
				break;
			}
		}
	}
	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}


unsigned __stdcall sound(void* pArguments)
{
	mciSendString(_T("open back.mp3 alias mymusic"), NULL, 0, NULL);	// 打开音乐
	mciSendString(_T("open money.mp3 alias themusic"), NULL, 0, NULL);	// 打开成功提示音乐
	mciSendString(_T("open warn.mp3 alias warn"), NULL, 0, NULL);	// 打开警告音乐
	while (!is_break)
	{
		if(deliver_music)
		{
			mciSendString(_T("play themusic from 0"), NULL, 0, NULL);//播放送货成功的提示音
			deliver_music = 0;
		}
	    if (mission_music)
		{
			mciSendString(_T("play mymusic from 0"), NULL, 0, NULL);					// 播放音乐
			mission_music = 0;
		}
		if (warn_music)
		{
			mciSendString(_T("play warn from 0"), NULL, 0, NULL);
			warn_music = 0;
		}
	}
	mciSendString(_T("close warn"), NULL, 0, NULL);	// 关闭警告音乐
	mciSendString(_T("close themusic"), NULL, 0, NULL);	// 关闭送货成功提示音
	mciSendString(_T("close mymusic"), NULL, 0, NULL);	// 关闭音乐
	_endthreadex(0);//线程完成时要调用_endthread
	return 0;
}

int main() {
	HANDLE hThread1;//用该进程处理鼠标输入时间
	HANDLE music;//加入一个进程用于音乐播放

	initialize(); //初始化函数

	hThread1 = (HANDLE)_beginthreadex(NULL, 0, getInput, NULL, 0, NULL);//开始鼠标监控线程
	music= (HANDLE)_beginthreadex(NULL, 0, sound, NULL, 0, NULL);//开始音乐响应进程

	solve();      //数据处理
	closegraph(); //按键关闭图形窗口

	WaitForSingleObject(hThread1, INFINITE);//等待线程结束
	WaitForSingleObject(sound, INFINITE);//等待线程结束

	CloseHandle(hThread1);//无须控制线程时删除此句柄，可防止内核对象泄露。
	CloseHandle(music);
	return 0;
}
