//���ߣ����
#include"all.h"
void add_deliver()
{
	while (money >= 400)                           //���Ǯ������400�������µ�����
	{
		money -= 300;
		num_deliver_man += 1;                           //Ǯ����300�����Ա����+1��
		memset(deliver_man[num_deliver_man - 1].mission_queue, -1, sizeof(deliver_man[num_deliver_man - 1].mission_queue));
		deliver_man[num_deliver_man - 1].x_location= initial_x_location;
		deliver_man[num_deliver_man - 1].y_location= initial_y_location;
		deliver_man[num_deliver_man - 1].index_misson = 0;
		deliver_man[num_deliver_man - 1].num_mission = 0;
		deliver_man[num_deliver_man - 1].is_allocate_new = 0;

		loadimage(&deliver_man[num_deliver_man - 1].driver_image, "driver.png");   //����ͼƬ
		putimage(40* initial_x_location, 40* initial_y_location, &deliver_man[num_deliver_man - 1].driver_image);

		for (int i = 0; i < max_dispose; i++)
			deliver_man[num_deliver_man - 1].task[i].is_complete = 1;
	}
}
