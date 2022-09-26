#include "data_t.h"// data_t 사용

#ifndef STACK_H    // STACK_H가 정의되어 있지 않다면
#define STACK_H    // STACK_H 매크로 정의

typedef struct _StackSingleNode _StackSingleNode, * StackSingleNode;    // 노드 정의

typedef struct _StackField _StackField,* StackField;	// 스택의 내부 요소
typedef struct _Stack {
	is_success_t(*push)(struct _Stack* self, data_t);	// 데이터를 스택에 삽입
	data_t(*pop)(struct _Stack* self);			// 데이터를 반환 후 제거
	data_t(*peek)(struct _Stack* self);			// 데이터를 반환
	unsigned int(*length)(struct _Stack* self);	// 스택의 길이를 반환

	StackField field;				// 스택의 요소
}_Stack, * Stack;					// 스택 구조체, 포인터 정의
	
Stack new_stack(void);				// 스택 생성 함수 정의
void stack_free(Stack, eBool_t is_deleted_data);	// 스택 동적 할당 해제
void stack_print(Stack, char*(*fp)(data_t));	// 스택 원소 출력

#endif				// #ifndef STACK_H 끝
