#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// 단일 연결 노드 정의
struct _StackSingleNode {
	StackSingleNode next;		// 다음 노드의 주소를 저장할 포인터
	data_t data;                // 데이터를 저장할 멤버
};

// 필드 구조체 정의
struct _StackField {
	StackSingleNode node;		// 단일 연결 노드
	unsigned int length;		// 스택의 길이
};

// 데이터를 스택에 삽입
is_success_t _stack_push(Stack self, data_t data) {
	StackSingleNode newNode = malloc(sizeof(_StackSingleNode));    // 새 노드 생성
	if (!newNode) return FALSE;			// 메모리 확인
	newNode->next = self->field->node;	// 새 노드의 다음 노드에 기준 노드의 다음 노드를 지정
	newNode->data = data;				// 데이터 저장
	self->field->node = newNode;		// 기준 노드의 다음 노드에 새 노드를 지정
	self->field->length++;				// 스택 길이 동기화
	return TRUE;
}

// 데이터를 반환 후 제거
data_t _stack_pop(Stack self) {
	StackSingleNode removeNode = self->field->node;// 기준 노드의 다음 노드 주소를 저장
	if (!removeNode) return NULL;			// 스택이 비어있는지 확인
	self->field->node = removeNode->next;	// 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정
	data_t data = removeNode->data;		// 제거하기 전 데이터 저장
	free(removeNode);					// 노드 메모리 해제
	self->field->length--;				// 스택 길이 동기화
	return data;		 // 데이터 리턴
}

// 데이터를 반환
data_t _stack_peek(Stack self) {
	if (!self->field->node) return NULL; // 스택이 비어있는지 확인
	return self->field->node->data;		 // 데이터 리턴
}

// 스택의 길이를 반환
unsigned int _stack_length(Stack self) {
	return self->field->length;
}

// 스택 생성 함수
Stack new_stack() {
	Stack newStack = malloc(sizeof(_Stack));	// 새 스택 생성
	if (!newStack) return NULL;// 메모리 할당 확인
	StackField newField = malloc(sizeof(_StackField));	// 새 스택 생성
	if (!newField) { free(newStack); return NULL; }// 메모리 할당 확인
	newStack->push = _stack_push;			// 함수 기입
	newStack->pop = _stack_pop;				// 함수 기입
	newStack->peek = _stack_peek;			// 함수 기입
	newStack->length = _stack_length;		// 함수 기입
	newStack->field = newField;				// 구조체 기입
	newStack->field->node = NULL;			// node 초기화
	newStack->field->length = 0;			// 스택의 길이 초기화
	return newStack;						// 스택 리턴
}

// 스택 동적 할당 해제
void stack_free(Stack stack, eBool_t is_deleted_data) {
	data_t data;		// 임시 저장할 데이터
	unsigned int i = 0;
	for (i; i < stack->field->length; i++) {
		data = _stack_pop(stack);		// 싱글 노드 제거
		if (is_deleted_data) {			// 데이터 삭제를 원하면 제거
			free(data);	
			data = NULL;
		}
	}
	free(stack->field);	// 필드 할당 제거
	stack->field = NULL;// 필드 포인터 초기화
	free(stack);		// 할당 해제
	stack = NULL;		// 초기화
}

// 스택 요소들의 주소 리턴
void stack_print(Stack stack, char*(*fp)(data_t)) {
	StackSingleNode node = stack->field->node;
	printf("head");
	while (node) {
		if(fp)
			printf("-> %s", fp(node->data));
		else
			printf("-> %p", node->data);
		node = node->next;
	}
	printf("\n");
}