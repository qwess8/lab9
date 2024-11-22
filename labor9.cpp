// labor9.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;


typedef struct node {
    int data;
    struct node* next;
} node;

int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[i][j];
        }
    }
    return G;
}
 
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DiFS(int** G, int size, int* dist, int s) {
    queue <int> q;
    q.push(s);
    dist[s] = 0;
 
    while (!q.empty()) {
        s = q.front();
        q.pop();
        for (int i = 0; i < size; i++) {
            if (G[s][i] && dist[i]==-1) {
                q.push(i);
                dist[i] = dist[s] + 1;
            }
        }
    }
}

node** createAdj(int** G, int size) {
    node** A = (node**)malloc(size * sizeof(node*));
    for (int i = 0; i < size; i++) {
        A[i] = NULL;
        node* tail = NULL;
        for (int j = 0; j < size; j++) {
            if (G[i][j] == 1) {
                node* newNode = (node*)malloc(sizeof(node));
                newNode->data = j;
                newNode->next = NULL;
                if (tail == NULL) {
                    A[i] = newNode;
                }
                else {
                    tail->next = newNode;
                }
                tail = newNode;
            }
        }
    }
    return A;
}
 
void printAdj(node** A, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        node* current = A[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}

void DiFSA(node** A, int size, int* dist, int s) {
    queue <int> q;
    q.push(s);
    dist[s] = 0;
    node* current = NULL;
    while (!q.empty()) {
        current = A[q.front()];
		s = q.front();
        q.pop();
 
        while (current) {
            if (dist[current->data]==-1) {
                q.push(current->data);
                dist[current->data] = dist[s] + 1;
            }
            current = current->next;
        }
    }
}

void DiFSD(int** G,int size, int *dist, int s, int d){
	dist[s] = d;
	for(int i = 0;i<size;i++){
		if(G[s][i] == 1 && (dist[i] ==-1||dist[i] > d)){
			(d)++;
			DiFSD(G, size, dist, i, d);
			(d)--;
		}
	}
}

void DiFSAD(node** A, int *dist, int s, int d){
	dist[s] = d;
	node* current = A[s];
	while(current!= NULL){
		if(dist[current->data] == -1 || dist[current->data]>d){
			d++;
			DiFSAD(A, dist, current->data, d);
			d--;
		}
		current = current->next;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
    int nG = 500;
	int* dist = (int*)malloc(sizeof(int) * nG);
	int** G = createG(nG);
	float spent_time;
	clock_t start, end;
	node** A = createAdj(G, nG);
	//printG(G,nG);
	//printAdj(A,nG);

	for(int i = 0; i < nG; i++) dist[i] = -1;

	start = clock();
	DiFS(G, nG, dist, 0);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	printf("n: %d\nDiFS;%.3f;\n",nG, spent_time);
	

	//printf("\n");
	//for(int i = 0; i < nG; i++){
		//printf("%d: %d\n", i, dist[i]);
	//}

	for(int i = 0; i < nG; i++) dist[i] = -1;

	start = clock();
	DiFSA(A, nG, dist, 0);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	printf("n: %d\nDiFSA;%.3f;\n",nG, spent_time);
	

	for(int i = 0; i < nG; i++) dist[i] = -1;

	start = clock();
	DiFSAD(A, dist, 0, 0);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	printf("n: %d\nDiFSAD;%.3f;\n",nG, spent_time);

	for(int i = 0; i < nG; i++) dist[i] = -1;

	start = clock();
	DiFSD(G, nG, dist, 0, 0);
	end = clock();
	spent_time = (float)(end - start) / CLOCKS_PER_SEC;
	printf("n: %d\nDiFSD;%.3f;\n",nG, spent_time);
	

	
	

	getchar();
	
	return 0;
}

