#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// ���� ���� ��� ����
struct _QueueSingleNode {
	QueueSingleNode next;		// ���� ����� �ּҸ� ������ ������
	data_t data;                // �����͸� ������ ���
};

// ���� ���� ��� ����
struct _QueueDoublyNode {
	QueueDoublyNode prev;		// ���� ����� �ּҸ� ������ ������
	QueueDoublyNode next;		// ���� ����� �ּҸ� ������ ������
	data_t data;                // �����͸� ������ ���
};

// �ʵ� ����ü ����
struct _QueueField {
	QueueSingleNode front;			// �����Ͱ� ������ ��
	QueueSingleNode rear;			// �����Ͱ� �߰��Ǵ� ��
	unsigned int length;			// ť�� ����
};

// �ʵ� ����ü ����
struct _DequeField {
	QueueDoublyNode front;			// �����Ͱ� ������ ��
	QueueDoublyNode rear;			// �����Ͱ� �߰��Ǵ� ��
	unsigned int length;			// ť�� ����
};

// �����͸� ť�� ����
is_success_t _queue_enQueue(Queue self, data_t data) {
	QueueSingleNode newNode = malloc(sizeof(_QueueSingleNode));// �� ��� ����
	if (!newNode) return FALSE;					 // �޸� Ȯ��
	newNode->data = data;						 // newNode �ʱ�ȭ
	newNode->next = NULL;						 // newNode �ʱ�ȭ
	if (self->field->front) {					 // ���� �����ϸ�
		self->field->rear->next = newNode;		 // �� ���� �߰�
		self->field->rear = newNode;			 // ���� ������ ���� ����
	}
	else {										 // ���� ���� ������
		self->field->front = newNode;			 // �� ����
		self->field->rear = newNode;			 // ���� ����
	}
	self->field->length++;				// ť ���� ����ȭ
	return TRUE;
}

// �����͸� ��ȯ �� ����
data_t _queue_deQueue(Queue self) {
	QueueSingleNode removeNode = self->field->front; // ���� ����� ���� ��� �ּҸ� ����
	if (!removeNode) return NULL;			// ť�� ����ִ��� Ȯ��
	self->field->front = removeNode->next;	// ���� ����� ���� ��忡 ������ ����� ���� ��带 ����
	data_t data = removeNode->data;			// �����ϱ� �� ������ ����
	free(removeNode);						// ��� �޸� ����
	self->field->length--;					// ť ���� ����ȭ
	return data;		 // ������ ����
}

// �����͸� ��ȯ
data_t _queue_peek(Queue self) {
	if (!self->field->front) return NULL;// ť�� ����ִ��� Ȯ��
	return self->field->front->data;	// ������ ����
}

// ť�� ���̸� ��ȯ
unsigned int _queue_length(Queue self) {
	return self->field->length;
}

// ť ���� �Լ�
Queue new_queue() {
	Queue newQueue = malloc(sizeof(_Queue));	// �� ť ����
	if (!newQueue) return NULL;// �޸� �Ҵ� Ȯ��
	QueueField newField = malloc(sizeof(_QueueField));	// �� ť ����
	if (!newField) { free(newQueue);  return NULL; }// �޸� �Ҵ� Ȯ��
	newQueue->enQueue = _queue_enQueue;			// �Լ� ����
	newQueue->deQueue = _queue_deQueue;			// �Լ� ����
	newQueue->peek = _queue_peek;			// �Լ� ����
	newQueue->length = _queue_length;		// �Լ� ����
	newQueue->field = newField;				// ����ü ����
	newQueue->field->front = NULL;			// front �ʱ�ȭ
	newQueue->field->rear = NULL;			// rear �ʱ�ȭ
	newQueue->field->length = 0;			// ������ ���� �ʱ�ȭ
	return newQueue;						// ���� ����
}

// ���� ���� �Ҵ� ����
void queue_free(Queue queue, eBool_t is_deleted_data) {
	data_t data;		// �ӽ� ������ ������
	unsigned int i = 0;
	for (i; i < queue->field->length; i++) {
		data = _queue_deQueue(queue);	// �̱� ��� ����
		if (is_deleted_data) {	// ������ ���Ÿ� ���ϸ� �Բ� ����
			free(data);
			data = NULL;
		}
	}
	free(queue->field);	// ���� ��� ����
	queue->field = NULL;// ���� ��� ������ �ʱ�ȭ
	free(queue);		// ť ����ü �Ҵ� ����
	queue = NULL;		// ������ �ʱ�ȭ
}

// ���� ��ҵ��� �ּ� ����
void queue_print(Queue queue, char* (*fp)(data_t)) {
	QueueSingleNode node = queue->field->front;
	printf("front");
	while (node) {
		if(fp)
			printf("-> %s", fp(node->data));
		else
			printf("-> %p", node->data);
		node = node->next;
	}
	printf("-> rear\n");
}

// �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

// �����͸� ��ť�� ������ ����
is_success_t _deque_append(Deque self, data_t data) {
	QueueDoublyNode newNode = malloc(sizeof(_QueueDoublyNode));// �� ��� ����
	if (!newNode) return FALSE;					 // �޸� Ȯ��
	newNode->data = data;						 // newNode �ʱ�ȭ
	newNode->prev = NULL;
	newNode->next = NULL;						 // newNode �ʱ�ȭ
	if (self->field->front) {					 // ���� �����ϸ�
		self->field->rear->next = newNode;		 // �� ���� �߰�
		newNode->prev = self->field->rear;		 // ���� ��� ����
		self->field->rear = newNode;			 // ���� ������ ���� ����
	}
	else {										 // ���� ���� ������
		self->field->front = newNode;			 // �� ����
		self->field->rear = newNode;			 // ���� ����
	}
	self->field->length++;				// ��ť ���� ����ȭ
	return TRUE;
}

