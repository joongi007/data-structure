#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"

// 그래프의 노드 정의
struct _GraphNode {
    char* vertex;   // 정점
    GraphNode link; // 다음 노드
};

// 그래프의 요소 정의
struct _GraphField {
    List adj_list;  // 정점 리스트
};

// 두개의 문자가 같은지 확인 strcmp
eBool_t _is_str_cmp(const char* s1, const char* s2) {
    while (*s1 != '\0' || *s2 != '\0') {
        if (*s1 != *s2) return FALSE;
        s1++;
        s2++;
    }
    return TRUE;
}

// GraphNode 리스트에 vertex가 있는지 확인
long _nodelist_contains(List base, char* vertex) {
    unsigned int length = base->length(base), i = 0; 
    GraphNode n;
    for (i; i < length; i++) {
        n = (GraphNode)base->get(base, i);
        if (_is_str_cmp(n->vertex, vertex)) 
            return i;   // 리스트에 값이 있으면 인덱스 리턴
    }
    return -1;  // 없으면 -1
}

// char* 리스트에 vertex가 있는지 확인
eBool_t _charlist_contains(List base, char* vertex) {
    unsigned int length = base->length(base), i = 0;
    char* n;
    for (i; i < length; i++) {
        n = (char*)base->get(base, i);
        if (_is_str_cmp(n, vertex))
            return TRUE;    // 값이 있으면 TRUE
    }
    return FALSE;
}

// 그래프에 정점 추가 함수
is_success_t _graph_insert_vertex(Graph self, char* v) {
    List list = self->field->adj_list;
    int index = _nodelist_contains(list, v);    
    if (index > -1) return FALSE;       // 정점이 이미 있음
    GraphNode newNode = malloc(sizeof(_GraphNode));
    if (!newNode) return FALSE; // 메모리 할당 실패
    newNode->link = NULL; newNode->vertex = v;
    if (!list->append(list, newNode)) { // 메모리 할당 실패
        free(newNode);
        return FALSE;
    } 
    return TRUE;
}

// 그래프에 정점과 정점을 잇는 간선 추가
is_success_t _graph_insert_edge(Graph self, char* u, char* v) {
    if (_is_str_cmp(u, v)) return FALSE; // 자기자신은 간선이 의미 없음
    List list = self->field->adj_list;
    int start_index = _nodelist_contains(list, u);
    if (start_index < 0 || _nodelist_contains(list, v) < 0) return FALSE;  // 정점은 반듯이 있어야함
    GraphNode node = list->get(list, start_index);
    while (node->link) {
        node = node->link;
        if (_is_str_cmp(node->vertex, v)) return FALSE; // 이미 해당 간선이 있음
    }
    GraphNode newEnd = malloc(sizeof(_GraphNode));
    if (!newEnd) return FALSE;
    newEnd->link = NULL; newEnd->vertex = v; // 초기화
    node->link = newEnd;
    return TRUE;
}

// 정점 삭제
is_success_t _graph_delete_vertex(Graph self, char* v) {
    List list = self->field->adj_list;
    int index = _nodelist_contains(list, v);    // 정점의 위치 얻기
    if (index < 0) return FALSE;
    GraphNode node = list->pop(list, index), tmp = NULL;    // 정점 리스트에서 해당 정점 제거
    while (node->link) {
        tmp = node;
        node = node->link;
        free(tmp);
    }
    unsigned int i = 0;
    for (i; i < list->length(list); i++) {  // 다른 정점이 해당 정점이랑 이어지는지 확인
        node = list->get(list, i);
        while (node->link) {
            tmp = node;
            node = node->link;
            if (_is_str_cmp(tmp->link->vertex, v)) {
                tmp->link = node->link;
                node->link, node->link->link;
                free(node);
                node = tmp;
                break;
            }
        }
    }
    return TRUE;
}

// 간선 삭제
is_success_t _graph_delete_edge(Graph self, char* u, char* v) {
    List list = self->field->adj_list;
    int index = _nodelist_contains(list, u);
    if (index < 0) return FALSE;
    GraphNode node = list->get(list, index);
    while (node->link) {
        if (_is_str_cmp(node->link->vertex, v)) {
            GraphNode tmp = node->link;
            node->link = node->link->link;
            free(tmp);
            return TRUE;
        }
    }
    return FALSE;
}

// 인접 정점
List _graph_adgacent(Graph self, char* v) {
    List tmp = self->field->adj_list;
    int index = _nodelist_contains(tmp, v);
    if (index < 0) return NULL;
    GraphNode node = (GraphNode)tmp->get(tmp, index);
    List list = new_list();
    while (node->link) {    // v를 기준으로 진행되는 정점 가져오기
        node = node->link;
        list->append(list, node->vertex);
    }
    return list;
}

