#include "data_t.h"// data_t ���

#ifndef LIST_H    // LIST_H�� ���ǵǾ� ���� �ʴٸ�
#define LIST_H    // LIST_H ��ũ�� ����

typedef struct _ListField _ListField, * ListField;	// ����Ʈ�� ���� ���
typedef struct _List{	// ����Ʈ ����
	is_success_t(*insert)(struct _List* self, long index, data_t);	 // ������ ����
	is_success_t(*append)(struct _List* self, data_t);		// ������ �߰�
	is_success_t(*set)(struct _List* self, long index, data_t);		// ������ ����
	data_t(*get)(struct _List* self, long index);			// ������ ���
	data_t(*pop)(struct _List* self, long index);			// ������ ���ױ�
	long(*index)(struct _List* self, data_t);				//	�������� �ε��� ���
	is_success_t(*remove)(struct _List* self, data_t);		// ������ �����
	is_success_t(*extend)(struct _List* self, struct _List* another);// ����Ʈ Ȯ��
	unsigned int(*length)(struct _List* self);				// ����Ʈ ����
	void(*sort)(struct _List* self, int(*_PtFuncCompare)(void const*, void const*));// ����Ʈ ����
	void(*reverse)(struct _List* self);						// ����Ʈ ����

	ListField field;	// ����Ʈ�� ���
}_List, *List;

List new_list(void);	// ����Ʈ ���� �Լ� ����
void list_free(List, eBool_t is_deleted_data);	// ����Ʈ �Ҵ� ����
void list_print(List, char* (*fp)(data_t));		// ����Ʈ ���� ���

#endif			  // #ifndef LIST_H ��
