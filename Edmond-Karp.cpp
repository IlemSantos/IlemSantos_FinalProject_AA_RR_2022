#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

// Numero de vertices do Grafo
#define V 8

// Funcao de busca em largura,
// retorna verdade caso haja um caminho entre S e T
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {

	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	
	return (visited[t] == true);
}

int fordFulkerson(int graph[V][V], int s, int t) {
	int u, v;

	// Grafo residual
	int rGraph[V][V];

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	// vetor que guarda o caminho do bfs
	int parent[V];

	int max_flow = 0;

	// Enquanto houver caminhos validos de S a T,
	// realiza a augmentacao do fluxo
	while (bfs(rGraph, s, t, parent)) {
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;

		cout << "Gráfico residual após a interação: \n\n";
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				cout << rGraph[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}

	return max_flow;
}

int main() {

	// O grafo deve ser estetico e representado pela matriz de adjacencia
	int graph[V][V] = {{0, 1, 1, 1, 0, 0, 0, 0},
					   {0, 0, 0, 0, 1, 0, 0, 0},
					   {0, 0, 0, 0, 1, 0, 0, 0},
					   {0, 0, 0, 0, 0, 0, 1, 0},
					   {0, 0, 0, 0, 0, 0, 0, 1},
					   {0, 0, 0, 0, 0, 0, 0, 1},
					   {0, 0, 0, 0, 0, 0, 0, 1},
					   {0, 0, 0, 0, 0, 0, 0, 0}};

	int solution = fordFulkerson(graph, 0, 7);
	cout << "O Maximo de funcionário alocado: " << solution << endl;

	return 0;
}
