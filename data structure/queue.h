#include "data_t.h"					// data_t 사용

#ifndef QUEUE_H    // QUEUE_H가 정의되어 있지 않다면
#define QUEUE_H    // QUEUE_H 매크로 정의

typedef struct _QueueSingleNode _QueueSingleNode, * QueueSingleNode;   // 큐 노드 정의
typedef struct _QueueDoublyNode _QueueDoublyNode, * QueueDoublyNode;   // 큐 노드 정의

typedef struct _QueueField _QueueField,* QueueField;	// 큐의 내부 요소
typedef struct _DequeField _DequeField, * DequeField;	// 데큐의 내부 요소

typedef struct _Queue {
	is_success_t(*enQueue)(struct _Queue* self, data_t);// 데이터를 큐에 삽입
	data_t(*deQueue)(struct _Queue* self);			// 데이터를 반환 후 제거
	data_t(*peek)(struct _Queue* self);				// 데이터를 반환
	unsigned int(*length)(struct _Queue* self);		// 큐의 길이를 반환

	QueueField field;				// 큐의 요소
}_Queue, * Queue;					// 큐 구조체, 포인터 정의

Queue new_queue(void);				// 큐 생성 함수 정의
void queue_free(Queue, eBool_t is_deleted_data);// 큐 동적 할당 해제
void queue_print(Queue, char*(*fp)(data_t));	//큐 원소 출력

typedef struct _Deque {
	is_success_t(*append)(struct _Deque* self, data_t);// 데이터를 큐 리어에 삽입
	data_t(*pop)(struct _Deque* self);			// 꼬리의 데이터를 반환 후 제거
	data_t(*peek)(struct _Deque* self);			// 꼬리의 데이터를 반환
	is_success_t(*append_left)(struct _Deque* self, data_t);// 데이터를 큐 프론트에 삽입
	data_t(*pop_left)(struct _Deque* self);			// 프론트의 데이터를 반환 후 제거
	data_t(*peek_left)(struct _Deque* self);		// 프론트의 데이터를 반환
	unsigned int(*length)(struct _Deque* self);		// 큐의 길이를 반환

	DequeField field;				// 큐의 요소
}_Deque, * Deque;					// 큐 구조체, 포인터 정의

Deque new_deque(void);				// 큐 생성 함수 정의
void deque_free(Deque, eBool_t is_deleted_data);// 큐 동적 할당 해제
void deque_print(Deque, char* (*fp)(data_t));	//큐 원소 출력

#endif				// #ifndef QUEUE_H 끝
