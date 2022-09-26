#include "data_t.h"// data_t ���

#ifndef STACK_H    // STACK_H�� ���ǵǾ� ���� �ʴٸ�
#define STACK_H    // STACK_H ��ũ�� ����

typedef struct _StackSingleNode _StackSingleNode, * StackSingleNode;    // ��� ����

typedef struct _StackField _StackField,* StackField;	// ������ ���� ���
typedef struct _Stack {
	is_success_t(*push)(struct _Stack* self, data_t);	// �����͸� ���ÿ� ����
	data_t(*pop)(struct _Stack* self);			// �����͸� ��ȯ �� ����
	data_t(*peek)(struct _Stack* self);			// �����͸� ��ȯ
	unsigned int(*length)(struct _Stack* self);	// ������ ���̸� ��ȯ

	StackField field;				// ������ ���
}_Stack, * Stack;					// ���� ����ü, ������ ����
	
Stack new_stack(void);				// ���� ���� �Լ� ����
void stack_free(Stack, eBool_t is_deleted_data);	// ���� ���� �Ҵ� ����
void stack_print(Stack, char*(*fp)(data_t));	// ���� ���� ���

#endif				// #ifndef STACK_H ��
