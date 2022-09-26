#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

// �ʵ� ����ü ����
struct _BinarySearchTreeNode {
	int key;					// ��ü�� ��
	BinarySearchTreeNode left;	// ���� ���
	BinarySearchTreeNode right; // ������ ���
	data_t data;				// ��
};

// ��带 �߰��� ��ġ�� ã�� �߰��ϴ� �Լ�
// ù��° �μ��� ���� ���, �ι�°�� �߰��� ���
is_success_t __BST_insert(BinarySearchTreeNode current, BinarySearchTreeNode target) {
	int current_key = current->key;		// ���� Ű��
	int target_key = target->key;		// ��� Ű��
	if (target_key < current_key) {		// ��� Ű���� ���� Ű������ �۴ٸ�
		if (current->left)				// ���� ����� ���� ��尡 �ִٸ�
			return __BST_insert(current->left, target);
		else
			current->left = target;
	}
	else if (target_key == current_key) {// ��� Ű���� ���� Ű���� ���ٸ�
		fprintf(stderr, "It has the same key %s %d\n", __FILE__, __LINE__);
		return FALSE;
	}
	else {								// ��� Ű���� ���� Ű������ ũ�ٸ�
		if (current->right)				// ���� ����� ������ ��尡 �ִٸ�
			return __BST_insert(current->right, target);
		else
			current->right = target;
	}
	return TRUE;
}

// ��� �߰� �Լ�
is_success_t _BST_insert(BinarySearchTree self, int key, data_t data) {
	BinarySearchTreeNode newNode = malloc(sizeof(_BinarySearchTreeNode));// �� ��� ����
	if (!newNode) return FALSE;						// �޸� �˻�
	newNode->key = key; newNode->left = NULL;		// �ʵ� �ʱ�ȭ
	newNode->right = NULL; newNode->data = data;	// �ʵ� �ʱ�ȭ
	
	if (self->root)				// root node�� �����ϸ� newField �߰�
		return __BST_insert(self->root, newNode);
	else 						// root node�� �������� ������
		self->root = newNode;	// ���� node �߰�
	return TRUE;
}

// ���� ��尡 Ű���� ������ �ִ��� Ž��
BinarySearchTreeNode __find(BinarySearchTreeNode current, BinarySearchTreeNode* parent, int key) {
	if (!current)					// ��尡 NULL �ϰ��
		return NULL;
	else if (key > current->key) {	// ��ǥ Ű���� ���� Ű������ ū ���
		*parent = current;
		return __find(current->right, parent, key);
	}
	else if (key < current->key) {	// ��ǥ Ű���� ���� Ű������ ���� ���
		*parent = current;
		return __find(current->left, parent, key);
	}
	return current;					// ��ǥ Ű���� ���� Ű���� ���� ���
}

// key ���� �������� �����͸� ã�� ��ȯ�ϴ� �Լ�
data_t _find(BinarySearchTree self, int key) {
	return __find(self->root, NULL, key)->data;
}

