#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

// 필드 구조체 정의
struct _BinarySearchTreeNode {
	int key;					// 주체의 값
	BinarySearchTreeNode left;	// 왼쪽 노드
	BinarySearchTreeNode right; // 오른쪽 노드
	data_t data;				// 값
};

// 노드를 추가할 위치를 찾아 추가하는 함수
// 첫번째 인수는 현재 노드, 두번째는 추가할 노드
is_success_t __BST_insert(BinarySearchTreeNode current, BinarySearchTreeNode target) {
	int current_key = current->key;		// 현재 키값
	int target_key = target->key;		// 대상 키값
	if (target_key < current_key) {		// 대상 키값이 현재 키값보다 작다면
		if (current->left)				// 현재 노드의 왼쪽 노드가 있다면
			return __BST_insert(current->left, target);
		else
			current->left = target;
	}
	else if (target_key == current_key) {// 대상 키값이 현재 키값과 같다면
		fprintf(stderr, "It has the same key %s %d\n", __FILE__, __LINE__);
		return FALSE;
	}
	else {								// 대상 키값이 현재 키값보다 크다면
		if (current->right)				// 현재 노드의 오른쪽 노드가 있다면
			return __BST_insert(current->right, target);
		else
			current->right = target;
	}
	return TRUE;
}

// 노드 추가 함수
is_success_t _BST_insert(BinarySearchTree self, int key, data_t data) {
	BinarySearchTreeNode newNode = malloc(sizeof(_BinarySearchTreeNode));// 새 노드 생성
	if (!newNode) return FALSE;						// 메모리 검사
	newNode->key = key; newNode->left = NULL;		// 필드 초기화
	newNode->right = NULL; newNode->data = data;	// 필드 초기화
	
	if (self->root)				// root node가 존재하면 newField 추가
		return __BST_insert(self->root, newNode);
	else 						// root node가 존재하지 않으면
		self->root = newNode;	// 현재 node 추가
	return TRUE;
}

// 현재 노드가 키값을 가지고 있는지 탐색
BinarySearchTreeNode __find(BinarySearchTreeNode current, BinarySearchTreeNode* parent, int key) {
	if (!current)					// 노드가 NULL 일경우
		return NULL;
	else if (key > current->key) {	// 목표 키값이 현재 키값보다 큰 경우
		*parent = current;
		return __find(current->right, parent, key);
	}
	else if (key < current->key) {	// 목표 키값이 현재 키값보다 작은 경우
		*parent = current;
		return __find(current->left, parent, key);
	}
	return current;					// 목표 키값이 현재 키값과 같은 경우
}

// key 값을 기준으로 데이터를 찾아 반환하는 함수
data_t _find(BinarySearchTree self, int key) {
	return __find(self->root, NULL, key)->data;
}

// key 값을 기준으로 데이터를 찾아 반환하고 트리에서 삭제하는 함수
// 현재 가독성이 떨어지는 코드, 추후개선 필요.
data_t _del(BinarySearchTree self, int key) {
	BinarySearchTreeNode parentNode = NULL;		// 부모노드
	BinarySearchTreeNode removeNode = __find(self->root, &parentNode, key);	// 부모 노드와 지워야할 노드 탐색
	if (!removeNode) return NULL;	// 지워야할 노드가 없다면 NULL 값 리턴
	data_t data = removeNode->data;	// 지운 데이터 임시저장

	// 자식이 둘 다 있는 경우
	if (removeNode->left && removeNode->right) {
		BinarySearchTreeNode successor = removeNode->right;	// 현재 키 값의 다음 키값을 구함
		BinarySearchTreeNode successorParent = NULL;		// 현캐 키 값의 다음 키값을 가지는 노드의 부모
		while (successor->left) {							// 현재 키 값의 다음 키값을 구함
			successorParent = successor;
			successor = successor->left;
		}
		if (successorParent) successorParent->left = successor->right;
		else removeNode->right = successor->right;
		if (parentNode) {
			if (parentNode->left == removeNode)	// 부모의 왼쪽 자식을 지워야 하는 경우
				parentNode->left = successor;
			else								// 부모의오른쪽 자식을 지워야 하는 경우
				parentNode->right = successor;
		}
		else 
			self->root = successor;
		successor->left = removeNode->left;
		successor->right = removeNode->right;
		
	}
	// 자식이 하나만 있는 경우
	else if (removeNode->left || removeNode->right) {
		if (removeNode->left) {	// 왼쪽 자식이 있다면
			if (parentNode) {	// 부모 노드가 있다면
				if (parentNode->left == removeNode)	// 부모의 왼쪽 자식을 지워야 하는 경우
					parentNode->left = removeNode->left;
				else								// 부모의오른쪽 자식을 지워야 하는 경우
					parentNode->right = removeNode->left;
			}
			else 				// 부모 노드가 없다면
				self->root = removeNode->left;
		}
		else {					// 오른쪽 자식이 있다면
			if (parentNode) {	// 부모 노드가 있다면
				if (parentNode->left == removeNode)	// 부모의 왼쪽 자식을 지워야 하는 경우
					parentNode->left = removeNode->right;
				else								// 부모의오른쪽 자식을 지워야 하는 경우
					parentNode->right = removeNode->right;
			}
			else 				// 부모 노드가 없다면
				self->root = removeNode->right;
		}
	}
	// 자식이 없는 경우
	else {
		if (parentNode) {	// 부모노드가 있는 경우
			if (parentNode->left == removeNode)	// 부모의 왼쪽 자식을 지워야 하는 경우
				parentNode->left = NULL;
			else// 부모의오른쪽 자식을 지워야 하는 경우
				parentNode->right = NULL;
		}
		else	// 부모 노드가 없는 경우
			self->root = NULL;
	}
	free(removeNode);	// 메모리 할당 해제
	return data;		// 지운 데이터 리턴
}

// 새 이진 탐색트리 할당
BinarySearchTree new_BST() {
	BinarySearchTree newTree = malloc(sizeof(_BinarySearchTree));// 새 트리 생성
	if (!newTree) return NULL;	// 메모리 할당 확인
	newTree->root = NULL;		// 루트 노드 초기화
	newTree->insert = _BST_insert;	// 함수 기입
	newTree->find = _find;		// 함수 기입
	newTree->del = _del;		// 함수 기입
	return newTree;				// 트리 리턴
}

// 이진 탐색 트리 노드 동적 할당 해제
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

// 이진 탐색 트리 동적 할당 해제
void BST_free(BinarySearchTree tree, eBool_t is_deleted_data) {
	BSTNode_free(tree->root, is_deleted_data);
	free(tree);
	tree = NULL;
}

// 이진 탐색 트리 전위 탐색
void preOrder(BinarySearchTreeNode node, char* (*fp)(data_t)) {
	if (fp) printf("-> %s", fp(node->data));
	else printf("-> %d", node->key);
	if (node->left) preOrder(node->left, fp);
	if (node->right) preOrder(node->right, fp);
}

// 이진 탐색 트리 중위 탐색
void inOrder(BinarySearchTreeNode node, char* (*fp)(data_t)) {
	if (node->left) inOrder(node->left, fp);
	if (fp) printf("-> %s", fp(node->data));
	else printf("-> %d", node->key);
	if (node->right)inOrder(node->right, fp);
}

// 이진 탐색 트리 후위 탐색
void postOrder(BinarySearchTreeNode node, char* (*fp)(data_t)) {
	if (node->left) postOrder(node->left, fp);
	if (node->right) postOrder(node->right, fp);
	if (fp) printf("-> %s", fp(node->data));
	else printf("-> %d", node->key);
}