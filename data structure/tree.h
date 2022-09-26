#include "data_t.h"	// data_t ���

#ifndef TREE_H    // TREE_H�� ���ǵǾ� ���� �ʴٸ�
#define TREE_H    // TREE_H ��ũ�� ����

typedef struct _BinarySearchTreeNode _BinarySearchTreeNode,* BinarySearchTreeNode;		// ����Ž��Ʈ���� ���� ���

typedef struct _BinarySearchTree {
	is_success_t(*insert)(struct _BinarySearchTree* self, int key, data_t);// ���Կ���
	data_t(*find)(struct _BinarySearchTree* self, int key);		// �˻�����
	data_t(*del)(struct _BinarySearchTree* self, int key);		// ���� ����

	BinarySearchTreeNode root;			// Ʈ���� ��Ʈ ���
}_BinarySearchTree, * BinarySearchTree;	// Ʈ�� ����ü, ������ ����

BinarySearchTree new_BST();	// ���� Ž�� Ʈ�� ���� �Լ� ����
void BST_free(BinarySearchTree tree, eBool_t is_deleted_data);	  // ���� Ž�� Ʈ�� ���� �Ҵ� ����
void preOrder(BinarySearchTreeNode Node, char* (*fp)(data_t));	  // ���� ��ȸ
void inOrder(BinarySearchTreeNode Node, char* (*fp)(data_t));	  // ���� ��ȸ
void postOrder(BinarySearchTreeNode Node, char* (*fp)(data_t));	  // ���� ��ȸ

#endif            // #ifndef TREE_H ��