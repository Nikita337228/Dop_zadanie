#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define HEADER ("Лабораторная работа №7\nВыполнил: Педай Н.Д. \n\n")

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue>

using namespace std;

struct node
{
	int vertex;
	int weight;
	struct node* next;
};

struct Graph
{
	int numVertices;
	struct node** adjList;
};

struct node* createNode(int v, int w)
{
	struct node* newNode = (node*)(malloc(sizeof(struct node)));
	newNode->vertex = v;
	newNode->weight = w;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices)
{
	struct Graph* graph = (Graph*)(malloc(sizeof(struct Graph)));
	graph->numVertices = vertices;
	graph->adjList = (node**)(malloc(vertices * sizeof(struct node*)));
	for (int i = 0; i < vertices; i++)
		graph->adjList[i] = NULL;
	return graph;
}

void addEdge(Graph* graph, int** M, int i, int j)
{
	node* newNode = createNode(i, M[i][j]);
	if (graph->adjList[j] == NULL)
	{
		graph->adjList[j] = newNode;
		newNode = NULL;
	}
	node* temp = graph->adjList[j];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

void printGraph(struct Graph* graph)
{
	for (int i = 0; i < graph->numVertices; i++)
	{
		struct node* temp = graph->adjList[i];
		printf("%d-я вершина: ", i);
		while (temp)
		{
			printf("%d(%d) ", temp->vertex, temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
}

int** createMatrix(char* argv[], int n)
{
	int** M = (int**)(malloc(n * sizeof(int*)));
	for (int i = 0; i < n; i++)
	{
		M[i] = (int*)(malloc(n * sizeof(int)));
		for (int j = 0; j < n; j++)
		{
			if (rand() % 100 < 40 || i == j)
			{
				M[i][j] = 0;
			}
			else
			{
				if (!strcmp(argv[1], "-0"))
				{
					M[i][j] = 1;
				}
				else
				{
					M[i][j] = rand() % n;
				}
			}
		}
	}
	if (!strcmp(argv[2], "-0"))
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (M[i][j] > 0)
				{
					M[j][i] = M[i][j];
				}
			}
		}
	}
	return M;
}

void printMatrix(int** M, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf(" %d ", M[i][j]);
		}
		printf("\n");
	}
}

void BFSD(Graph* G, int n, int* dist, int x)
{
	queue <int> Q;
	node* node = G->adjList[x];
	Q.push(x);
	dist[x] = 0;
	while (!Q.empty())
	{
		x = Q.front();
		node = G->adjList[x];
		Q.pop();
		while (node)
		{
			if (dist[node->vertex] > dist[x] + node->weight)
			{
				Q.push(node->vertex);
				dist[node->vertex] = dist[x] + node->weight;
			}
			node = node->next;
		}
	}
}

void func(Graph* G, int** M, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] > 0)
			{
				addEdge(G, M, i, j);
			}
		}
	}
	printGraph(G);
	int x;
	int* dist = (int*)(malloc(n * sizeof(int)));
	printf("\nВведите номер вершины: ");
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
	{
		dist[i] = SHRT_MAX;
	}
	BFSD(G, n, dist, x);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", dist[i]);
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	if (argc > 1)
	{
		int n;
		sscanf(strtok(argv[3], "-"), "%d", &n);
		int** M = createMatrix(argv, n);
		Graph* G = createGraph(n);
		func(G, M, n);
	}
	else
	{
		printf("Введите аргументы!\n");
	}
	system("PAUSE");
	return 0;
}
