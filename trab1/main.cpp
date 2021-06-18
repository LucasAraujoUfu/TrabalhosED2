#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "lib/sort.h"

#define N 10
#define M 50000

using namespace std;

int main(void){
	vector<int> x = {0, 10, 20, 40, 80, 160, 320};
	vector<int> v[N];	
	
	for(int k : x){
		for(int i=0;i<N;i++){
			v[i] = vector<int>(M);
			for(int j=0;j<v[i].size();j++){
				v[i][j] = rand()%M+1;
			}
		}
		//Msort(v,0,v.size()-1,0);
		//selectSort(v,0,v.size()-1);
		clock_t t[2];
		t[0] = clock();
		for(int i=0;i<N;i++){
			btnUpsort(v[i],k);
		}
		t[1] = clock();
		double tmp = (t[1] - t[0]) / (double)CLOCKS_PER_SEC;
		printf("%d:\n%g s\n",k,tmp);
		/*
		for(int j=0;j<N;j++){
			for(int i=0;i<v[j].size();i++){
				printf("%d ",v[j][i]);
			}
			printf("\n");
		}
		cout<<endl;
		*/
	}
	return 0;
}
