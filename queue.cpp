//���ߣ����

#include "all.h"


void queue_create(Linkqueue* q) //����һ���ն���
{
	q->front = q->rear = (Qptr)malloc(sizeof(Queue));
	if (!q->front)
		exit(0);
	q->front->next = NULL;
}

int queue_push(Linkqueue* q, missionptr join) //��һ��missionԪ�ؼ������queue�У�����ֵ����Ƿ���ӳɹ�����ӳɹ�����1�����򷵻�0
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

missionptr queue_top(Linkqueue * q) //���ض��е�һ��Ԫ��
{
	if (q->front == q->rear)
		return NULL;
	else
		return q->front->next->data;
}
int queue_pop(Linkqueue * q) //����ͷԪ�س���
{
	Qptr p;
	if (q->front == q->rear)
		return 0;
	p = q->front->next;
	q->front->next = p->next;
	if (q->rear == p)
		q->rear = q->front; //��p��Ϊ���һ�����ݣ���ͷβָ��ָ��ͬһλ��
	free(p);
	return 1;
}

int queue_isempty(Linkqueue * q) //�ж϶����Ƿ�Ϊ��
{
	if (q->front->next == NULL)
		return 1;
	else
		return 0;
}

int queue_size(Linkqueue * q) //���ض���Ԫ�صĸ���
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