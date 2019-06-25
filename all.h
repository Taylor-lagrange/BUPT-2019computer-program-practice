#pragma once  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <process.h>   //创建线程函数头文件
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")		//为了在之中加入音乐

//程序符号常量的定义
#define max_dispose 30         //设置为一个外卖员处理订单的最大数量
#define max_deliver_man 100    //设置为外卖员数组的大小，即预计会招快递员的最大人数
#define inf 0x3f3f3f3f         //定义可能为数组赋的最大值
#define dead_line 30           //超过这个时间就会被认为超时
#define total_dead_line 60     //超过这个时间限制直接破产
#define initial_x_location 9   //骑手初始x坐标
#define initial_y_location 8   //骑手初始y坐标
#define warning 5              //跨区域骑手预警值
#define deep_dsf 8            //限制dsf算法最大搜索深度，控制时间复杂度

//一个任务的信息记录
typedef struct
{
	int number = 0;          //订单编号
	int order_time = 0;      //下单时间
	int x_start = -1;    //餐馆x坐标
	int y_start = -1;    //餐馆y坐标
	int x_terminal = -1; //食客x坐标
	int y_terminal = -1; //食客y坐标
	int fetch_time = 0;  //标记该订单被取走的时间，如果订单还未被取走fetch_time==0
	int is_complete = 1; //如果该变量为1说明完成了任务，下一个插入外卖员任务队列直接插在这,一开始全初始化为一，标记为空订单
} mission;

//对于外卖输出的记录
typedef struct
{
	int count = 0;//作为计数变量，0不存值，0表示这个点没有订单
	int deliver_man_i[20];//快递员编号
	int num_deliver[20];//存该订单的订单号；
	int is_done[20];//作为bool变量标记是取单还是送单
}node;

//一个外卖员的结构体
typedef struct
{
	int x_location = initial_x_location; //外卖员x坐标
	int y_location = initial_y_location; //外卖员y坐标
	int num_mission = 0;                 //外卖员的任务数量
	int mission_queue[max_dispose * 2] = { -1 };  //标记外卖员的任务队列，每完成一个任务index_misson++
	int index_misson = 0;                //标记任务进行到哪一个
	int is_allocate_new = 0;             //是否在一个时间段内被分配了新任务
	mission task[max_dispose];           //该外卖员处理订单列表
	int stopflag1;					//代表外卖员左边/上边的停靠情况							
	int stopflag2;					//代表外卖员右边/下边的停靠情况	

	IMAGE  driver_image;    
} deliver;



//queue
typedef mission* missionptr;
typedef struct queue
{
	missionptr data; //队列存储信息为任务的指针
	struct queue* next;

} Queue;
typedef Queue* Qptr;
typedef struct Linkqueue
{
	Qptr front, rear; //创建头尾指针
} Linkqueue;
void queue_create(Linkqueue* q);               //创建一个空队列
int queue_push(Linkqueue* q, missionptr join); //将一个mission元素加入队列queue中，返回值标记是否入队成功，入队成功返回1，否则返回0
missionptr queue_top(Linkqueue* q);            //返回队列第一个元素
int queue_pop(Linkqueue* q);                   //队列头元素出队
int queue_isempty(Linkqueue* q);               //判断是否队空
int queue_size(Linkqueue* q);                  //返回队列元素的个数




//main
void initialize(); //初始化函数
void solve();      //数据处理

//dsf
void order_dispose(int man);           //处理订单调用函数,num是对订单进行重新进行路径规划的外卖员编号
void dsf(int man, int deep, int dead); //在订单内寻找最短遍历图的算法

//solve
void mission_allocate(mission dispose);//将订单分配给合适的快递员
int predict(mission dispose, deliver man);//通过深搜赋权，找到目标最优骑手
void state_update();//状态更新
void print(); //每一个时间单位输出状态

//gui
void innitial_map();   //地图及右侧文字输出的初始化
void map_print();    //地图、骑手等图片元素的刷新
void stop_print(int total, int deliver_man_i, int num_deliver, int is_done,int x,int y);  //停靠时图片及文字信息的输出
void gui_line(int x_start,int y_start,int x_ter,int y_ter);


//other
void add_deliver(); //买入骑手
int distance_spent(int x1, int x2, int y1, int y2);//dsf中用于距离的测算


//下面是对全局变量的引用
//保存输出信息的变量
extern int time;          //作为总的时间变量，记录时间
extern int num_order;     //记录接单数量
extern int num_completed; //记录完成订单的变量
extern int num_overtime;  //记录超时的订单数量
extern int money;         //记录钱的数量
extern int is_break;      //若出现破产条件将其置一，跳出循环
extern int num_completing[20];                //储存当前时间结单编号的数组
extern int num_overtiming[20];				//储存当前时间超时单编号的数组
extern int num_iscompleting;       //记录当前时间结单数
extern int num_isovertiming;		//记录当前时间超时数
extern int cartoon_count;//用于统计订单数量
extern int deliver_music;//用于线程送货时支付宝音乐
extern int mission_music;//用于线程送货美团外卖音乐
extern int warn_music;//用于超时订单警告
extern node put_matrix[19][19];//用于输出停靠状态



//每一次处理的外卖员数组
extern int num_deliver_man;            //用该变量标记快递员的人数
extern deliver deliver_man[max_deliver_man];




//总的任务队列
extern Linkqueue mission_queue;