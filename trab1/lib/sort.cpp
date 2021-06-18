#ifndef SORT_C
#define SORT_C

#include <math.h>
#include <vector>

#include "sort.h"

using namespace std;

void mergeSort(vector<int> &v){
	Msort(v,0,v.size(),0);
}

void merge(vector<int> &v, int in, int m, int fm){
	vector<int> aux(v);
	int i = in, j = m+1;
	for(int k=in;k<=fm;k++){
		if(i>m)v[k] = aux[j++];
		else if(j>fm)v[k] = aux[i++];
		else if(aux[j]<aux[i])v[k] = aux[j++];
		else v[k] = aux[i++];
	}	
}

void btnUpsort(vector<int>& v,int c){
	int tam = v.size();
	for(int i=1;i<tam;i*=2){
		for(int j=0;j<tam-i;j+=i+i){
			if(fmin(tam-1,j+i+i-1)-j<=c)
				selectSort(v,j,fmin(tam-1,j+i+i-1));
			else
				merge(v,j,j+i-1,fmin(tam-1,j+i+i-1));
		}
	}
}


void Msort(vector<int> &v, int in, int fm,int c){
	if(in>=fm)return;
	else if(fm-in<=c){
		selectSort(v,in,fm);
	}
	else{
		int m = in + (fm-in)/2;
		Msort(v,in,m,c);
		Msort(v,m+1,fm,c);
		merge(v,in,m,fm);	
	}
}

void selectSort(vector<int>& v,int in,int fm){
	for(int i=in;i<fm;i++){
		int me = i;
		for(int j=i;j<=fm;j++){
			if(v[j]<v[me]){
				me = j;
			}
		}
		if(me!=i){
			swap(v[i],v[me]);
		}
	}
}

#endif