// key ���� �������� �����͸� ã�� ��ȯ�ϰ� Ʈ������ �����ϴ� �Լ�
// ���� �������� �������� �ڵ�, ���İ��� �ʿ�.
data_t _del(BinarySearchTree self, int key) {
	BinarySearchTreeNode parentNode = NULL;		// �θ���
	BinarySearchTreeNode removeNode = __find(self->root, &parentNode, key);	// �θ� ���� �������� ��� Ž��
	if (!removeNode) return NULL;	// �������� ��尡 ���ٸ� NULL �� ����
	data_t data = removeNode->data;	// ���� ������ �ӽ�����

	// �ڽ��� �� �� �ִ� ���
	if (removeNode->left && removeNode->right) {
		BinarySearchTreeNode successor = removeNode->right;	// ���� Ű ���� ���� Ű���� ����
		BinarySearchTreeNode successorParent = NULL;		// ��ĳ Ű ���� ���� Ű���� ������ ����� �θ�
		while (successor->left) {							// ���� Ű ���� ���� Ű���� ����
			successorParent = successor;
			successor = successor->left;
		}
		if (successorParent) successorParent->left = successor->right;
		else removeNode->right = successor->right;
		if (parentNode) {
			if (parentNode->left == removeNode)	// �θ��� ���� �ڽ��� ������ �ϴ� ���
				parentNode->left = successor;
			else								// �θ��ǿ����� �ڽ��� ������ �ϴ� ���
				parentNode->right = successor;
		}
		else 
			self->root = successor;
		successor->left = removeNode->left;
		successor->right = removeNode->right;
		
	}
	// �ڽ��� �ϳ��� �ִ� ���
	else if (removeNode->left || removeNode->right) {
		if (removeNode->left) {	// ���� �ڽ��� �ִٸ�
			if (parentNode) {	// �θ� ��尡 �ִٸ�
				if (parentNode->left == removeNode)	// �θ��� ���� �ڽ��� ������ �ϴ� ���
					parentNode->left = removeNode->left;
				else								// �θ��ǿ����� �ڽ��� ������ �ϴ� ���
					parentNode->right = removeNode->left;
			}
			else 				// �θ� ��尡 ���ٸ�
				self->root = removeNode->left;
		}
		else {					// ������ �ڽ��� �ִٸ�
			if (parentNode) {	// �θ� ��尡 �ִٸ�
				if (parentNode->left == removeNode)	// �θ��� ���� �ڽ��� ������ �ϴ� ���
					parentNode->left = removeNode->right;
				else								// �θ��ǿ����� �ڽ��� ������ �ϴ� ���
					parentNode->right = removeNode->right;
			}
			else 				// �θ� ��尡 ���ٸ�
				self->root = removeNode->right;
		}
	}
	// �ڽ��� ���� ���
	else {
		if (parentNode) {	// �θ��尡 �ִ� ���
			if (parentNode->left == removeNode)	// �θ��� ���� �ڽ��� ������ �ϴ� ���
				parentNode->left = NULL;
			else// �θ��ǿ����� �ڽ��� ������ �ϴ� ���
				parentNode->right = NULL;
		}
		else	// �θ� ��尡 ���� ���
			self->root = NULL;
	}
	free(removeNode);	// �޸� �Ҵ� ����
	return data;		// ���� ������ ����
}

// �� ���� Ž��Ʈ�� �Ҵ�
BinarySearchTree new_BST() {
	BinarySearchTree newTree = malloc(sizeof(_BinarySearchTree));// �� Ʈ�� ����
	if (!newTree) return NULL;	// �޸� �Ҵ� Ȯ��
	newTree->root = NULL;		// ��Ʈ ��� �ʱ�ȭ
	newTree->insert = _BST_insert;	// �Լ� ����
	newTree->find = _find;		// �Լ� ����
	newTree->del = _del;		// �Լ� ����
	return newTree;				// Ʈ�� ����
}

// ���� Ž�� Ʈ�� ��� ���� �Ҵ� ����
void BSTNode_free(BinarySearchTreeNode node, eBool_t is_deleted_data) {
	if (node->left) BSTNode_free(node->left, is_deleted_data);
	if (node->right) BSTNode_free(node->right, is_deleted_data);
	if (is_deleted_data) {
		free(node->data);
		node->data = NULL;
	}
	free(node);
	node = NULL;
}

// ���� Ž�� Ʈ�� ���� �Ҵ� ����
void BST_free(BinarySearchTree tree, eBool_t is_deleted_data) {
	BSTNode_free(tree->root, is_deleted_data);
	free(tree);
	tree = NULL;
}

// ���� Ž�� Ʈ�� ���� Ž��
void preOrder(BinarySearchTreeNode node, char* (*fp)(data_t)) {
	if (fp) printf("-> %s", fp(node->data));
	else printf("-> %d", node->key);
	if (node->left) preOrder(node->left, fp);
	if (node->right) preOrder(node->right, fp);
}

// ���� Ž�� Ʈ�� ���� Ž��
void inOrder(BinarySearchTreeNode node, char* (*fp)(data_t)) {
	if (node->left) inOrder(node->left, fp);
	if (fp) printf("-> %s", fp(node->data));
	else printf("-> %d", node->key);
	if (node->right)inOrder(node->right, fp);
}

// ���� Ž�� Ʈ�� ���� Ž��
void postOrder(BinarySearchTreeNode node, char* (*fp)(data_t)) {
	if (node->left) postOrder(node->left, fp);
	if (node->right) postOrder(node->right, fp);
	if (fp) printf("-> %s", fp(node->data));
	else printf("-> %d", node->key);
}