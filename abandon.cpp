//IMAGE complete;
			//gui_stop();
			//loadimage(&deliver_man[num_deliver_man - 1].driver_image, "complete1.png");   //����ͼƬ
/*
gui_stop(i, deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].fetch_time);  //ͼ�����
stop_count++;



						//loadimage(&complete, "complete1.png");
						//putimage(40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_start, 40 * 40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_start, &complete);
						/*if ((deliver_man[i].x_location + deliver_man[i].y_location) - (aim_x + aim_y) ==-1)
						{
							if (deliver_man[i].stopflag1 == 0)
								deliver_man[i].stopflag1 = 1;
							else if (deliver_man[i].stopflag1 == 2)
								deliver_man[i].stopflag1 = 3;
						}												//��Ǹ�����Ա�����/�Ϸ�ȡ����
						else
						{
							if (deliver_man[i].stopflag2 == 0)
								deliver_man[i].stopflag2 = 1;
							else if (deliver_man[i].stopflag2 == 2)
								deliver_man[i].stopflag2 = 3;
						}								//��Ǹ�����Ա���Ҳ�/�·�ȡ����

						//��ͼ
					//putimage(40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].x_terminal, 40 * 40 * deliver_man[i].task[deliver_man[i].mission_queue[deliver_man[i].index_misson]].y_terminal, &complete);

					/*if ((deliver_man[i].x_location + deliver_man[i].y_location) - (aim_x + aim_y) == -1)
						{
							if (deliver_man[i].stopflag1 == 0)
								deliver_man[i].stopflag1 = 2;
							else if (deliver_man[i].stopflag1 == 1)
								deliver_man[i].stopflag1 = 3;
						}									//��Ǹ�����Ա�����/�Ϸ��͵���
						else
						{
							if (deliver_man[i].stopflag2 == 0)
								deliver_man[i].stopflag2 = 2;
							else if (deliver_man[i].stopflag2 == 1)
								deliver_man[i].stopflag2 = 3;
						}										//��Ǹ�����Ա���Ҳ�/�·��͵��� 


*/

/*
void gui_stop(int i, int flag) //ͣ��ʱ�Ķ������
{
	char timestr5[20] = "ͣ����";
	char timestr6[20] = "�͹ݣ�";
	char timestr7[20] = "ʳ�ͣ�";
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
/*printf("ʱ��: %d\n", time);
	printf("Ǯ: %d\n", money);
	printf("�ӵ���: %d\n", num_order);
	printf("�����: %d;	�ᵥ: ", num_completed);
	for (int i = 0; i <= num_iscompleting; i++)
		if (num_completing[i] != -1)
			printf("%d ", num_completing[i]);
	printf(";\n��ʱ��: %d; ��ʱ: ", num_overtime);
	for (int i = 0; i <= num_isovertiming; i++)
		if (num_overtiming[i] != -1)
			printf("%d	", num_overtiming[i]);
	printf(";\n");
	int i = 0; //������������
	while (i < num_deliver_man)
	{
		printf("����%dλ��: %d,%d; ͣ����", i, deliver_man[i].x_location, deliver_man[i].y_location);
		if (deliver_man[i].x_location % 2 == 0)
		{
			if (deliver_man[i].stopflag1 == 1)
				printf("�͹�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
			else if (deliver_man[i].stopflag1 == 2)
				printf("ʳ��%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
			else if (deliver_man[i].stopflag1 == 3)
				printf("�Ϳ�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);              //�ж��Ϸ��������
			if (deliver_man[i].stopflag2 == 1)
				printf("�͹�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
			else if (deliver_man[i].stopflag2 == 2)
				printf("ʳ��%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
			else if (deliver_man[i].stopflag2 == 3)
				printf("�Ϳ�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);				//�ж��·��������


		}             //�����Աλ��������������֮��ʱ
		else
		{
			if (deliver_man[i].stopflag1 == 1)
				printf("�͹�%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag1 == 2)
				printf("ʳ��%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag1 == 3)
				printf("�Ϳ�%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);					//�ж���ཨ�������
			if (deliver_man[i].stopflag2 == 1)
				printf("�͹�%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag2 == 2)
				printf("ʳ��%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
			else if (deliver_man[i].stopflag2 == 3)
				printf("�Ϳ�%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);				//�ж��Ҳཨ�����

		}				//�����Աλ��������������֮��ʱ
		i++;
		printf(";\n\n");


	}*/
/*
//��û���¶������������ж�����ɣ�����ѭ��
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
		if (queue_isempty(&mission_queue) && over&&time> mission_queue.rear->data->order_time)//���ж�βԪ��
			break;//һֱ���⣬��ʽ���п���ע�͵�
		//printf("time:%d\n\n", time);*/
		/*if (thread_lock == 0)
		{
			if (!_kbhit())
				thread_lock = 1;
		}*/
/*
		/*for (int i = 0; i < num_deliver_man; i++)
		{
			setfillcolor(RGB(207, 169, 114));     //������ 207 269 114
			//����ԭ���ķ��飬���뱳����ͬ����ɫ
			solidrectangle(40 * deliver_man[i].x_location, 40 * deliver_man[i].y_location, 40 * deliver_man[i].x_location + 40, 40 * deliver_man[i].y_location + 40);
		}*/

		/*int unique = 0;
		if (mission_queue.rear->data->order_time == time && unique==0)//���ж�βԪ��
		{
			flag = 1;
			unique = 1;
			num_order++;  //�ӵ�����һ
			mission_allocate(*(mission_queue.rear->data));
		}*/

		/*missionptr m = NULL; //����һ������ṹ�� ָ��
		FILE* fptr = NULL;   //�����ļ�ָ��
		int flag = 0;
		if (fopen_s(&fptr, "3.in", "r") != 0)
		{
			printf("File could not be opened\n"); //����ʧ�ܣ������������ʾ
			do
			{
				m = (missionptr)malloc(sizeof(mission)); //��ȡ��һ�����ݺ󣬴����µĽṹ�壬�����µĴ���ռ�
				if (m != NULL)
				{
					m->fetch_time = 0;//����״̬
					m->is_complete = 0;
					scanf_s("%d %d %d %d %d %d", &(m->number), &(m->order_time), &(m->x_start), &(m->y_start), &(m->x_terminal), &(m->y_terminal));
					queue_push(&mission_queue, m);//���µ�����������
				}
				else
					printf("wrong on malloc m!!");
			} while (getchar() != EOF);
		}
		else
		{
			if (fptr != NULL)//����ļ�ָ��Ϸ��������ļ�����
			{
				while (!feof(fptr)) //����ļ��Ƿ����
				{
					m = (missionptr)malloc(sizeof(mission)); //ÿ��ȡ�����з�ʱ�򴴽�һ���µĽṹ�壬�����µĴ���ռ�
					if (m != NULL)//���䲻�ɹ������ʾ��Ϣ
					{
						m->fetch_time = 0;//����״̬
						m->is_complete = 0;
						fscanf_s(fptr, "%d %d %d %d %d %d", &(m->number), &(m->order_time), &(m->x_start), &(m->y_start), &(m->x_terminal), &(m->y_terminal));//��ȡ����
						queue_push(&mission_queue, m);			 //���µ�����������
					}
					else
						printf("wrong on malloc m!!");
				}
				fclose(fptr);
			}
			else
				printf("wrong on fptr != NULL");
		}*/