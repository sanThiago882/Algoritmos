#include <bits/stdc++.h>

using namespace std;

class Graph {

    private:

        vector<vector<int>> graph;
        vector<int> input;

        int nodes;

    public:

        Graph(int n) : graph(n), input(n, 0) {
            nodes = n;
        }

        int size() {
            return nodes;
        }
        void make_path(int a, int b) {
            graph[a].push_back(b);
            input[b]++;
        }
        bool has_path(int a, int b) {
            return find(graph[a].begin(), graph[a].end(), b) != graph[a].end();
        }
        int input_degree(int v) {
            return input[v];
        }
        int output_degree(int v) {
            return graph[v].size();
        }
        int distance_between_vertices(int a, int b) {
            int distance = 0;

            if(a != b) {
                queue<int> qnow, qnext, qempty;
                vector<int> visited(nodes, false);

                qnow.push(a);

                while(true) {
                    bool path = false;
                    while(!qnow.empty()) {
                        a = qnow.front();
                        qnow.pop();
                        visited[a] = true;

                        if(has_path(a, b)) {
                            path = true;
                        }

                        for(int i:graph[a]) {
                            if(!visited[i]) {
                                qnext.push(i);
                            }
                        }
                    }
                    distance++;

                    if(path) {
                        break;
                    }

                    if(qnow.empty() && qnext.empty()) {
                        distance = -1;
                        break;
                    }
                    qnow = qnext;
                    qnext = qempty;
                }
            }

            return distance;
        }
        void bfs(int v) {
            queue<int> q;
            vector<bool> visited(nodes, false);

            q.push(v);

            while(!q.empty()) {
                v = q.front();
                printf("%d\n", v);
                q.pop();
                visited[v] = true;

                for(int i:graph[v]) {
                    if(!visited[i]) {
                        q.push(i);
                    }
                }
            }
        }
        void dfs(int v) {
            stack<int> s;
            vector<bool> visited(nodes, false);

            while(true) {
                if(!visited[v]) {
                    s.push(v);
                    visited[v] = true;
                }

                bool unvisited = false;
                auto i = graph[v].begin();

                while(i != graph[v].end()) {
                    if(!visited[*i]) {
                        unvisited = true;
                        break;
                    }
                    i++;
                }

                if(unvisited) {
                    v = *i;
                } else {
                    printf("%d\n", s.top());
                    s.pop();
                    if(s.empty()) {
                        break;
                    }
                    v = s.top();
                }
            }
        }
};

int main() {

    Graph G(4);

    G.make_path(0, 1);
    G.make_path(0, 3);
    G.make_path(1, 2);
    G.make_path(3, 1);
    G.make_path(3, 2);

    for(int i = 0; i < G.size(); i++) {
        printf("Grau de Entrada [%d]: %d\n", i, G.input_degree(i));
        printf("  Grau de Saida [%d]: %d\n", i, G.output_degree(i));
    }

    printf("\n");

    for(int i = 0; i < G.size(); i++) {
        for(int j = 0; j < G.size(); j++) {
            if(i != j) {
                if(G.has_path(i, j)) {
                    printf("[%d] -> [%d] Existe Caminho\n", i, j);
                } else {
                    printf("[%d] -> [%d] Nao Existe Caminho\n", i, j);
                }
            }
        }
        printf("\n");
    }

    return 0;
}