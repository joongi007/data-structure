#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// 단일 연결 노드 정의
struct _QueueSingleNode {
	QueueSingleNode next;		// 다음 노드의 주소를 저장할 포인터
	data_t data;                // 데이터를 저장할 멤버
};

// 단일 연결 노드 정의
struct _QueueDoublyNode {
	QueueDoublyNode prev;		// 이전 노드의 주소를 저장할 포인터
	QueueDoublyNode next;		// 다음 노드의 주소를 저장할 포인터
	data_t data;                // 데이터를 저장할 멤버
};

// 필드 구조체 정의
struct _QueueField {
	QueueSingleNode front;			// 데이터가 나가는 앞
	QueueSingleNode rear;			// 데이터가 추가되는 뒤
	unsigned int length;			// 큐의 길이
};

// 필드 구조체 정의
struct _DequeField {
	QueueDoublyNode front;			// 데이터가 나가는 앞
	QueueDoublyNode rear;			// 데이터가 추가되는 뒤
	unsigned int length;			// 큐의 길이
};

// 데이터를 큐에 삽입
is_success_t _queue_enQueue(Queue self, data_t data) {
	QueueSingleNode newNode = malloc(sizeof(_QueueSingleNode));// 새 노드 생성
	if (!newNode) return FALSE;					 // 메모리 확인
	newNode->data = data;						 // newNode 초기화
	newNode->next = NULL;						 // newNode 초기화
	if (self->field->front) {					 // 앞이 존재하면
		self->field->rear->next = newNode;		 // 새 꼬리 추가
		self->field->rear = newNode;			 // 현재 마지막 꼬리 갱신
	}
	else {										 // 앞이 현재 없으면
		self->field->front = newNode;			 // 앞 갱신
		self->field->rear = newNode;			 // 꼬리 갱신
	}
	self->field->length++;				// 큐 길이 동기화
	return TRUE;
}

// 데이터를 반환 후 제거
data_t _queue_deQueue(Queue self) {
	QueueSingleNode removeNode = self->field->front; // 기준 노드의 다음 노드 주소를 저장
	if (!removeNode) return NULL;			// 큐가 비어있는지 확인
	self->field->front = removeNode->next;	// 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정
	data_t data = removeNode->data;			// 제거하기 전 데이터 저장
	free(removeNode);						// 노드 메모리 해제
	self->field->length--;					// 큐 길이 동기화
	return data;		 // 데이터 리턴
}

// 데이터를 반환
data_t _queue_peek(Queue self) {
	if (!self->field->front) return NULL;// 큐가 비어있는지 확인
	return self->field->front->data;	// 데이터 리턴
}

// 큐의 길이를 반환
unsigned int _queue_length(Queue self) {
	return self->field->length;
}

// 큐 생성 함수
Queue new_queue() {
	Queue newQueue = malloc(sizeof(_Queue));	// 새 큐 생성
	if (!newQueue) return NULL;// 메모리 할당 확인
	QueueField newField = malloc(sizeof(_QueueField));	// 새 큐 생성
	if (!newField) { free(newQueue);  return NULL; }// 메모리 할당 확인
	newQueue->enQueue = _queue_enQueue;			// 함수 기입
	newQueue->deQueue = _queue_deQueue;			// 함수 기입
	newQueue->peek = _queue_peek;			// 함수 기입
	newQueue->length = _queue_length;		// 함수 기입
	newQueue->field = newField;				// 구조체 기입
	newQueue->field->front = NULL;			// front 초기화
	newQueue->field->rear = NULL;			// rear 초기화
	newQueue->field->length = 0;			// 스택의 길이 초기화
	return newQueue;						// 스택 리턴
}

// 스택 동적 할당 해제
void queue_free(Queue queue, eBool_t is_deleted_data) {
	data_t data;		// 임시 저장할 데이터
	unsigned int i = 0;
	for (i; i < queue->field->length; i++) {
		data = _queue_deQueue(queue);	// 싱글 노드 제거
		if (is_deleted_data) {	// 데이터 제거를 원하면 함꼐 제거
			free(data);
			data = NULL;
		}
	}
	free(queue->field);	// 내부 요소 해제
	queue->field = NULL;// 내부 요소 포인터 초기화
	free(queue);		// 큐 구조체 할당 해제
	queue = NULL;		// 포인터 초기화
}

// 스택 요소들의 주소 리턴
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

// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

// 데이터를 데큐의 꼬리에 삽입
is_success_t _deque_append(Deque self, data_t data) {
	QueueDoublyNode newNode = malloc(sizeof(_QueueDoublyNode));// 새 노드 생성
	if (!newNode) return FALSE;					 // 메모리 확인
	newNode->data = data;						 // newNode 초기화
	newNode->prev = NULL;
	newNode->next = NULL;						 // newNode 초기화
	if (self->field->front) {					 // 앞이 존재하면
		self->field->rear->next = newNode;		 // 새 꼬리 추가
		newNode->prev = self->field->rear;		 // 이전 노드 갱신
		self->field->rear = newNode;			 // 현재 마지막 꼬리 갱신
	}
	else {										 // 앞이 현재 없으면
		self->field->front = newNode;			 // 앞 갱신
		self->field->rear = newNode;			 // 꼬리 갱신
	}
	self->field->length++;				// 데큐 길이 동기화
	return TRUE;
}

