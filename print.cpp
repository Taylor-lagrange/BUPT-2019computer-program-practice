//作者：王宇航

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
			fprintf(Fptr, "时间: %d\n", time);
			fprintf(Fptr, "钱: %d\n", money);
			fprintf(Fptr, "接单数: %d\n", num_order);
			fprintf(Fptr, "完成数: %d;	结单: ", num_completed);
			for (int i = 0; i <= num_iscompleting; i++)
				if (num_completing[i] != -1)
					fprintf(Fptr, "%d ", num_completing[i]);
			fprintf(Fptr, ";\n超时数: %d; 罚时: ", num_overtime);
			for (int i = 0; i <= num_isovertiming; i++)
				if (num_overtiming[i] != -1)
					fprintf(Fptr, "%d	", num_overtiming[i]);
			fprintf(Fptr, ";\n");
			int i = 0; //计数骑手数量
			while (i < num_deliver_man)
			{
				fprintf(Fptr, "骑手%d位置: %d,%d; 停靠：", i, deliver_man[i].x_location, deliver_man[i].y_location);
				if (deliver_man[i].x_location % 2 == 0)
				{
					if (deliver_man[i].stopflag1 == 1)
						fprintf(Fptr, "餐馆%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
					else if (deliver_man[i].stopflag1 == 2)
						fprintf(Fptr, "食客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);
					else if (deliver_man[i].stopflag1 == 3)
						fprintf(Fptr, "餐客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location + 1);              //判断上方建筑情况
					if (deliver_man[i].stopflag2 == 1)
						fprintf(Fptr, "餐馆%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
					else if (deliver_man[i].stopflag2 == 2)
						fprintf(Fptr, "食客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);
					else if (deliver_man[i].stopflag2 == 3)
						fprintf(Fptr, "餐客%d %d ", deliver_man[i].x_location, deliver_man[i].y_location - 1);				//判断下方建筑情况


				}             //当快递员位于两建筑物上下之间时
				else
				{
					if (deliver_man[i].stopflag1 == 1)
						fprintf(Fptr, "餐馆%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag1 == 2)
						fprintf(Fptr, "食客%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag1 == 3)
						fprintf(Fptr, "餐客%d %d ", deliver_man[i].x_location + 1, deliver_man[i].y_location);					//判断左侧建筑物情况
					if (deliver_man[i].stopflag2 == 1)
						fprintf(Fptr, "餐馆%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag2 == 2)
						fprintf(Fptr, "食客%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);
					else if (deliver_man[i].stopflag2 == 3)
						fprintf(Fptr, "餐客%d %d ", deliver_man[i].x_location - 1, deliver_man[i].y_location);				//判断右侧建筑情况

				}				//当快递员位于两建筑物左右之间时
				i++;
				fprintf(Fptr, ";\n");
			}
			fprintf(Fptr, "\n");
			fclose(Fptr);
		}
	}
}