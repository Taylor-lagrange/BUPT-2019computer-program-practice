//���ߣ����

#include "all.h"
void print()
{
	FILE* Fptr;
	if (fopen_s(&Fptr, "output.txt", "a+") != 0)
		printf("can't open the source file\n");
	else
	{
		if (Fptr != 0)
		{
			fprintf(Fptr, "ʱ��: %d\n", time);
			fprintf(Fptr, "Ǯ: %d\n", money);
			fprintf(Fptr, "�ӵ���: %d\n", num_order);
			fprintf(Fptr, "�����: %d;	�ᵥ: ", num_completed);
			for (int i = 0; i <= num_iscompleting; i++)
				if (num_completing[i] != -1)
					fprintf(Fptr, "%d ", num_completing[i]);
			fprintf(Fptr, ";\n��ʱ��: %d; ��ʱ: ", num_overtime);
			for (int i = 0; i <= num_isovertiming; i++)
				if (num_overtiming[i] != -1)
					fprintf(Fptr, "%d	", num_overtiming[i]);
			fprintf(Fptr, ";\n");
			int i = 0; //������������
			while (i < num_deliver_man)
			{
				fprintf(Fptr, "����%dλ��: %d,%d; ͣ����", i, deliver_man[i].x_location, deliver_man[i].y_location);
				if (deliver_man[i].x_location % 2 == 0)
				{
					if (deliver_man[i].stopflag1 == 1)
						fprintf(Fptr, "�͹�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
					else if (deliver_man[i].stopflag1 == 2)
						fprintf(Fptr, "ʳ��%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
					else if (deliver_man[i].stopflag1 == 3)
						fprintf(Fptr, "�Ϳ�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);              //�ж��Ϸ��������
					if (deliver_man[i].stopflag2 == 1)
						fprintf(Fptr, "�͹�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
					else if (deliver_man[i].stopflag2 == 2)
						fprintf(Fptr, "ʳ��%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
					else if (deliver_man[i].stopflag2 == 3)
						fprintf(Fptr, "�Ϳ�%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);				//�ж��·��������


				}             //�����Աλ��������������֮��ʱ
				else
				{
					if (deliver_man[i].stopflag1 == 1)
						fprintf(Fptr, "�͹�%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag1 == 2)
						fprintf(Fptr, "ʳ��%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag1 == 3)
						fprintf(Fptr, "�Ϳ�%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);					//�ж���ཨ�������
					if (deliver_man[i].stopflag2 == 1)
						fprintf(Fptr, "�͹�%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag2 == 2)
						fprintf(Fptr, "ʳ��%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag2 == 3)
						fprintf(Fptr, "�Ϳ�%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);				//�ж��Ҳཨ�����

				}				//�����Աλ��������������֮��ʱ
				i++;
				fprintf(Fptr, ";\n");
			}
			fprintf(Fptr, "\n");
			fclose(Fptr);
		}
	}
}