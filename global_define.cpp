//作者：吴静迪 蒋明君 王宇航

#include"all.h"

//保存输出信息的变量
int time;          //作为总的时间变量，记录时间
int num_order;     //记录接单数量
int num_completed; //记录完成订单的变量
int num_overtime;  //记录超时的订单数量
int money = 1000;         //记录钱的数量
int is_break;      //若出现破产条件将其置一，跳出循环
int num_completing[20];                //储存当前时间结单编号的数组
int num_overtiming[20];				//储存当前时间超时单编号的数组
int num_iscompleting;       //记录当前时间结单数
int num_isovertiming;		//记录当前时间超时数
int cartoon_count;//用于统计订单数量
int deliver_music;//用于线程送货时支付宝音乐
int mission_music;//用于线程送货美团外卖音乐
int warn_music;//用于超时订单警告
node put_matrix[19][19];//用于输出停靠状态

//每一次处理的外卖员数组
int num_deliver_man = 0;            //用该变量标记快递员的人数
deliver deliver_man[max_deliver_man];

//总的任务队列
Linkqueue mission_queue;



