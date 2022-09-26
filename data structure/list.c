#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// 리스트의 내부 요소
struct _ListField {
	unsigned int length;
	data_t* arr;
};

// 리스트의 길이에 따라 자동 재할당 함수
is_success_t auto_allocate(List list) {
	data_t* address = realloc(list->field->arr, sizeof(void*) * list->field->length);
	if (!address) return FALSE;
	list->field->arr = address;
	return TRUE;
}

// index의 값을 정상적인 인덱스로 바꿈 ex) length : 3, index : -1 -> 2
long get_std_index(unsigned int length, long index) {
	if (index < 0) return length + index;
	return index;
}

// 원하는 인덱스에 삽입하는 함수
is_success_t _list_insert(List self, long index, data_t data) {
	long length = (long)self->field->length;
	index = get_std_index(length, index);
	if (index < 0 || index >= length) return FALSE;
	self->field->length++;
	if (auto_allocate(self)) {
		for (length; length > index; length--) 
			self->field->arr[length] = self->field->arr[length - 1];
		self->field->arr[length] = data;
		return TRUE;
	}
	self->field->length--;
	return FALSE;
}

// 데이터 추가 함수
is_success_t _list_append(List self, data_t data) {
	self->field->length++;
	if (auto_allocate(self)) {
		self->field->arr[self->field->length - 1] = data;
		return TRUE;
	}
	self->field->length--;
	return FALSE;
}

// 리스트 수정
is_success_t _list_set(List self, long index, data_t data) {
	index = get_std_index(self->field->length, index);
	if (index < 0 || index >= (long)self->field->length) return FALSE;
	self->field->arr[index] = data;
	return TRUE;
}

// 데이터 얻기
data_t _list_get(List self, long index) {
	index = get_std_index(self->field->length, index);
	if (index < 0 || index >= (long)self->field->length) return NULL;
	return self->field->arr[index];
}

// 데이터 꺼네기
data_t _list_pop(List self, long index) {
	int length = self->field->length;
	index = get_std_index(length, index);
	if (index < 0 || index >= length) return NULL;
	data_t* arr = self->field->arr;
	data_t data = arr[index];
	for (++index; index < length; index++)
		arr[index - 1] = arr[index];
	arr[index] = NULL;
	self->field->length--;
	auto_allocate(self);
	return data;
} 

//	데이터의 인덱스 얻기
long _list_index(List self, data_t data) {
	unsigned int index = 0;
	for (index; index < self->field->length; index++)
		if (self->field->arr[index] == data) return index;
	return -1;
}

// 데이터 지우기
is_success_t _list_remove(List self, data_t data) {
	int index = 0, length = self->field->length;
	for (index; index < length; index++)
		if (self->field->arr[index] == data) {
			for (++index; index < length; index++)
				self->field->arr[index - 1] = self->field->arr[index];
			self->field->arr[index] = NULL;
			self->field->length--;
			auto_allocate(self);
			return TRUE;
		};
	return FALSE;
}

// 리스트 확장
is_success_t _list_extend(List self, List another) {
	int self_length = self->field->length;
	int length = self_length + another->field->length;
	self->field->length = length;
	if (auto_allocate(self)) {
		int last_index = self_length;
		for (last_index; last_index < length; last_index++)
			self->field->arr[last_index] = another->field->arr[last_index - self_length];
		return TRUE;
	}
	return FALSE;
}

// 리스트 길이
unsigned int _list_length(List self) {
	return self->field->length;
}

// 리스트 정렬
void _list_sort(List self, int (*_PtFuncCompare)(void const*, void const*)) {
	qsort(self->field->arr, self->field->length, sizeof(void*), _PtFuncCompare);
}

// 리스트 역전
void _list_reverse(List self) {
	data_t* arr = self->field->arr;
	int length = self->field->length, i = 0;
	void* tmp;
	for (i; i < length / 2; i++) {
		tmp = arr[i];
		arr[i] = arr[(length - 1) - i];
		arr[(length - 1) - i] = tmp;
	}
}

// 리스트 생성 함수 정의
List new_list(void){
	List newList = malloc(sizeof(_List));	// 새 리스트 생성
	if (!newList) return NULL;	// 메모리 할당 확인
	ListField newField = malloc(sizeof(_ListField)); // 새 리스트 요소 생성
	if (!newField) { free(newList);  return NULL; }	// 메모리 할당 확인
	newField->arr = NULL;					// arr 초기화
	newField->length = 0;					// 길이 초기화
	newList->field = newField;				// 구조체 기입
	newList->insert = _list_insert;			// 함수 기입
	newList->append = _list_append;			// 함수 기입
	newList->set = _list_set;				// 함수 기입
	newList->get = _list_get;				// 함수 기입
	newList->pop = _list_pop;				// 함수 기입
	newList->index = _list_index;			// 함수 기입
	newList->remove = _list_remove;			// 함수 기입
	newList->extend = _list_extend;			// 함수 기입
	newList->length = _list_length;			// 함수 기입
	newList->sort = _list_sort;				// 함수 기입
	newList->reverse = _list_reverse;		// 함수 기입
	return newList;							// 새 리스트 리턴
}	

// 리스트 할당 해제
void list_free(List list, eBool_t is_deleted_data){
	data_t* arr = list->field->arr;
	int length = list->field->length;
	list->field->arr = NULL;
	free(list->field);
	list->field = NULL;
	free(list);
	list = NULL;
	if (is_deleted_data) {
		int i = 0;
		for (i; i < length; i++) {
			free(arr[i]);
			arr[i] = NULL;
		}
	}
}	

// 리스트 원소 출력
void list_print(List list, char* (*fp)(data_t)) {
	int length = list->field->length, i = 0;
	printf("[");
	for (i; i < length; i++) {
		if (i) printf(", ");
		if (fp) printf("%s", fp(list->field->arr[i]));
		else printf("%p", list->field->arr[i]);
	}
	printf("]\n");
}