// ��ť�� ���� �����͸� ��ȯ �� ����
data_t _deque_pop(Deque self) {
	QueueDoublyNode removeNode = self->field->rear; // ���� ���
	if (!removeNode) return NULL;			// ť�� ����ִ��� Ȯ��
	self->field->rear = removeNode->prev;	// ���� ����� ���� ��忡 ������ ����� ���� ��带 ����
	self->field->rear->next = NULL;			// ������ ���� ���� �׻� NULL
	data_t data = removeNode->data;			// �����ϱ� �� ������ ����
	free(removeNode);						// ��� �޸� ����
	self->field->length--;					// ��ť ���� ����ȭ
	return data;		 // ������ ����
}

// ������ �����͸� ��ȯ
data_t _deque_peek(Deque self) {
	if (!self->field->rear) return NULL;// ť�� ����ִ��� Ȯ��
	return self->field->rear->data;	// ������ ����
}

// �����͸� ��ť �Ӹ��� ����
is_success_t _deque_append_left(Deque self, data_t data) {
	QueueDoublyNode newNode = malloc(sizeof(_QueueDoublyNode));// �� ��� ����
	if (!newNode) return FALSE;					 // �޸� Ȯ��
	newNode->data = data;						 // newNode �ʱ�ȭ
	newNode->next = NULL;						 // newNode �ʱ�ȭ
	if (self->field->front) {					 // ���� �����ϸ�
		self->field->front->prev = newNode;		 // ���� ��� ���� 
		newNode->next = self->field->front;		 // �� �Ӹ� �߰�	 
		self->field->front = newNode;			 // ���� ������ ���� ����
	}
	else {										 // ���� ���� ������
		self->field->front = newNode;			 // �� ����
		self->field->rear = newNode;			 // ���� ����
	}
	self->field->length++;				// ��ť ���� ����ȭ
	return TRUE;
}

// �Ӹ� �����͸� ��ȯ �� ����
data_t _deque_pop_left(Deque self) {
	QueueDoublyNode removeNode = self->field->front; // ������
	if (!removeNode) return NULL;			// ��ť�� ����ִ��� Ȯ��
	self->field->front = removeNode->next;	// ���� ����� ���� ��忡 ������ ����� ���� ��带 ����
	data_t data = removeNode->data;			// �����ϱ� �� ������ ����
	free(removeNode);						// ��� �޸� ����
	self->field->length--;					// ��ť ���� ����ȭ
	return data;		 // ������ ����
}

// �Ӹ� �����͸� ��ȯ
data_t _deque_peek_left(Deque self) {
	if (!self->field->front) return NULL;// ��ť�� ����ִ��� Ȯ��
	return self->field->front->data;	// ������ ����
}

// ��ť�� ���̸� ��ȯ
unsigned int _deque_length(Deque self) {
	return self->field->length;
}

// ť ���� �Լ� ����
Deque new_deque(void) {
	Deque newDeque = malloc(sizeof(_Deque));	// �� ��ť ����
	if (!newDeque) return NULL;// �޸� �Ҵ� Ȯ��
	DequeField newField = malloc(sizeof(_DequeField));	// �� ��ť ��� ����
	if (!newField) { free(newDeque);  return NULL; }// �޸� �Ҵ� Ȯ��
	newDeque->append = _deque_append;		// �Լ� ����
	newDeque->pop = _deque_pop;				// �Լ� ����
	newDeque->peek = _deque_peek;			// �Լ� ����
	newDeque->append_left = _deque_append_left;	// �Լ� ����
	newDeque->pop_left = _deque_pop_left;	// �Լ� ����
	newDeque->peek_left = _deque_peek_left;	// �Լ� ����
	newDeque->length = _deque_length;		// �Լ� ����
	newDeque->field = newField;				// ����ü ����
	newDeque->field->front = NULL;			// front �ʱ�ȭ
	newDeque->field->rear = NULL;			// rear �ʱ�ȭ
	newDeque->field->length = 0;			// ������ ���� �ʱ�ȭ
	return newDeque;						// ���� ����
}

// ť ���� �Ҵ� ����
void deque_free(Deque deque, eBool_t is_deleted_data) {
	data_t data;		// �ӽ� ������ ������
	unsigned int i = 0;
	for (i; i < deque->field->length; i++) {
		data = _deque_pop(deque);	// �̱� ��� ����
		if (is_deleted_data) {	// ������ ���Ÿ� ���ϸ� �Բ� ����
			free(data);
			data = NULL;
		}
	}
	free(deque->field);	// ���� ��� ����
	deque->field = NULL;// ���� ��� ������ �ʱ�ȭ
	free(deque);		// ��ť ����ü �Ҵ� ����
	deque = NULL;		// ������ �ʱ�ȭ
}

//ť ���� ���
void deque_print(Deque deque, char* (*fp)(data_t)) {
	QueueDoublyNode node = deque->field->front;
	printf("front");
	while (node) {
		if (fp)
			printf("-> %s", fp(node->data));
		else
			printf("-> %p", node->data);
		node = node->next;
	}
	printf("-> rear\n");
}