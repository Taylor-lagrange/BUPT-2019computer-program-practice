//���ߣ�������
#include "all.h"

IMAGE map;
IMAGE time1, money1, complete1, overtime1, arrive;   //ͼƬ�����ز�

void innitial_map()   //��ͼ���Ҳ���������ĳ�ʼ��
{
	initgraph(1030, 680);          //��ʼ��ͼ�δ���
	char timestr1[20] = "ʱ�䵥λ��", moneystr1[20] = "��Ǯ����  ", completestr1[20] = "��ɵ�����", overtimestr1[20] = "��ʱ����:";
	setbkcolor(RGB(151, 192, 192));
	cleardevice();     //�ñ���ɫ��䴰��
	loadimage(NULL, _T("map.png"));  //���ص�ͼ����

	loadimage(&time1, "time1.png");         //����ͼƬ��ʱ��
	loadimage(&money1, "money1.png");       //����ͼƬ��Ǯ��
	loadimage(&complete1, "complete1.png"); //����ͼƬ���Ժ�
	loadimage(&overtime1, "overtime1.png"); //����ͼƬ�����
	//��ͼƬ����ָ��λ��
	putimage(685, 30, &time1);
	putimage(685, 130, &money1);
	putimage(685, 230, &complete1);
	putimage(685, 330, &overtime1);
	//�Ҳ������������
	settextstyle(17, 9, _T("Courier"));
	settextcolor(BLACK);
	outtextxy(685, 90, timestr1);
	outtextxy(685, 190, moneystr1);
	outtextxy(685, 290, completestr1);
	outtextxy(685, 390, overtimestr1);
	for (int i = 0; i < 19; i++)//�Ըþ�������ʼ������ʼΪ��û�ж���
		for (int j = 0; j < 19; j++)
			put_matrix[i][j].count = 0;
}


void map_print()  //��ͼ�����ֵ�ͼƬԪ�ص�ˢ��
{
	char timestr[20], moneystr[20], completestr[20], overtimestr[20];  //�ַ��������Դ洢�����������Ϣ
	IMAGE map;
	loadimage(NULL, _T("map.png"));  //��ͼ����
	Linkqueue q = mission_queue; //�������У�����δ���Ӷ�������
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
		//���ƿ��Ա��λ��
		putimage(40 * deliver_man[i].x_location, 40 * deliver_man[i].y_location, &deliver_man[i].driver_image);
	}

	//������ת��Ϊ�ַ���
	_itoa_s(time, timestr, 10);
	_itoa_s(money, moneystr, 10);
	_itoa_s(num_completed, completestr, 10);
	_itoa_s(num_overtime, overtimestr, 10);
	//ʵʱ���������Ŀ
	outtextxy(785, 90, timestr);
	setfillcolor(RGB(151, 192, 192));   
	solidrectangle(785, 190, 820, 210); //�����θ��Ǿ���Ϣ
	outtextxy(785, 190, moneystr);
	outtextxy(785, 290, completestr);
	outtextxy(785, 390, overtimestr);
	setfillcolor(RGB(151, 192, 192));
	solidrectangle(865, 90, 1030, 680); //�����θ��Ǿ���Ϣ
	int tot = 0;  //���������ͣ����Ϣ
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
		{
			for (int k = 1; k <= put_matrix[i][j].count; k++)  //������ǰ�����ͣ����Ϣ
			{
				tot++;//tot��һ��ʼ
				stop_print(tot, put_matrix[i][j].deliver_man_i[k], put_matrix[i][j].num_deliver[k], put_matrix[i][j].is_done[k], i, j);
			}
			put_matrix[i][j].count = 0;//�õ������count��0
		}
}


void stop_print(int total, int deliver_man_i, int num_deliver, int is_done, int x, int y)  //ͣ��ʱͼƬ��������Ϣ�����
{
	char timestr5[20] = "ͣ����";
	char timestr6[20] = "�͹ݣ�";
	char timestr7[20] = "ʳ�ͣ�";
	char timestr8[20] = "���ֱ�ţ�";
	char timestr9[20] = "�����ţ�";
	char str_stop_x[3], str_stop_y[3];
	char str_deliver[3], str_order[3];  //�����ַ����鴢��������Ϣ
	settextstyle(17, 9, _T("Courier"));
	settextcolor(BLACK);

	loadimage(&arrive, "arrive.jpg"); //���ء�ͣ����ͼƬ
	putimage(40 * x, 40 * y, &arrive);

	outtextxy(865, 90, timestr5);  //������֡�ͣ����
	_itoa_s(deliver_man_i, str_deliver, 10);
	outtextxy(865, 90 * total+20, timestr8);  //������ֺ�
	outtextxy(960, 90 * total + 20, str_deliver);
	_itoa_s(num_deliver, str_order, 10);
	outtextxy(865, 90 * total+40, timestr9);  //�������
	outtextxy(940, 90 * total + 40, str_order);
	if(is_done == 0)   //��ͣ����Ϊ�͹�
		outtextxy(865, 90*total +60, timestr6);
	else     //��ͣ����Ϊʳ��
		outtextxy(865, 90*total +60, timestr7);
	//��ͣ����Ϊ�Ϳͣ����ͬʱ���������Ϣ
	_itoa_s(x, str_stop_x, 10);
	_itoa_s(y, str_stop_y, 10);
	outtextxy(940, 90 * total + 60, str_stop_x), outtextxy(995, 90 * total + 60, str_stop_y);
}


