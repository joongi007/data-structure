#include "data_t.h"	// data_t 사용

#ifndef TREE_H    // TREE_H가 정의되어 있지 않다면
#define TREE_H    // TREE_H 매크로 정의

typedef struct _BinarySearchTreeNode _BinarySearchTreeNode,* BinarySearchTreeNode;		// 이진탐색트리의 내부 요소

typedef struct _BinarySearchTree {
	is_success_t(*insert)(struct _BinarySearchTree* self, int key, data_t);// 삽입연산
	data_t(*find)(struct _BinarySearchTree* self, int key);		// 검색연산
	data_t(*del)(struct _BinarySearchTree* self, int key);		// 삭제 연산

	BinarySearchTreeNode root;			// 트리의 루트 노드
}_BinarySearchTree, * BinarySearchTree;	// 트리 구조체, 포인터 정의

BinarySearchTree new_BST();	// 이진 탐색 트리 생성 함수 정의
void BST_free(BinarySearchTree tree, eBool_t is_deleted_data);	  // 이진 탐색 트리 동적 할당 해제
void preOrder(BinarySearchTreeNode Node, char* (*fp)(data_t));	  // 전위 순회
void inOrder(BinarySearchTreeNode Node, char* (*fp)(data_t));	  // 중위 순회
void postOrder(BinarySearchTreeNode Node, char* (*fp)(data_t));	  // 후위 순회

#endif            // #ifndef TREE_H 끝