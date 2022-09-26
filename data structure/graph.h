#include "data_t.h"// data_t 사용

#ifndef GRAPH_H    // GRAPH_H가 정의되어 있지 않다면
#define GRAPH_H    // GRAPH_H 매크로 정의

typedef struct _GraphNode _GraphNode, * GraphNode; // 그래프 노드 정의
typedef struct _GraphField _GraphField, * GraphField;// 그래프 내부 요소
typedef struct _Graph {     // 그래프 정의
    is_success_t(*insert_vertex)(struct _Graph* self, char* v);         // 정점 등록
    is_success_t(*insert_edge)(struct _Graph* self, char* u, char* v);  // 간선 등록
    is_success_t(*delete_vertex)(struct _Graph* self, char* v);         // 정점 삭제
    is_success_t(*delete_edge)(struct _Graph* self, char* u, char* v);  // 간선 삭제
    List(*adgacent)(struct _Graph* self, char* v);    // 인접 정점
    eBool_t(*is_empty)(struct _Graph* self);          // 그래프에 정점이 있는지
    GraphField field;       // 그래프 내부 요소
}_Graph, * Graph;

Graph new_graph(void);	// 리스트 생성 함수 정의
void graph_free(Graph);	// 리스트 할당 해제
void DFS(Graph graph, char* v);  // dfs
void BFS(Graph graph, char* v);  // bfs

#endif			   // #ifndef GRAPH_H 끝
