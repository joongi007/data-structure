#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// ���� ���� ��� ����
struct _StackSingleNode {
	StackSingleNode next;		// ���� ����� �ּҸ� ������ ������
	data_t data;                // �����͸� ������ ���
};

// �ʵ� ����ü ����
struct _StackField {
	StackSingleNode node;		// ���� ���� ���
	unsigned int length;		// ������ ����
};

// �����͸� ���ÿ� ����
is_success_t _stack_push(Stack self, data_t data) {
	StackSingleNode newNode = malloc(sizeof(_StackSingleNode));    // �� ��� ����
	if (!newNode) return FALSE;			// �޸� Ȯ��
	newNode->next = self->field->node;	// �� ����� ���� ��忡 ���� ����� ���� ��带 ����
	newNode->data = data;				// ������ ����
	self->field->node = newNode;		// ���� ����� ���� ��忡 �� ��带 ����
	self->field->length++;				// ���� ���� ����ȭ
	return TRUE;
}

// �����͸� ��ȯ �� ����
data_t _stack_pop(Stack self) {
	StackSingleNode removeNode = self->field->node;// ���� ����� ���� ��� �ּҸ� ����
	if (!removeNode) return NULL;			// ������ ����ִ��� Ȯ��
	self->field->node = removeNode->next;	// ���� ����� ���� ��忡 ������ ����� ���� ��带 ����
	data_t data = removeNode->data;		// �����ϱ� �� ������ ����
	free(removeNode);					// ��� �޸� ����
	self->field->length--;				// ���� ���� ����ȭ
	return data;		 // ������ ����
}

// �����͸� ��ȯ
data_t _stack_peek(Stack self) {
	if (!self->field->node) return NULL; // ������ ����ִ��� Ȯ��
	return self->field->node->data;		 // ������ ����
}

// ������ ���̸� ��ȯ
unsigned int _stack_length(Stack self) {
	return self->field->length;
}

// ���� ���� �Լ�
Stack new_stack() {
	Stack newStack = malloc(sizeof(_Stack));	// �� ���� ����
	if (!newStack) return NULL;// �޸� �Ҵ� Ȯ��
	StackField newField = malloc(sizeof(_StackField));	// �� ���� ����
	if (!newField) { free(newStack); return NULL; }// �޸� �Ҵ� Ȯ��
	newStack->push = _stack_push;			// �Լ� ����
	newStack->pop = _stack_pop;				// �Լ� ����
	newStack->peek = _stack_peek;			// �Լ� ����
	newStack->length = _stack_length;		// �Լ� ����
	newStack->field = newField;				// ����ü ����
	newStack->field->node = NULL;			// node �ʱ�ȭ
	newStack->field->length = 0;			// ������ ���� �ʱ�ȭ
	return newStack;						// ���� ����
}

// ���� ���� �Ҵ� ����
void stack_free(Stack stack, eBool_t is_deleted_data) {
	data_t data;		// �ӽ� ������ ������
	unsigned int i = 0;
	for (i; i < stack->field->length; i++) {
		data = _stack_pop(stack);		// �̱� ��� ����
		if (is_deleted_data) {			// ������ ������ ���ϸ� ����
			free(data);	
			data = NULL;
		}
	}
	free(stack->field);	// �ʵ� �Ҵ� ����
	stack->field = NULL;// �ʵ� ������ �ʱ�ȭ
	free(stack);		// �Ҵ� ����
	stack = NULL;		// �ʱ�ȭ
}

// ���� ��ҵ��� �ּ� ����
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