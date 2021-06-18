#include <stdio.h>
#include <iostream>
#include <vector>

#include "lib/graph.h"

using namespace std;

graph g;

int main(void){
	FILE *file;
	string arq;
	while(true){
		printf("Digite o nome do arquivo do grafo (0 para sair): ");
		getline(cin,arq);
		if(arq=="0")break;
		
		file = fopen(arq.c_str(),"r");
		
		g = read_graph(file);
		
		fclose(file);
		
		int c = ksn(g,3);
		
		write_edgeList_conectedComponents("grafo",g);
		
		file = fopen("grafo.txt","w");
		
		write_graph(file,g);
		
		fclose(file);
		
		file = fopen("edgeList.txt","w");
		
		write_edgeList(file,g);
		
		fclose(file);
	}
	return 0;
}
