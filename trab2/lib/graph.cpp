#ifndef GRAPH_C
#define GRAPH_C

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <sstream>

#include "graph.h"

using namespace std;

graph create_graph(int v){
	graph g(v);
	return g;
}

graph read_graph(FILE *file){
	
	graph g;
	
	if(file == NULL)return g;
	
	bool din=true;

	while(!feof(file)){
		stringstream ss;
		char l[200];
		int x,y;
		fgets(l,200,file);
		if(l[0]=='%')continue;
		else if(din){
			int z;
			din = false;
			ss<<l;
			ss>>x>>z>>y;
			g.resize(x+1);
		}
		else{
			ss<<l;
			ss>>x>>y;
			//cout<<x<<" "<<y<<endl;
			g[x].push_back(y);
			g[y].push_back(x);
		}
	}

	return g;
}

int write_graph(FILE *file,graph &g){
	
	if(file == NULL)return EOF_ERROR;
	
	set<pair<int,int>> S;
	
	for(int i=0;i<g.size();i++){
		for(int j=0;j<g[i].size();j++){
			int v = g[i][j];
			if(S.find({i,v})==S.end()&&S.find({v,i})==S.end()){
				S.insert({i,v});
			}
		}
	}
	
	fprintf(file,"%lu %lu %lu\n",g.size()-1,g.size()-1,S.size());
	
	for(pair<int,int> p:S){
		fprintf(file,"%d %d\n",p.first,p.second);
	}
	
	return SUCCESS;
	
}

int write_edgeList(FILE *file, graph g){
	
	if(file == NULL)return EOF_ERROR;
	
	set<pair<int,int>> S;
	
	for(int i=0;i<g.size();i++){
		for(int j=0;j<g[i].size();j++){
			int v = g[i][j];
			if(S.find({i,v})==S.end()&&S.find({v,i})==S.end()){
				S.insert({i,v});
			}
		}
	}
	
	for(pair<int,int> p:S){
		fprintf(file,"%d %d\n",p.first,p.second);
	}
	
	return SUCCESS;
	
}

int write_conectedComponents(string arq, graph g){
	
	int comp[g.size()] = {0};
	
	deque<int> q;
	int label = 0;
	for(int i=1;i<g.size();i++){
		
		if(comp[i]==0){
			q.push_back(i);
			label++;
		}
		
		graph g1(g.size());
		
		while(!q.empty()){
			int u = q.front();
			q.pop_front();
			
			if(comp[u]!=0)continue;
			
			comp[u] = label;
			
			for(int j=0;j<g[u].size();j++){
				q.push_back(g[u][j]);
				add_edge(u,g[u][j],g1);
			}
			
		}
		
		FILE *file = fopen((arq+" "+to_string(label).c_str()+".txt").c_str(),"w");
		write_graph(file,g1);
		
	}
	
	return SUCCESS;
}

int write_edgeList_conectedComponents(string arq, graph g){
	
	int comp[g.size()] = {0};
	
	deque<int> q;
	int label = 0;
	for(int i=1;i<g.size();i++){
		
		if(comp[i]==0){
			q.push_back(i);
			label++;
		}
		
		graph g1(g.size());
		
		set<int> Sver;
		
		while(!q.empty()){
			int u = q.front();
			q.pop_front();
			
			if(comp[u]!=0)continue;
			
			comp[u] = label;
			Sver.insert(u);
			for(int j=0;j<g[u].size();j++){
				q.push_back(g[u][j]);
				add_edge(u,g[u][j],g1);
			}
			
		}
		if(Sver.size()>0){
			FILE *file = fopen((arq+" "+to_string(label).c_str()+".txt").c_str(),"w");
			for(int j : Sver){
				fprintf(file,"%d ",j);
			}fprintf(file,"\n");
			write_edgeList(file,g1);
		}
	}
	
	return SUCCESS;
}

int add_edge(int x,int y,graph &g){
	if(x>g.size()||y>g.size())return SIZE_ERROR;
	g[x].push_back(y);
	g[y].push_back(x);
	return SUCCESS;
}

int remove_edge(int x,int y,graph &g){
	if(x>g.size()||y>g.size())return VERTEX_NOT_FOUND;
	bool ap=false;
	for(int i=0;i<g[x].size();i++){
		if(g[x][i] == y){
			g[x].erase(g[x].begin()+i);
			ap = true;
		}
	}
	if(!ap)return EDGE_NOT_FOUND;
	for(int i=0;i<g[y].size();i++){
		if(g[y][i] == x){
			g[y].erase(g[y].begin()+i);
			ap = true;
		}
	}
	if(!ap)return EDGE_NOT_FOUND;
	return SUCCESS;
}

int ksn(graph &g,int n){
	
	int grau[g.size()] = {0}; // grau de cada vertice
	int comp[g.size()] = {0}; // memo de vertices computados
	for(int i=0;i<=g.size();i++){ // le o grau de cada vertice
		grau[i] = g[i].size(); 
	}
	
	for(int i=0;i<=g.size();i++){
		deque<int> q; // fila de vertices
		if(comp[i]==0){ // verifica se o vertice foi visitado
			q.push_back(i); // adiciona na fila o vertice não visitado
		}
		
		while(!q.empty()){ // bfs
			
			int u = q.front(); // pegar o proximo na fila
			q.pop_front(); // tira da fila
			
			if(comp[u]==1)continue;
			
			comp[u] = 1;
			
			priority_queue<pair<int,int>> pq; //fila que guardará a prioridade de remoção de arestas
			
			for(int j=0;j<g[u].size();j++){ //percorre os vizinhos de u
				
				int v = g[u][j]; //vertice que estmos visitando
				
				pq.push({-grau[v],v}); //colocamos o vertice e seu grau em uma fila de prioridade
				
				q.push_back(v); // adicionamos o vertice a fila da bfs para ser processado
				
			}
			
			
			while(pq.size()>n){
				remove_edge(u,pq.top().second,g); // removemos E_v - N arestas do vertice u
				pq.pop();
			}
			
		}
		
	}
	return SUCCESS;
}

#endif
