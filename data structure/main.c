#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "list.h"
#include "graph.h"

int* int_data(int data); // 정수 동적 할당 함수
char* int_to_char_p(data_t data);		// 정수 to 문자열 함수
int compare(const void*, const void*); // qsort를 위한 비교함수
void ex_stack();	// 스택 예시
void ex_queue();	// 큐 예시
void ex_deque();	// 데크 예시
void ex_tree();		// 트리 예시
void ex_list();		// 리스트 예시
void ex_graph();	// 그래프 예시

int main() {
	ex_stack();
	ex_queue();
	ex_deque();
	ex_tree();
	ex_list();
	ex_graph();
	return 0;
}

int* int_data(int data) {
	int* v = malloc(sizeof(int));
	if (!v) return NULL;
	*v = data;
	return v;
}

char* int_to_char_p(data_t data) {
	char* v = malloc(sizeof(char) * 20);
	if (!v) return NULL;
	sprintf_s(v, 20, "%d", *(int*)data);
	return v;
}

int compare(void const * a, void const * b) {
	int n1 = **(int**)a;
	int n2 = **(int**)b;
	return (n1 > n2) ? 1 : (n1 == n2) ? 0 : -1;
}

void ex_stack() {
	Stack stack = new_stack();
	int i = 0;
	for (i; i < 10; i++) stack->push(stack, int_data(i));
	printf("Stack Example\n");
	printf("\tcurrent : ");
	stack_print(stack, int_to_char_p);
	stack->push(stack, int_data(10));
	printf("\tpush    : %d\n\tcurrent : ", 10);
	stack_print(stack, int_to_char_p);
	printf("\tpop     : %d\n\tcurrent : ", *(int*)stack->pop(stack));
	stack_print(stack, int_to_char_p);
	stack_free(stack, TRUE);
	puts("\n");
}

void ex_queue() {
	Queue queue = new_queue();
	int i = 0;
	for (i; i < 10; i++) queue->enQueue(queue, int_data(i));
	printf("Queue Example\n");
	printf("\tcurrent : ");
	queue_print(queue, int_to_char_p);
	queue->enQueue(queue, int_data(10));
	printf("\tenQueue : %d\n\tcurrent : ", 10);
	queue_print(queue, int_to_char_p);
	printf("\tdeQueue : %d\n\tcurrent : ", *(int*)queue->deQueue(queue));
	queue_print(queue, int_to_char_p);
	queue_free(queue, TRUE);
	puts("\n");
}

void ex_deque() {
	Deque deque = new_deque();
	int i = 0;
	for (i; i < 10; i++) deque->append(deque, int_data(i));
	printf("Deque Example\n");
	printf("\tcurrent : ");
	deque_print(deque, int_to_char_p);
	deque->append(deque, int_data(10));
	printf("\tappend  : %d\n\tcurrent : ", 10);
	deque_print(deque, int_to_char_p);
	printf("\tpop     : %d\n\tcurrent : ", *(int*)deque->pop(deque));
	deque_print(deque, int_to_char_p);
	deque->append_left(deque, int_data(11));
	printf("\tappend_left : %d\n\tcurrent : ", 11);
	deque_print(deque, int_to_char_p);
	printf("\tpop_left: %d\n\tcurrent : ", *(int*)deque->pop_left(deque));
	deque_print(deque, int_to_char_p);
	deque_free(deque, TRUE);
	puts("\n");
}

void ex_tree() {
	printf("Binary Search Tree Example\n");
	int key [10] = { 9,1,4,7,8,3,2,0,5,6 }, i = 0;
	printf("\tkey       : [ ");
	for (i; i < 10; i++) printf("%d ", key[i]); printf("]\n");
	BinarySearchTree BST = new_BST();
	for (i = 0; i < 10; i++) BST->insert(BST, key[i], int_data(key[i]));
	printf("\tpreOreder : "); preOrder(BST->root, int_to_char_p);
	puts("");
	printf("\tinOreder  : "); inOrder(BST->root, int_to_char_p);
	puts("");
	printf("\tpostOreder: "); postOrder(BST->root, int_to_char_p);
	BST_free(BST, TRUE);
	puts("\n\n");
}

void ex_list() {
	printf("List Example\n");
	List list = new_list();
	int i = 0;
	for (i; i < 10; i++) list->append(list, int_data(i));
	printf("\tcurrent : ");
	list_print(list, int_to_char_p);

	list->append(list, int_data(10));
	printf("\tappend  : %d\n\tcurrent : ", 10);
	list_print(list, int_to_char_p);

	list->insert(list, 5, int_data(11));
	printf("\tindex   : 5 insert : %d\n\tcurrent : ", 11);
	list_print(list, int_to_char_p);

	list->set(list, 3, int_data(12));
	printf("\tindex   : 3 set : %d\n\tcurrent : ", 12);
	list_print(list, int_to_char_p);

	printf("\tindex   : 8 pop : %d\n\tcurrent : ", *(int*)list->pop(list, 8));
	list_print(list, int_to_char_p);

	list->sort(list, compare);
	printf("\tsort    : ");
	list_print(list, int_to_char_p);

	list->reverse(list);
	printf("\treverse : ");
	list_print(list, int_to_char_p);
	list_free(list, TRUE);
	puts("\n");
}
 
void ex_graph() {
	printf("Graph Example\n");
	Graph graph = new_graph();
	graph->insert_vertex(graph, "0");
	graph->insert_vertex(graph, "1");
	graph->insert_vertex(graph, "2");
	graph->insert_vertex(graph, "3");
	graph->insert_vertex(graph, "4");
	graph->insert_vertex(graph, "5");
	graph->insert_vertex(graph, "6");
	graph->insert_edge(graph, "0", "1");
	graph->insert_edge(graph, "0", "2");
	graph->insert_edge(graph, "1", "3");
	graph->insert_edge(graph, "1", "4");
	graph->insert_edge(graph, "2", "5");
	graph->insert_edge(graph, "2", "6");
	printf("\tGraph shape:\n");
	printf("\t\t 0\n");
	printf("\t\t│\n");
	printf("\t\t├─ 1\n");
	printf("\t\t│  ├ 3\n");
	printf("\t\t│  └ 4\n");
	printf("\t\t└─ 2\n");
	printf("\t\t   ├ 3\n");
	printf("\t\t   └ 4\n");
	printf("\tfrom 0 DFS: ");
	DFS(graph, "0");
	printf("\tfrom 0 DFS: ");
	BFS(graph, "0");
	graph_free(graph);
	puts("");
}