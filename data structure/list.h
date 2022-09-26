#include "data_t.h"// data_t 사용

#ifndef LIST_H    // LIST_H가 정의되어 있지 않다면
#define LIST_H    // LIST_H 매크로 정의

typedef struct _ListField _ListField, * ListField;	// 리스트의 내부 요소
typedef struct _List{	// 리스트 정의
	is_success_t(*insert)(struct _List* self, long index, data_t);	 // 데이터 삽입
	is_success_t(*append)(struct _List* self, data_t);		// 데이터 추가
	is_success_t(*set)(struct _List* self, long index, data_t);		// 데이터 변경
	data_t(*get)(struct _List* self, long index);			// 데이터 얻기
	data_t(*pop)(struct _List* self, long index);			// 데이터 꺼네기
	long(*index)(struct _List* self, data_t);				//	데이터의 인덱스 얻기
	is_success_t(*remove)(struct _List* self, data_t);		// 데이터 지우기
	is_success_t(*extend)(struct _List* self, struct _List* another);// 리스트 확장
	unsigned int(*length)(struct _List* self);				// 리스트 길이
	void(*sort)(struct _List* self, int(*_PtFuncCompare)(void const*, void const*));// 리스트 정렬
	void(*reverse)(struct _List* self);						// 리스트 역전

	ListField field;	// 리스트의 요소
}_List, *List;

List new_list(void);	// 리스트 생성 함수 정의
void list_free(List, eBool_t is_deleted_data);	// 리스트 할당 해제
void list_print(List, char* (*fp)(data_t));		// 리스트 원소 출력

#endif			  // #ifndef LIST_H 끝