// 그래프에 정점이 있는지 확인
eBool_t _graph_is_empty(Graph self) {
    return self->field->adj_list->length(self->field->adj_list) > 0 ? TRUE : FALSE;
}

Graph new_graph(void) {
    Graph newGraph = malloc(sizeof(_Graph));
    if (!newGraph) return NULL; // 동적 할당 확인
    GraphField newField = malloc(sizeof(_GraphField));
    if (!newField) { free(newGraph);  return NULL; }// 동적 할당 확인
    List newList = new_list();
    if (!newList) { free(newGraph); free(newField);  return NULL; } // 동적 할당 확인
    newField->adj_list = newList;                   // 필드 요소 초기화
    newGraph->field = newField;                     // 필드 기입
    newGraph->insert_vertex = _graph_insert_vertex; // 함수 기입
    newGraph->insert_edge = _graph_insert_edge;     // 함수 기입
    newGraph->delete_vertex = _graph_delete_vertex; // 함수 기입
    newGraph->delete_edge = _graph_delete_edge;     // 함수 기입
    newGraph->adgacent = _graph_adgacent;           // 함수 기입
    newGraph->is_empty = _graph_is_empty;           // 함수 기입
    return newGraph;
}

// 그래프 동적 할당 해제
void graph_free(Graph graph) {
    List list = graph->field->adj_list;// 정점 리스트
    unsigned int i = 0;
    GraphNode node, tmp;
    for (i; i < list->length(list); i++) {  // 모든 정점과 간선 제거
        node = (GraphNode)list->pop(list, -1);
        tmp = node;
        while (tmp) {
            tmp = tmp->link;
            free(node);
            node = tmp;
        }
    }
    list_free(list, TRUE);
    free(graph->field);
    graph->field = NULL;
    free(graph);
    graph = NULL;
}

// dfs
void DFS(Graph graph, char* v) {
    List visited = new_list();
    if (!visited) return;
    Stack stack = new_stack();  // 스택을 통해 DFS 구현
    if (!stack) { list_free(visited, FALSE);  return; }
    if (!stack->push(stack, v)) { 
        list_free(visited, FALSE); 
        stack_free(stack, FALSE);
        return; 
    }
    List tmp;
    printf("<DFS> ");
    while (stack->length(stack)) {
        char* vertex = (char*)stack->pop(stack);
        if (_charlist_contains(visited, vertex)) continue;
        if (!visited->append(visited, vertex)) {
            list_free(visited, FALSE);
            stack_free(stack, FALSE);
            return;
        }
        printf("-> %s", vertex);
        tmp = graph->adgacent(graph, vertex);
        if (!tmp) continue;
        unsigned int i = tmp->length(tmp);
        for (i; i > 0 ; i--) {
            if (!stack->push(stack, tmp->get(tmp, i - 1))) {
                list_free(visited, FALSE);
                stack_free(stack, FALSE);
                list_free(tmp, FALSE);
                return;
            }
        }
        list_free(tmp, FALSE);      
    }
    printf(" <\\DFS>\n");
    list_free(visited, FALSE);
    stack_free(stack, FALSE);
}  

// bfs
void BFS(Graph graph, char* v) {
    List visited = new_list();
    if (!visited) return;
    Queue queue= new_queue();   // 큐를 통해 BFS 구현
    if (!queue) { list_free(visited, FALSE);  return; }
    if (!queue->enQueue(queue, v)) {
        list_free(visited, FALSE);
        queue_free(queue, FALSE);
        return;
    }
    List tmp;
    printf("<BFS> ");
    while (queue->length(queue)) {
        char* vertex = (char*)queue->deQueue(queue);
        if (_charlist_contains(visited, vertex)) continue;
        if (!visited->append(visited, vertex)) {
            list_free(visited, FALSE);
            queue_free(queue, FALSE);
            return;
        }
        printf("-> %s", vertex);
        tmp = graph->adgacent(graph, vertex);
        if (!tmp) continue;
        unsigned int i = 0;
        for (i; i < tmp->length(tmp); i++) {
            if (!queue->enQueue(queue, tmp->get(tmp, i))) {
                list_free(visited, FALSE);
                queue_free(queue, FALSE);
                list_free(tmp, FALSE);
                return;
            }
        }
        list_free(tmp, FALSE);
    }
    printf(" <\\BFS>\n");
    list_free(visited, FALSE);
    queue_free(queue, FALSE);
}  