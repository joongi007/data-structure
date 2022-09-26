#include "data_t.h"					// data_t ���

#ifndef QUEUE_H    // QUEUE_H�� ���ǵǾ� ���� �ʴٸ�
#define QUEUE_H    // QUEUE_H ��ũ�� ����

typedef struct _QueueSingleNode _QueueSingleNode, * QueueSingleNode;   // ť ��� ����
typedef struct _QueueDoublyNode _QueueDoublyNode, * QueueDoublyNode;   // ť ��� ����

typedef struct _QueueField _QueueField,* QueueField;	// ť�� ���� ���
typedef struct _DequeField _DequeField, * DequeField;	// ��ť�� ���� ���

typedef struct _Queue {
	is_success_t(*enQueue)(struct _Queue* self, data_t);// �����͸� ť�� ����
	data_t(*deQueue)(struct _Queue* self);			// �����͸� ��ȯ �� ����
	data_t(*peek)(struct _Queue* self);				// �����͸� ��ȯ
	unsigned int(*length)(struct _Queue* self);		// ť�� ���̸� ��ȯ

	QueueField field;				// ť�� ���
}_Queue, * Queue;					// ť ����ü, ������ ����

Queue new_queue(void);				// ť ���� �Լ� ����
void queue_free(Queue, eBool_t is_deleted_data);// ť ���� �Ҵ� ����
void queue_print(Queue, char*(*fp)(data_t));	//ť ���� ���

typedef struct _Deque {
	is_success_t(*append)(struct _Deque* self, data_t);// �����͸� ť ��� ����
	data_t(*pop)(struct _Deque* self);			// ������ �����͸� ��ȯ �� ����
	data_t(*peek)(struct _Deque* self);			// ������ �����͸� ��ȯ
	is_success_t(*append_left)(struct _Deque* self, data_t);// �����͸� ť ����Ʈ�� ����
	data_t(*pop_left)(struct _Deque* self);			// ����Ʈ�� �����͸� ��ȯ �� ����
	data_t(*peek_left)(struct _Deque* self);		// ����Ʈ�� �����͸� ��ȯ
	unsigned int(*length)(struct _Deque* self);		// ť�� ���̸� ��ȯ

	DequeField field;				// ť�� ���
}_Deque, * Deque;					// ť ����ü, ������ ����

Deque new_deque(void);				// ť ���� �Լ� ����
void deque_free(Deque, eBool_t is_deleted_data);// ť ���� �Ҵ� ����
void deque_print(Deque, char* (*fp)(data_t));	//ť ���� ���

#endif				// #ifndef QUEUE_H ��
