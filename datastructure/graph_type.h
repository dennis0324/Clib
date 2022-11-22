#ifndef GRAPHTYPE_H
#define GRAPHTYPE_H

#include <stdio.h>
#include <stdlib.h>
 

#ifndef GRAPHELEMENT
#define GRAPHELEMENT int
#endif

typedef struct GraphVertex {
	int value;
	int preVertex;
	GRAPHELEMENT data;
	struct GraphVertex* next;
}GraphVertex;
 
typedef struct graph_type {
	int size;
	int total;
	GraphVertex** header;
}GraphType;
 
int vertex[100] = { 0 };
 
void init(GraphType** g) {
	for (int i = 0; i < (*g)->total; i++) {
		(*g)->header[i] = NULL;
	}
}
GraphType* createGraph(int n) {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	g->total = n;
	g->size = 0;
	g->header = (GraphVertex**)malloc(sizeof(GraphVertex*) * n);
 
	init(&g);
	return g;
}
 
 
void insertVertex(GraphType* g) {
	if (g->size >= g->total) return;
	g->size++;
}
 
void insertEdge(GraphType* g, int start, int end,GRAPHELEMENT data) {
	if (start >= g->total || end >= g->total) return;
	GraphVertex* ge = (GraphVertex*)malloc(sizeof(GraphVertex));
	ge->next = NULL;
	if (!ge) return;
	ge->data = data;
	ge->value = end;
	ge->next = g->header[start];
	g->header[start] = ge;
 
}
 
 
void deleteGraph(GraphType* g) {
	for (int i = 0; i < g->size; i++) {
		GraphVertex* gv = g->header[i];
		while (gv != NULL) {
			GraphVertex* temp = gv;
			gv = gv->next;
			free(temp);
		}
 
	}
	free(g);
}
 
 
void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->size; i++) {
		GraphVertex* p = g->header[i];
		printf("정점 [%d]", i);
		while (p != NULL) {
			printf("-> %d", p->value);
			p = p->next;
		}
		printf("\n");
	}
}
int adjacent(GraphType* g, int start) {
	int count = 0;
	if (start >= g->size) return;
	for (GraphVertex* n = g->header[start]; n; n = n->next) {
		count++;
	}
 
	return count;
}
 
 
void dfs_recur(GraphType* g, int v) {
	GraphVertex* node;
	vertex[v] = 1;
	printf("%d -> ", v);
	for (node = g->header[v]; node; node = node->next)
		if (!vertex[node->value]) {
			dfs_recur(g, node->value);
		}
}
 
 
 
 
void dfs_iter(GraphType* g, int v) {
	GraphVertex* stack[200];
	int top = -1;
 
 
	GraphVertex* node;
	vertex[v] = 1;
	stack[++top] = g->header[v];
	printf("%d -> ", v);
	while (top != -1) {
		node = stack[top--];
		vertex[node->value] = 1;
		printf("%d -> ", node->value);
		for (node = g->header[node->value]; node; node = node->next) {
			if (!vertex[node->value])
				stack[++top] = node;
		}
	}
}
 
void bfs_iter(GraphType* g, int v) {
	int que[100] = { 0 };
	int front = 0, rear = 0;
	printf("%d 방문",v);
	que[rear++] = v;
	while (front != rear) {
		v = que[front++];
		vertex[v] = 1;
		
		for (GraphVertex* temp = g->header[v]; temp; temp = temp->next) {
			if (!vertex[temp->value]) {
				printf(" -> %d", temp->value);
				vertex[temp->value] = 1;
				que[rear++] = temp->value;
			}
		}
	}
}

#endif