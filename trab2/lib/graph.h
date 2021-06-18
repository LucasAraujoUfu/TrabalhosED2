#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define SUCCESS 0
#define EOF_ERROR -1
#define SIZE_ERROR -2
#define VERTEX_NOT_FOUND -3
#define EDGE_NOT_FOUND -4

typedef std::vector<std::vector<int>> graph;

graph create_graph(int v);
graph read_graph(FILE *file);

int write_graph(FILE *file,graph &g);
int write_edgeList(FILE *file, graph g);

int write_conectedComponents(std::string arq, graph g);
int write_edgeList_conectedComponents(std::string arq, graph g);

int add_edge(int x,int y,graph &g);
int remove_edge(int x,int y,graph &g);

int ksn(graph &g,int n);

#endif
