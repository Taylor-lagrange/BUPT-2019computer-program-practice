//���� �⾲��

#include "all.h"
unsigned __stdcall getInput(void* pArguments)
//�̺߳����ķ���ֵ��ָ�����ͣ��β�Ҳֻ����һ��
{
	missionptr temp = NULL;
	int x = 0, y = 0;
	temp = (missionptr)malloc(sizeof(mission));
	temp->is_complete = 0;
	temp->fetch_time = 0;
	int key = 0;
	char str_1[20] = "�������¶�����", str_2[20] = "�͹�λ�ã� ", str_3[20] = "ʳ��λ�ã� ", str_4[20] = "�¶�����ţ�";
	char str_x_start[3], str_y_start[3], str_x_terminal[3], str_y_terminal[3], str_count[3];
	MOUSEMSG m;
	while (!is_break)//�Ʋ��źŲ��������̲���ֹ
	{
		temp->number = cartoon_count;
		while (MouseHit())//�������Ϣ����ѭ��
		{
			m = GetMouseMsg();

			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN://���������Ϣ��
				x = m.x / 40;
				y = m.y / 40;
				if (x % 2 == 0 && y % 2 == 0 && 0 <= x && x <= 16 && 0 <= y && y <= 16) //�����Ϸ��Ҳ�Խ��
				{
					temp->x_start = x;
					temp->y_start = y;
					temp->order_time = time;
					key = 1;
				}
				break;
			case WM_LBUTTONUP://���������Ϣ
				x = m.x / 40;
				y = m.y / 40;
				if (x % 2 == 0 && y % 2 == 0 && 0 <= x && x <= 16 && 0 <= y && y <= 16 && key == 1) //�����Ϸ��Ҳ�Խ��
				{
					temp->x_terminal = x;
					temp->y_terminal = y;
					//queue_push(&mission_queue, temp); //���µ�����������
					mission_allocate(*temp);
					cartoon_count++;
					key = 0;
					setfillcolor(RGB(151, 192, 192));
					solidrectangle(780, 470, 850, 490); //������һ��������ַ���
					solidrectangle(685, 490, 850, 530); //�������������¶�������
					solidrectangle(685, 440, 850, 460); //�������¶�����š�
					_itoa_s(cartoon_count, str_count, 10);
					settextstyle(17, 9, _T("Courier"));
					settextcolor(BLACK);
					outtextxy(685, 440, str_4);
					outtextxy(780, 440, str_count),


					_itoa_s(temp->x_start, str_x_start, 10), _itoa_s(temp->y_start, str_y_start, 10);
					settextstyle(17, 9, _T("Courier"));
					settextcolor(BLACK);
					outtextxy(685, 470, str_2);
					outtextxy(780, 470, str_x_start), outtextxy(810, 470, str_y_start); //����͹�λ��
					_itoa_s(temp->x_terminal, str_x_terminal, 10), _itoa_s(temp->y_terminal, str_y_terminal, 10);

					setlinecolor(RED);	//�����ڲ͹ݺ�ʳ�ͼ仭��
					line(temp->x_start * 40 + 20, temp->y_start * 40 + 20, temp->x_terminal * 40 + 20, temp->y_terminal * 40 + 20);

					settextstyle(17, 9, _T("Courier"));
					settextcolor(BLACK);
					outtextxy(685, 490, str_3);
					outtextxy(685, 510, str_1);
					outtextxy(780, 490, str_x_terminal), outtextxy(810, 490, str_y_terminal); //���ʳ��λ��
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
	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}


unsigned __stdcall sound(void* pArguments)
{
	mciSendString(_T("open back.mp3 alias mymusic"), NULL, 0, NULL);	// ������
	mciSendString(_T("open money.mp3 alias themusic"), NULL, 0, NULL);	// �򿪳ɹ���ʾ����
	mciSendString(_T("open warn.mp3 alias warn"), NULL, 0, NULL);	// �򿪾�������
	while (!is_break)
	{
		if(deliver_music)
		{
			mciSendString(_T("play themusic from 0"), NULL, 0, NULL);//�����ͻ��ɹ�����ʾ��
			deliver_music = 0;
		}
	    if (mission_music)
		{
			mciSendString(_T("play mymusic from 0"), NULL, 0, NULL);					// ��������
			mission_music = 0;
		}
		if (warn_music)
		{
			mciSendString(_T("play warn from 0"), NULL, 0, NULL);
			warn_music = 0;
		}
	}
	mciSendString(_T("close warn"), NULL, 0, NULL);	// �رվ�������
	mciSendString(_T("close themusic"), NULL, 0, NULL);	// �ر��ͻ��ɹ���ʾ��
	mciSendString(_T("close mymusic"), NULL, 0, NULL);	// �ر�����
	_endthreadex(0);//�߳����ʱҪ����_endthread
	return 0;
}

int main() {
	HANDLE hThread1;//�øý��̴����������ʱ��
	HANDLE music;//����һ�������������ֲ���

	initialize(); //��ʼ������

	hThread1 = (HANDLE)_beginthreadex(NULL, 0, getInput, NULL, 0, NULL);//��ʼ������߳�
	music= (HANDLE)_beginthreadex(NULL, 0, sound, NULL, 0, NULL);//��ʼ������Ӧ����

	solve();      //���ݴ���
	closegraph(); //�����ر�ͼ�δ���

	WaitForSingleObject(hThread1, INFINITE);//�ȴ��߳̽���
	WaitForSingleObject(sound, INFINITE);//�ȴ��߳̽���

	CloseHandle(hThread1);//��������߳�ʱɾ���˾�����ɷ�ֹ�ں˶���й¶��
	CloseHandle(music);
	return 0;
}
