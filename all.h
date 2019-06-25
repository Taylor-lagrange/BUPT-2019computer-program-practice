#pragma once  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <process.h>   //�����̺߳���ͷ�ļ�
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")		//Ϊ����֮�м�������

//������ų����Ķ���
#define max_dispose 30         //����Ϊһ������Ա���������������
#define max_deliver_man 100    //����Ϊ����Ա����Ĵ�С����Ԥ�ƻ��п��Ա���������
#define inf 0x3f3f3f3f         //�������Ϊ���鸳�����ֵ
#define dead_line 30           //�������ʱ��ͻᱻ��Ϊ��ʱ
#define total_dead_line 60     //�������ʱ������ֱ���Ʋ�
#define initial_x_location 9   //���ֳ�ʼx����
#define initial_y_location 8   //���ֳ�ʼy����
#define warning 5              //����������Ԥ��ֵ
#define deep_dsf 8            //����dsf�㷨���������ȣ�����ʱ�临�Ӷ�

//һ���������Ϣ��¼
typedef struct
{
	int number = 0;          //�������
	int order_time = 0;      //�µ�ʱ��
	int x_start = -1;    //�͹�x����
	int y_start = -1;    //�͹�y����
	int x_terminal = -1; //ʳ��x����
	int y_terminal = -1; //ʳ��y����
	int fetch_time = 0;  //��Ǹö�����ȡ�ߵ�ʱ�䣬���������δ��ȡ��fetch_time==0
	int is_complete = 1; //����ñ���Ϊ1˵�������������һ����������Ա�������ֱ�Ӳ�����,һ��ʼȫ��ʼ��Ϊһ�����Ϊ�ն���
} mission;

//������������ļ�¼
typedef struct
{
	int count = 0;//��Ϊ����������0����ֵ��0��ʾ�����û�ж���
	int deliver_man_i[20];//���Ա���
	int num_deliver[20];//��ö����Ķ����ţ�
	int is_done[20];//��Ϊbool���������ȡ�������͵�
}node;

//һ������Ա�Ľṹ��
typedef struct
{
	int x_location = initial_x_location; //����Աx����
	int y_location = initial_y_location; //����Աy����
	int num_mission = 0;                 //����Ա����������
	int mission_queue[max_dispose * 2] = { -1 };  //�������Ա��������У�ÿ���һ������index_misson++
	int index_misson = 0;                //���������е���һ��
	int is_allocate_new = 0;             //�Ƿ���һ��ʱ����ڱ�������������
	mission task[max_dispose];           //������Ա�������б�
	int stopflag1;					//��������Ա���/�ϱߵ�ͣ�����							
	int stopflag2;					//��������Ա�ұ�/�±ߵ�ͣ�����	

	IMAGE  driver_image;    
} deliver;



//queue
typedef mission* missionptr;
typedef struct queue
{
	missionptr data; //���д洢��ϢΪ�����ָ��
	struct queue* next;

} Queue;
typedef Queue* Qptr;
typedef struct Linkqueue
{
	Qptr front, rear; //����ͷβָ��
} Linkqueue;
void queue_create(Linkqueue* q);               //����һ���ն���
int queue_push(Linkqueue* q, missionptr join); //��һ��missionԪ�ؼ������queue�У�����ֵ����Ƿ���ӳɹ�����ӳɹ�����1�����򷵻�0
missionptr queue_top(Linkqueue* q);            //���ض��е�һ��Ԫ��
int queue_pop(Linkqueue* q);                   //����ͷԪ�س���
int queue_isempty(Linkqueue* q);               //�ж��Ƿ�ӿ�
int queue_size(Linkqueue* q);                  //���ض���Ԫ�صĸ���




//main
void initialize(); //��ʼ������
void solve();      //���ݴ���

//dsf
void order_dispose(int man);           //���������ú���,num�ǶԶ����������½���·���滮������Ա���
void dsf(int man, int deep, int dead); //�ڶ�����Ѱ����̱���ͼ���㷨

//solve
void mission_allocate(mission dispose);//��������������ʵĿ��Ա
int predict(mission dispose, deliver man);//ͨ�����Ѹ�Ȩ���ҵ�Ŀ����������
void state_update();//״̬����
void print(); //ÿһ��ʱ�䵥λ���״̬

//gui
void innitial_map();   //��ͼ���Ҳ���������ĳ�ʼ��
void map_print();    //��ͼ�����ֵ�ͼƬԪ�ص�ˢ��
void stop_print(int total, int deliver_man_i, int num_deliver, int is_done,int x,int y);  //ͣ��ʱͼƬ��������Ϣ�����
void gui_line(int x_start,int y_start,int x_ter,int y_ter);


//other
void add_deliver(); //��������
int distance_spent(int x1, int x2, int y1, int y2);//dsf�����ھ���Ĳ���


//�����Ƕ�ȫ�ֱ���������
//���������Ϣ�ı���
extern int time;          //��Ϊ�ܵ�ʱ���������¼ʱ��
extern int num_order;     //��¼�ӵ�����
extern int num_completed; //��¼��ɶ����ı���
extern int num_overtime;  //��¼��ʱ�Ķ�������
extern int money;         //��¼Ǯ������
extern int is_break;      //�������Ʋ�����������һ������ѭ��
extern int num_completing[20];                //���浱ǰʱ��ᵥ��ŵ�����
extern int num_overtiming[20];				//���浱ǰʱ�䳬ʱ����ŵ�����
extern int num_iscompleting;       //��¼��ǰʱ��ᵥ��
extern int num_isovertiming;		//��¼��ǰʱ�䳬ʱ��
extern int cartoon_count;//����ͳ�ƶ�������
extern int deliver_music;//�����߳��ͻ�ʱ֧��������
extern int mission_music;//�����߳��ͻ�������������
extern int warn_music;//���ڳ�ʱ��������
extern node put_matrix[19][19];//�������ͣ��״̬



//ÿһ�δ��������Ա����
extern int num_deliver_man;            //�øñ�����ǿ��Ա������
extern deliver deliver_man[max_deliver_man];




//�ܵ��������
extern Linkqueue mission_queue;