# data structure
기본 자료구조를 실제로 구현해보는 프로젝트입니다.
## 목차
### [1. 구현 내용](#구현-내용)
### [2. 구조](#구조)
### [3. 함수 설명](#함수-설명)
### [4. 앞으로 추가할 자료구조](#앞으로-추가할-자료구조)

## 구현 내용
|자료구조|헤더|설명|   
|--------|---|----|   
|스택|stack.h|LIFO 구조의 자료인 스텍을 구현|   
|큐|queue.h|FIFO 구조의 자료인 큐 구현|   
|데큐|queue.h|양쪽 끝에서 삽입과 삭제가 가능한 구조 구현|
|이진탐색트리|tree.h|순서가 있는 이진 트리 구조 구현|
|연속리스트|list.h|파이썬의 리스트와 같은 연속 리스트 구현|
|무가중치 방향 그래프|graph.h|무가중치 방향 그래프 구현|

## 구조
|이름|설명|Fan In|Fan Out|
|----|---|------|-------|
|data_t.h|프로젝트에서 쓸 기본 데이터 타입 정의.<br>TRUE, FALSE 정의.<br>함수 실행 성공여부 타입 정의.||stack.h<br>queue.h<br>tree.h<br>list.h<br>graph.h|
|stack.h<br>stack.c|스택 구조체 정의<br>스택 생성 함수 정의<br>스택 제거 함수 정의|data_t.h|graph.h|
|queue.h<br>queue.c|큐 구조체 정의<br>큐 생성 함수 정의<br>큐 제거 함수 정의<br>데큐 구조체 정의<br>데큐 생성 함수 정의<br>데큐 제거 함수 정의|data_t.h|graph.h|
|tree.h<br>tree.c|이진탐색트리 구조체 정의<br>이진탐색트리 생성 함수<br>이진탐색트리 제거 함수<br>preOrder<br>inOrder<br>postOrder|data_t.h||
|list.h<br>list.c|리스트 구조체 정의<br>리스트 생성 함수<br>리스트 제거 함수<br>리스트 출력 함수|data_t.h||
|graph.h<br>graph.c|무가중치 방향 그래프 구조체 정의<br>그래프 생성 함수<br>그래프 제거 함수<br>BFS<br>DFS|data_t.h<br>stack.h<br>queue.h||

## 함수 설명
예제에서 사용할 함수 세가지
```c
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
```
### 1. stack
(1) 스택 생성
```c
Stack stack = new_stack();
```
(2) 스택 push
```c
stack->push(stack, int_data(10));
```
(3) 스택 pop
```c
stack->pop(stack);
```
(4) 스택 출력
```c
stack_print(stack, int_to_char_p);
```
(5) 스택 제거
```c
stack_free(stack, TRUE);
```
### 2. queue
(1) 큐 생성
```c
Queue queue = new_queue();
```
(2) 큐 enQueue
```c
queue->enQueue(queue, int_data(10));
```
(3) 큐 deQueue
```c
queue->deQueue(queue);
```
(4) 큐 출력
```c
queue_print(queue, int_to_char_p);
```
(5) 큐 제거
```c
queue_free(queue, TRUE);
```
### 3. deque
(1) 데큐 생성
```c
Deque deque = new_deque();
```
(2) 데큐 append
```c
deque->append(deque, int_data(10));
```
(3) 데큐 pop
```c
deque->pop(deque);
```
(3) 데큐 append left
```c
deque->append_left(deque, int_data(11));
```
(4) 데큐 pop left
```c
deque->pop_left(deque);
```
(5) 데큐 출력
```c
deque_print(deque, int_to_char_p);
```
(6) 데큐 제거
```c
deque_free(deque, TRUE);
```
### 4. tree
(1) 트리 생성
```c
BinarySearchTree BST = new_BST();
```
(2) 트리 insert
```c
BST->insert(BST, 1, int_data(1));
```
(3) 트리 find
```c
BST->find(BST, 1);
```
(4) 트리 del
```c
BST->del(BST, 1);
```
(5) 트리 출력
```c
preOrder(BST->root, int_to_char_p);
inOrder(BST->root, int_to_char_p);
postOrder(BST->root, int_to_char_p);
```
(6) 트리 제거
```c
BST_free(BST, free);
```
### 5. list
(1) 리스트 생성
```c
List list = new_list();
```
(2) 리스트 append
```c
list->append(list, int_data(10));
```
(3) 리스트 insert
```c
list->insert(list, 0, int_data(11));
```
(4) 리스트 set
```c
list->set(list, 0, int_data(12));
```
(5) 리스트 get
```c
list->get(list, 0);
```
(6) 리스트 pop
```c
list->pop(list, 0);
```
(7) 리스트 extend
```c
List other = new_list();
other->append(other, int_data(1));
list->extend(list, other);
```
(8) 리스트 length
```c
list->length(list);
```
(9) 리스트 sort
```c
list->sort(list, compare);  
```
(10) 리스트 reverse
```c
list->reverse(list);
```
(11) 리스트 출력
```c
list_print(list, int_to_char_p);
```
(11) 리스트 제거
```c
list_free(list, TRUE);
```
### 5. graph
(1) 그래프 생성
```c
Graph graph = new_graph();
```
(2) 그래프 정점 추가
```c
graph->insert_vertex(graph, "0");
graph->insert_vertex(graph, "1");
```
(3) 그래프 간선 추가
```c
graph->insert_edge(graph, "0", "1");
```
(4) 그래프 정점 제거
```c
graph->delete_vertex(graph, "0");
```
(5) 그래프 간선 제거
```c
graph->delete_edge(graph, "0", "1");
```
(6) 그래프 출력
```c
DFS(graph, "0");
BFS(graph, "0");
```
(7) 그래프 제거
```c
graph_free(graph);
```

## 앞으로 추가할 자료구조
1. Heap
2. Hash-Map 