//���ߣ��⾲�� ������ ���

#include"all.h"

//���������Ϣ�ı���
int time;          //��Ϊ�ܵ�ʱ���������¼ʱ��
int num_order;     //��¼�ӵ�����
int num_completed; //��¼��ɶ����ı���
int num_overtime;  //��¼��ʱ�Ķ�������
int money = 1000;         //��¼Ǯ������
int is_break;      //�������Ʋ�����������һ������ѭ��
int num_completing[20];                //���浱ǰʱ��ᵥ��ŵ�����
int num_overtiming[20];				//���浱ǰʱ�䳬ʱ����ŵ�����
int num_iscompleting;       //��¼��ǰʱ��ᵥ��
int num_isovertiming;		//��¼��ǰʱ�䳬ʱ��
int cartoon_count;//����ͳ�ƶ�������
int deliver_music;//�����߳��ͻ�ʱ֧��������
int mission_music;//�����߳��ͻ�������������
int warn_music;//���ڳ�ʱ��������
node put_matrix[19][19];//�������ͣ��״̬

//ÿһ�δ��������Ա����
int num_deliver_man = 0;            //�øñ�����ǿ��Ա������
deliver deliver_man[max_deliver_man];

//�ܵ��������
Linkqueue mission_queue;



