#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <climits>
#include <cmath>
#include <bits/stdc++.h>
#include <numeric>
using namespace std;
static const int inf = 9999; 
// Name: Saumya Sadh 
// PID: A17043544 

///////////////////////////////////////////////////////
//////////////       QUESTION 1 HERE   ////////////////
///////////////////////////////////////////////////////

vector<vector<vector<int>>> myFloyd(vector<vector<int>> M)
{
  int n = (int)M.size();
  vector<vector<int>> dist = M;
  vector<vector<vector<int>>> phases;
  phases.reserve(n);

  for (int k = 0; k < n; ++k) {
    vector<vector<int>> next = dist;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        // 'inf' is from the starter (defined as 9999). Use it as infinity.
        if (dist[i][k] != inf && dist[k][j] != inf) {
          int via = dist[i][k] + dist[k][j];
          if (via < next[i][j]) next[i][j] = via;
        }
      }
    }
    phases.push_back(next);     // phase after allowing k as an intermediate
    dist.swap(next);
  }
  return phases;                // size n
}


/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////
tuple<vector<vector<int>>, vector<int>>myDijkstra(vector<int> vertices, vector<tuple<int, int, int>> edges)
{
  int n = (int)vertices.size();

  // Build adjacency list
  vector<vector<pair<int,int> > > adj(n);
  for (size_t i = 0; i < edges.size(); ++i) {
    int u = get<0>(edges[i]);
    int v = get<1>(edges[i]);
    int w = get<2>(edges[i]);
    adj[u].push_back(make_pair(v, w));  // directed
  }

  const int INF = 1000000000;
  vector<int> dist(n, INF), parent(n, -1);
  vector<char> used(n, 0);
  dist[0] = 0;

  typedef pair<int,int> P; // (dist, node)
  priority_queue<P, vector<P>, greater<P> > pq;
  pq.push(make_pair(0, 0));

  while (!pq.empty()) {
    P top = pq.top(); pq.pop();
    int d = top.first, u = top.second;
    if (used[u]) continue;
    used[u] = 1;

    for (size_t idx = 0; idx < adj[u].size(); ++idx) {
      int v = adj[u][idx].first;
      int w = adj[u][idx].second;
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;
        pq.push(make_pair(dist[v], v));
      }
    }
  }

  // Reconstruct paths from 0 to each i
  vector<vector<int> > paths(n);
  for (int i = 0; i < n; ++i) {
    if (dist[i] == INF) {
      paths[i] = vector<int>();            // unreachable: empty path
    } else {
      vector<int> rev;
      for (int cur = i; cur != -1; cur = parent[cur]) rev.push_back(cur);
      reverse(rev.begin(), rev.end());     // now starts at 0
      paths[i] = rev;
    }
  }

  return make_tuple(paths, dist);
}



/////////////////////////////////////////////////////////
//////////////       QUESTION 3 HERE   //////////////////
/////////////////////////////////////////////////////////
tuple<vector<int>, int> myMSTTSP(vector<vector<int>> distance_matrix)
{
    int n = (int)distance_matrix.size();
  if (n == 0) return make_tuple(vector<int>(), 0);

  const int INF = 1000000000;

  // Prim's MST
  vector<int> key(n, INF), parent(n, -1);
  vector<char> inMST(n, 0);
  key[0] = 0;
  for (int it = 0; it < n; ++it) {
    int u = -1, best = INF;
    for (int v = 0; v < n; ++v)
      if (!inMST[v] && key[v] < best) { best = key[v]; u = v; }
    if (u == -1) break;
    inMST[u] = 1;
    for (int v = 0; v < n; ++v) {
      if (!inMST[v] && v != u && distance_matrix[u][v] < key[v]) {
        key[v] = distance_matrix[u][v];
        parent[v] = u;
      }
    }
  }

  // Build MST adjacency
  vector<vector<int> > tree(n);
  for (int v = 1; v < n; ++v) {
    int p = parent[v];
    if (p != -1) {
      tree[p].push_back(v);
      tree[v].push_back(p);
    }
  }
  for (int i = 0; i < n; ++i) sort(tree[i].begin(), tree[i].end());

  // Preorder DFS from 0
  vector<int> order, st;
  vector<char> seen(n, 0);
  st.push_back(0);
  while (!st.empty()) {
    int u = st.back(); st.pop_back();
    if (seen[u]) continue;
    seen[u] = 1;
    order.push_back(u);
    // push neighbors in reverse to visit in ascending order
    for (int idx = (int)tree[u].size() - 1; idx >= 0; --idx) {
      int v = tree[u][idx];
      if (!seen[v]) st.push_back(v);
    }
  }

  // IMPORTANT: tour must END at 0 for the grader
  vector<int> tour = order;
  tour.push_back(0);

  long long total = 0;
  for (int i = 0; i + 1 < (int)tour.size(); ++i)
    total += distance_matrix[tour[i]][tour[i+1]];

  return make_tuple(tour, (int)total);
}
