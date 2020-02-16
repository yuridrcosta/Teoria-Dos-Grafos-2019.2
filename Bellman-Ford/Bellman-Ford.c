#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 999999999

/* Formato de entrada: 1 linha com o número de vértices N e o número de arestas M seguidos de M linhas com 
 * o vértice de ínicio V1, vértice incidente V2 e o peso W:
 *
 * N M
 * V1 V2 W1
 * v3 V5 W2
 *
 */

void print_graph(int v_number, int graph[v_number][v_number])
{
	int i, j;
	for(i=0; i<v_number; i++){
      for(j=0; j<v_number; j++){
        if(graph[i][j] > INFINITY - 10000){ 
        	printf("+   ");
        }else{
        	printf("%d   ", graph[i][j]);
        }	
      }
      printf("\n");
	}
	printf("\nObs.: + significa que o peso da aresta eh infinito\n");
}

void BellmanFord(int v_number, int graph[v_number][v_number], int start){
	int i,j,k;
	int dist[v_number];
	int prev[v_number];

	for(i=0;i<v_number;i++){
		dist[i]=INFINITY;
		prev[i]=-1;
	}

	dist[start]=0;
	prev[start]=start;

	for(i=0;i<v_number-1;i++){
		for(j=0; j<v_number;j++){
			for(k=1;k<v_number;k++){
				if(graph[j][k]!=INFINITY && dist[k]>dist[j]+graph[j][k]){
					dist[k]=dist[j]+graph[j][k];
					prev[k]=j;
				}	
			}
		}
	}
	printf("Array de Distancias em relacao ao Vertice Inicial (0)\n\n");
	for(i=0;i<v_number;i++){
		printf("%d ",dist[i]);
	}
	printf("\n\n\n");
	printf("Array de Predecessores\n\n");
	for(i=0;i<v_number;i++){
		printf("%d ",prev[i]);
	}
	printf("\n");
}

int main(){

	FILE *file;
	file = fopen("entrada","r");

	if(file == NULL){
		printf("Não foi possível abrir o arquivo de entrada \n");
		return 0;
	}

	int v_number;//Número de Vértices
	int e_number;//Número de Arestas
	int i,j;
	int v1,v2,w;//Vertice de início, vertice incidente e peso

	fscanf(file,"%d %d", &v_number, &e_number);

	int graph[v_number][v_number];
	int weight[v_number][v_number];

	//Inicializando com 0
	for(i=0;i<v_number;i++){
		for(j=0;j<v_number;j++){
			if(i != j){
				graph[i][j]=INFINITY;
			}else{
				graph[i][j]=0;
			}
		}
	}

	//Lendo as arestas
	for(i = 0;i<e_number;i++){
		fscanf(file,"%d %d %d", &v1,&v2,&w);
		graph[v1][v2]=w;
	}

	//printf("Matriz de Adjacencias: \n\n");
	//print_graph(v_number,graph);

	//Após o Floyd-Warshall, a matriz de adjacências do grafo será usada como matriz
	// de distâncias entre dois vértices
	BellmanFord(v_number,graph,0);
	return 0;
}
