#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"

// �׷����� ��� ����
struct _GraphNode {
    char* vertex;   // ����
    GraphNode link; // ���� ���
};

// �׷����� ��� ����
struct _GraphField {
    List adj_list;  // ���� ����Ʈ
};

// �ΰ��� ���ڰ� ������ Ȯ�� strcmp
eBool_t _is_str_cmp(const char* s1, const char* s2) {
    while (*s1 != '\0' || *s2 != '\0') {
        if (*s1 != *s2) return FALSE;
        s1++;
        s2++;
    }
    return TRUE;
}

// GraphNode ����Ʈ�� vertex�� �ִ��� Ȯ��
long _nodelist_contains(List base, char* vertex) {
    unsigned int length = base->length(base), i = 0; 
    GraphNode n;
    for (i; i < length; i++) {
        n = (GraphNode)base->get(base, i);
        if (_is_str_cmp(n->vertex, vertex)) 
            return i;   // ����Ʈ�� ���� ������ �ε��� ����
    }
    return -1;  // ������ -1
}

// char* ����Ʈ�� vertex�� �ִ��� Ȯ��
eBool_t _charlist_contains(List base, char* vertex) {
    unsigned int length = base->length(base), i = 0;
    char* n;
    for (i; i < length; i++) {
        n = (char*)base->get(base, i);
        if (_is_str_cmp(n, vertex))
            return TRUE;    // ���� ������ TRUE
    }
    return FALSE;
}

// �׷����� ���� �߰� �Լ�
is_success_t _graph_insert_vertex(Graph self, char* v) {
    List list = self->field->adj_list;
    int index = _nodelist_contains(list, v);    
    if (index > -1) return FALSE;       // ������ �̹� ����
    GraphNode newNode = malloc(sizeof(_GraphNode));
    if (!newNode) return FALSE; // �޸� �Ҵ� ����
    newNode->link = NULL; newNode->vertex = v;
    if (!list->append(list, newNode)) { // �޸� �Ҵ� ����
        free(newNode);
        return FALSE;
    } 
    return TRUE;
}

// �׷����� ������ ������ �մ� ���� �߰�
is_success_t _graph_insert_edge(Graph self, char* u, char* v) {
    if (_is_str_cmp(u, v)) return FALSE; // �ڱ��ڽ��� ������ �ǹ� ����
    List list = self->field->adj_list;
    int start_index = _nodelist_contains(list, u);
    if (start_index < 0 || _nodelist_contains(list, v) < 0) return FALSE;  // ������ �ݵ��� �־����
    GraphNode node = list->get(list, start_index);
    while (node->link) {
        node = node->link;
        if (_is_str_cmp(node->vertex, v)) return FALSE; // �̹� �ش� ������ ����
    }
    GraphNode newEnd = malloc(sizeof(_GraphNode));
    if (!newEnd) return FALSE;
    newEnd->link = NULL; newEnd->vertex = v; // �ʱ�ȭ
    node->link = newEnd;
    return TRUE;
}

// ���� ����
is_success_t _graph_delete_vertex(Graph self, char* v) {
    List list = self->field->adj_list;
    int index = _nodelist_contains(list, v);    // ������ ��ġ ���
    if (index < 0) return FALSE;
    GraphNode node = list->pop(list, index), tmp = NULL;    // ���� ����Ʈ���� �ش� ���� ����
    while (node->link) {
        tmp = node;
        node = node->link;
        free(tmp);
    }
    unsigned int i = 0;
    for (i; i < list->length(list); i++) {  // �ٸ� ������ �ش� �����̶� �̾������� Ȯ��
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

// ���� ����
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

// ���� ����
List _graph_adgacent(Graph self, char* v) {
    List tmp = self->field->adj_list;
    int index = _nodelist_contains(tmp, v);
    if (index < 0) return NULL;
    GraphNode node = (GraphNode)tmp->get(tmp, index);
    List list = new_list();
    while (node->link) {    // v�� �������� ����Ǵ� ���� ��������
        node = node->link;
        list->append(list, node->vertex);
    }
    return list;
}

// �׷����� ������ �ִ��� Ȯ��
eBool_t _graph_is_empty(Graph self) {
    return self->field->adj_list->length(self->field->adj_list) > 0 ? TRUE : FALSE;
}

Graph new_graph(void) {
    Graph newGraph = malloc(sizeof(_Graph));
    if (!newGraph) return NULL; // ���� �Ҵ� Ȯ��
    GraphField newField = malloc(sizeof(_GraphField));
    if (!newField) { free(newGraph);  return NULL; }// ���� �Ҵ� Ȯ��
    List newList = new_list();
    if (!newList) { free(newGraph); free(newField);  return NULL; } // ���� �Ҵ� Ȯ��
    newField->adj_list = newList;                   // �ʵ� ��� �ʱ�ȭ
    newGraph->field = newField;                     // �ʵ� ����
    newGraph->insert_vertex = _graph_insert_vertex; // �Լ� ����
    newGraph->insert_edge = _graph_insert_edge;     // �Լ� ����
    newGraph->delete_vertex = _graph_delete_vertex; // �Լ� ����
    newGraph->delete_edge = _graph_delete_edge;     // �Լ� ����
    newGraph->adgacent = _graph_adgacent;           // �Լ� ����
    newGraph->is_empty = _graph_is_empty;           // �Լ� ����
    return newGraph;
}

// �׷��� ���� �Ҵ� ����
void graph_free(Graph graph) {
    List list = graph->field->adj_list;// ���� ����Ʈ
    unsigned int i = 0;
    GraphNode node, tmp;
    for (i; i < list->length(list); i++) {  // ��� ������ ���� ����
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
    Stack stack = new_stack();  // ������ ���� DFS ����
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
    Queue queue= new_queue();   // ť�� ���� BFS ����
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