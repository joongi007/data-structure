#include "data_t.h"// data_t ���

#ifndef GRAPH_H    // GRAPH_H�� ���ǵǾ� ���� �ʴٸ�
#define GRAPH_H    // GRAPH_H ��ũ�� ����

typedef struct _GraphNode _GraphNode, * GraphNode; // �׷��� ��� ����
typedef struct _GraphField _GraphField, * GraphField;// �׷��� ���� ���
typedef struct _Graph {     // �׷��� ����
    is_success_t(*insert_vertex)(struct _Graph* self, char* v);         // ���� ���
    is_success_t(*insert_edge)(struct _Graph* self, char* u, char* v);  // ���� ���
    is_success_t(*delete_vertex)(struct _Graph* self, char* v);         // ���� ����
    is_success_t(*delete_edge)(struct _Graph* self, char* u, char* v);  // ���� ����
    List(*adgacent)(struct _Graph* self, char* v);    // ���� ����
    eBool_t(*is_empty)(struct _Graph* self);          // �׷����� ������ �ִ���
    GraphField field;       // �׷��� ���� ���
}_Graph, * Graph;

Graph new_graph(void);	// ����Ʈ ���� �Լ� ����
void graph_free(Graph);	// ����Ʈ �Ҵ� ����
void DFS(Graph graph, char* v);  // dfs
void BFS(Graph graph, char* v);  // bfs

#endif			   // #ifndef GRAPH_H ��
