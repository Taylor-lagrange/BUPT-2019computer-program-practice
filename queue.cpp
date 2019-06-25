//作者：王宇航

#include "all.h"


void queue_create(Linkqueue* q) //创建一个空队列
{
	q->front = q->rear = (Qptr)malloc(sizeof(Queue));
	if (!q->front)
		exit(0);
	q->front->next = NULL;
}

int queue_push(Linkqueue* q, missionptr join) //将一个mission元素加入队列queue中，返回值标记是否入队成功，入队成功返回1，否则返回0
{
	Qptr p;
	p = (Qptr)malloc(sizeof(Queue));
	if (p == NULL)
		exit(0);
	p->data = join;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
	return 1;
}

missionptr queue_top(Linkqueue * q) //返回队列第一个元素
{
	if (q->front == q->rear)
		return NULL;
	else
		return q->front->next->data;
}
int queue_pop(Linkqueue * q) //队列头元素出队
{
	Qptr p;
	if (q->front == q->rear)
		return 0;
	p = q->front->next;
	q->front->next = p->next;
	if (q->rear == p)
		q->rear = q->front; //若p即为最后一组数据，则将头尾指针指向同一位置
	free(p);
	return 1;
}

int queue_isempty(Linkqueue * q) //判断队列是否为空
{
	if (q->front->next == NULL)
		return 1;
	else
		return 0;
}

int queue_size(Linkqueue * q) //返回队列元素的个数
{
	int n = 0;
	Qptr cur = q->front;
	while (cur != q->rear)
	{
		n++;
		cur = cur->next;
	}
	return n;
}