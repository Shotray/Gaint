#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

struct Edge {
  string from;
  string to;
  int distance;
  bool operator <(const Edge& rhs)const {
    return distance < rhs.distance;
  }
};

string unionFind(map<string, string> m, string x){
  return m[x] == x ? x : m[x] = unionFind(m, m[x]);
}

bool checkUnionFind(map<string, string>m) {
  map<string, string>::iterator it = m.begin();
  string ans = unionFind(m, it->first);
  for (it = m.begin();it != m.end();it++) {
    if (unionFind(m,it->second) != ans)
      return false;
  }
  return true;
}

vector<Edge> Kruskal(vector<Edge> edge, map<string, string> m, vector<string> vertex) {
  vector<Edge> ans;
  sort(edge.begin(), edge.end());
  for (int i = 0;i < edge.size();i++) {
    if (unionFind(m, edge[i].from) == unionFind(m, edge[i].to))
      continue;
    m[unionFind(m, edge[i].to)] = unionFind(m, edge[i].from);
    ans.push_back(edge[i]);
  }
  if (!checkUnionFind(m))
  {
    cout << "There is no minimum spanning tree in the graph." << endl;
    ans.clear();
  }
  return ans;
}

string minKey(map<string,int>key,vector<Edge>& ans,map<string,bool> is_visited){
  map<string, int>::iterator it;
  int min_key = INT_MAX;
  string min_index;
  for (it = key.begin();it != key.end();it++) {
    if (min_key > it->second&&!is_visited[it->first]) {
      min_key = it->second;
      min_index = it->first;
    }
  }
  return min_index;
}

vector<Edge> Prim(vector<Edge> edge, vector<string> vertices,string x) {
  map<string, bool> is_visited;
  map<string, int> key;
  vector<Edge> prim;
  map<string, string> parent;
  for (int i = 0;i < vertices.size();i++) {
    is_visited[vertices[i]] = false;
    key[vertices[i]] = INT_MAX;
  }
  key[x] = 0;
  for (int i = 0;i < vertices.size();i++) {
    string u = minKey(key,prim,is_visited);
    is_visited[u] = true;
    if (i != 0) {
      Edge e;
      e.from = parent[u];
      e.to = u;
      e.distance = key[u];
      prim.push_back(e);
    }

    for (int i = 0;i < edge.size();i++) {
      if (edge[i].from == u && !is_visited[edge[i].to]) {
        key[edge[i].to] = edge[i].distance;
        parent[edge[i].to] = u;
      }
      else if (edge[i].to == u && !is_visited[edge[i].from]) {
        key[edge[i].from] = edge[i].distance;
        parent[edge[i].from] = u;
      }
    }
  }

  //check
  map<string, bool>::iterator it;
  for (it = is_visited.begin();it != is_visited.end();it++) {
    if (!it->second) {
      cout << "There is no MST."<<endl;
      prim.clear();
    }
  }
  
  return prim;
}

void print(vector<Edge> MST) {
  if (MST.size() == 0) {
    cout << "The tree is empty!" << endl;
    return;
  }
  for (int i = 0;i < MST.size();i++) {
    cout << MST[i].from << "-<" << MST[i].distance << ">->" << MST[i].to << "      ";
  }
  cout << endl;
  return;
}

bool is_valid(string s, vector<string> ver) {
  for (int i = 0;i < ver.size();i++)
    if (s == ver[i]) return true;
  return false;
}

void solve() {
  cout << "**      Power grid cost simulation system      **" << endl;
  cout << "=================================================" << endl;
  cout << "**          A---Creating grid vertices         **" << endl;
  cout << "**             B---Add side of grid            **" << endl;
  cout << "**    C---Constructing minimum spanning tree   **" << endl;
  cout << "**        D---Show minimum spanning tree       **" << endl;
  cout << "**                   E---Exit                  **" << endl;
  cout << "=================================================" << endl;
  vector<Edge> min_spanning_tree;
  vector<Edge> edge;
  vector<string> vertices;
  map<string, string> union_find;
  while (true) {
    cout << "Please select an action:";
    char op;
    cin >> op;
    if (op == 'A') {
      int total;
      cout << "Please input the number of vertices:";
      cin >> total;
      if (cin.fail())
        throw invalid_argument("Wrong Input!");
      cout << "Please input the vertices:";
      for (int i = 0;i < total;i++) {
        string vertex;
        cin >> vertex;
        vertices.push_back(vertex);
      }
    }
    else if (op == 'B') {
      while (true) {
        cout << "Please input two vertices and edge:";
        Edge e;
        cin >> e.from >> e.to >> e.distance;
        if (e.from == "?" && e.to == "?" && e.distance == 0)
          break;
        if (!is_valid(e.from, vertices) || !is_valid(e.to, vertices))
          throw invalid_argument("Wrong Input!");
        union_find[e.from] = e.from;
        union_find[e.to] = e.to;
        edge.push_back(e);
      }
    }
    else if (op == 'C') {
      cout << "Please enter the starting vertex:";
      string s;
      cin >> s;
      if (!is_valid(s, vertices))
        throw invalid_argument("Wrong Input!");
      //Prim
      min_spanning_tree = Prim(edge, vertices, s);

      //Kruskal
      //min_spanning_tree = Kruskal(edge, union_find, vertices);

      if(min_spanning_tree.size()!=0)
        cout << "Minimum spanning tree generated!" << endl;
    }
    else if (op == 'D') {
      cout << "Vertices and edges in minimum spanning tree are:" << endl;
      print(min_spanning_tree);
    }
    else if (op == 'E') {
      break;
    }
    else {
      throw invalid_argument("Wrong Input");
    }
  }
  return;
}

int main(void) {
  solve();
  return 0;
}