// 데큐의 꼬리 데이터를 반환 후 제거
data_t _deque_pop(Deque self) {
	QueueDoublyNode removeNode = self->field->rear; // 지울 노드
	if (!removeNode) return NULL;			// 큐가 비어있는지 확인
	self->field->rear = removeNode->prev;	// 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정
	self->field->rear->next = NULL;			// 꼬리의 다음 노드는 항상 NULL
	data_t data = removeNode->data;			// 제거하기 전 데이터 저장
	free(removeNode);						// 노드 메모리 해제
	self->field->length--;					// 데큐 길이 동기화
	return data;		 // 데이터 리턴
}

// 꼬리의 데이터를 반환
data_t _deque_peek(Deque self) {
	if (!self->field->rear) return NULL;// 큐가 비어있는지 확인
	return self->field->rear->data;	// 데이터 리턴
}

// 데이터를 데큐 머리에 삽입
is_success_t _deque_append_left(Deque self, data_t data) {
	QueueDoublyNode newNode = malloc(sizeof(_QueueDoublyNode));// 새 노드 생성
	if (!newNode) return FALSE;					 // 메모리 확인
	newNode->data = data;						 // newNode 초기화
	newNode->next = NULL;						 // newNode 초기화
	if (self->field->front) {					 // 앞이 존재하면
		self->field->front->prev = newNode;		 // 이전 노드 갱신 
		newNode->next = self->field->front;		 // 새 머리 추가	 
		self->field->front = newNode;			 // 현재 마지막 꼬리 갱신
	}
	else {										 // 앞이 현재 없으면
		self->field->front = newNode;			 // 앞 갱신
		self->field->rear = newNode;			 // 꼬리 갱신
	}
	self->field->length++;				// 데큐 길이 동기화
	return TRUE;
}

// 머리 데이터를 반환 후 제거
data_t _deque_pop_left(Deque self) {
	QueueDoublyNode removeNode = self->field->front; // 지울노드
	if (!removeNode) return NULL;			// 데큐가 비어있는지 확인
	self->field->front = removeNode->next;	// 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정
	data_t data = removeNode->data;			// 제거하기 전 데이터 저장
	free(removeNode);						// 노드 메모리 해제
	self->field->length--;					// 데큐 길이 동기화
	return data;		 // 데이터 리턴
}

// 머리 데이터를 반환
data_t _deque_peek_left(Deque self) {
	if (!self->field->front) return NULL;// 데큐가 비어있는지 확인
	return self->field->front->data;	// 데이터 리턴
}

// 데큐의 길이를 반환
unsigned int _deque_length(Deque self) {
	return self->field->length;
}

// 큐 생성 함수 정의
Deque new_deque(void) {
	Deque newDeque = malloc(sizeof(_Deque));	// 새 데큐 생성
	if (!newDeque) return NULL;// 메모리 할당 확인
	DequeField newField = malloc(sizeof(_DequeField));	// 새 데큐 요소 생성
	if (!newField) { free(newDeque);  return NULL; }// 메모리 할당 확인
	newDeque->append = _deque_append;		// 함수 기입
	newDeque->pop = _deque_pop;				// 함수 기입
	newDeque->peek = _deque_peek;			// 함수 기입
	newDeque->append_left = _deque_append_left;	// 함수 기입
	newDeque->pop_left = _deque_pop_left;	// 함수 기입
	newDeque->peek_left = _deque_peek_left;	// 함수 기입
	newDeque->length = _deque_length;		// 함수 기입
	newDeque->field = newField;				// 구조체 기입
	newDeque->field->front = NULL;			// front 초기화
	newDeque->field->rear = NULL;			// rear 초기화
	newDeque->field->length = 0;			// 스택의 길이 초기화
	return newDeque;						// 스택 리턴
}

// 큐 동적 할당 해제
void deque_free(Deque deque, eBool_t is_deleted_data) {
	data_t data;		// 임시 저장할 데이터
	unsigned int i = 0;
	for (i; i < deque->field->length; i++) {
		data = _deque_pop(deque);	// 싱글 노드 제거
		if (is_deleted_data) {	// 데이터 제거를 원하면 함꼐 제거
			free(data);
			data = NULL;
		}
	}
	free(deque->field);	// 내부 요소 해제
	deque->field = NULL;// 내부 요소 포인터 초기화
	free(deque);		// 데큐 구조체 할당 해제
	deque = NULL;		// 포인터 초기화
}

//큐 원소 출력
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