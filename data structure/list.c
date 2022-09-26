#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// ����Ʈ�� ���� ���
struct _ListField {
	unsigned int length;
	data_t* arr;
};

// ����Ʈ�� ���̿� ���� �ڵ� ���Ҵ� �Լ�
is_success_t auto_allocate(List list) {
	data_t* address = realloc(list->field->arr, sizeof(void*) * list->field->length);
	if (!address) return FALSE;
	list->field->arr = address;
	return TRUE;
}

// index�� ���� �������� �ε����� �ٲ� ex) length : 3, index : -1 -> 2
long get_std_index(unsigned int length, long index) {
	if (index < 0) return length + index;
	return index;
}

// ���ϴ� �ε����� �����ϴ� �Լ�
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

// ������ �߰� �Լ�
is_success_t _list_append(List self, data_t data) {
	self->field->length++;
	if (auto_allocate(self)) {
		self->field->arr[self->field->length - 1] = data;
		return TRUE;
	}
	self->field->length--;
	return FALSE;
}

// ����Ʈ ����
is_success_t _list_set(List self, long index, data_t data) {
	index = get_std_index(self->field->length, index);
	if (index < 0 || index >= (long)self->field->length) return FALSE;
	self->field->arr[index] = data;
	return TRUE;
}

// ������ ���
data_t _list_get(List self, long index) {
	index = get_std_index(self->field->length, index);
	if (index < 0 || index >= (long)self->field->length) return NULL;
	return self->field->arr[index];
}

// ������ ���ױ�
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

//	�������� �ε��� ���
long _list_index(List self, data_t data) {
	unsigned int index = 0;
	for (index; index < self->field->length; index++)
		if (self->field->arr[index] == data) return index;
	return -1;
}

// ������ �����
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

// ����Ʈ Ȯ��
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

// ����Ʈ ����
unsigned int _list_length(List self) {
	return self->field->length;
}

// ����Ʈ ����
void _list_sort(List self, int (*_PtFuncCompare)(void const*, void const*)) {
	qsort(self->field->arr, self->field->length, sizeof(void*), _PtFuncCompare);
}

// ����Ʈ ����
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

// ����Ʈ ���� �Լ� ����
List new_list(void){
	List newList = malloc(sizeof(_List));	// �� ����Ʈ ����
	if (!newList) return NULL;	// �޸� �Ҵ� Ȯ��
	ListField newField = malloc(sizeof(_ListField)); // �� ����Ʈ ��� ����
	if (!newField) { free(newList);  return NULL; }	// �޸� �Ҵ� Ȯ��
	newField->arr = NULL;					// arr �ʱ�ȭ
	newField->length = 0;					// ���� �ʱ�ȭ
	newList->field = newField;				// ����ü ����
	newList->insert = _list_insert;			// �Լ� ����
	newList->append = _list_append;			// �Լ� ����
	newList->set = _list_set;				// �Լ� ����
	newList->get = _list_get;				// �Լ� ����
	newList->pop = _list_pop;				// �Լ� ����
	newList->index = _list_index;			// �Լ� ����
	newList->remove = _list_remove;			// �Լ� ����
	newList->extend = _list_extend;			// �Լ� ����
	newList->length = _list_length;			// �Լ� ����
	newList->sort = _list_sort;				// �Լ� ����
	newList->reverse = _list_reverse;		// �Լ� ����
	return newList;							// �� ����Ʈ ����
}	

// ����Ʈ �Ҵ� ����
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

// ����Ʈ ���� ���
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