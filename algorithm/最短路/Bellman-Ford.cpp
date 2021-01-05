#include <iostream>
#include <vector>
using namespace std;

#define INF 2147483647

while(1) for each edge(u,v) relax(u,v);

struct Edge {
  int u, v;
  int w;
};


void BellmanFord(vector<int> dis) {
  int n = dis.size();
  int begin = 0;
  int u[30];
  int v[30];
  int w[30];
  vector<Edge> edge;
  for (int i = 0; i < n; i++) dis[i] = INF;
  dis[begin] = 0;
  for (int k = 0; k < n - 1; k++) {
    for (int i = 0; i < edge.size(); i++) {
      int x = edge[i].u, y = edge[i].v;
      if (dis[x] < INF) 
        dis[y] = min(dis[y], dis[x] + edge[i].w);
    }
  }
}
