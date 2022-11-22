// MIT License

// Copyright (c) 2022 Foxstar

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


// NOTE: this is not the best way to use as dikjstra algorithm
// THIS WILL BE FIXED!

#ifndef DIJKSTRA_H
#include <graph_type.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INF INFINITY


void dijkstra(GraphType * g,int start);

#endif
#define DIJKSTRA_IMPLEMENTATION
#ifdef DIJKSTRA_IMPLEMENTATION

int choose(GraphType * g,int * distance, int * visited){
    int min = INF;
    int minPos = -1;
    for(int i = 0; i < g->size; i++){
        if(distance[i] < min && !visited[i]){
            minPos = i;
            min = distance[i];
            break;
        }
    }

    return minPos;
}
void print(GraphType * g, int * distance){
    for(int i = 0; i < g->size; i++){
        printf("%-5d ",i);
    }
    printf("\n");
    for(int i = 0; i < g->size; i++){
        distance[i] == __INT32_MAX__ ? printf("%-5c ",'*') : printf("%-5d ",distance[i]);
    }
    printf("\n");
}
void dijkstra(GraphType * g,int start){
    int * distance = malloc(sizeof(*distance) * g->size);
    int * visited = malloc(sizeof(*visited) * g->size);

    for(int i = 0; i<g->size; i++){
        distance[i] = INF;
    }

    GraphVertex * node = g->header[start];
    while(node){
        distance[node->value] = node->data;
        node = node->next;
    }
    visited[start] = true;
    distance[start] = 0;

    for(int i = 0 ; i < g->size; i++){
        int vertex = choose(g,distance,visited);
        visited[vertex] = true;
        node = g->header[vertex];
        print(g,distance);
        while(node){
            if(!visited[node->value])
                if(distance[node->value] > g->header[node->value][vertex].data + distance[vertex]){
                    int alpha = distance[node->value];
                    GraphVertex a = g->header[node->value][vertex];
                    int b = distance[vertex];
                    distance[node->value] = g->header[node->value][vertex].data + distance[vertex];
                }
            node = node->next;
        }
    }

    free(distance);
    free(visited);
}
#endif