//作者：蒋明君

#include "all.h"
void solve()
{
	do
	{
		int flag = 0; //一个标记变量，标记while循环是否运行，来决定是否进行骑手路径优化
		/*while (!queue_isempty(&mission_queue))
		{
			flag = 1;
			num_order++;  //接单数加一
			mission_allocate(*queue_top(&mission_queue));
			queue_pop(&mission_queue);  //队列头元素出队
		}
		if (flag) //若flag==1重新规划路径*/

		for (int i = 0; i < num_deliver_man; i++)
			if (deliver_man[i].is_allocate_new)
			{
					deliver_man[i].is_allocate_new = 0;
					order_dispose(i);
			}
		Sleep(2000);  //每次变化位置前间隔2s
		state_update();
		map_print();
		//print();注释掉print不生成output文件
		if (is_break)
			break;
	} while (++time); //每次更新时间,注意自加操作顺序
}
