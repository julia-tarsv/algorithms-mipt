#include <iostream>
#include <set>
#include <vector>

class Graph {
private:
  size_t size_;

public:
  std::vector<std::vector<std::pair<size_t, int>>> graph;

  explicit Graph(size_t size) : size_(size), graph(size) {}

  void AddEdge(size_t start, size_t end, int cost);

  size_t Size() const { return size_; }
};

void Graph::AddEdge(size_t start, size_t end, int cost) {
  graph[start].push_back({end, cost});
  graph[end].push_back({start, cost});
}

size_t MST(Graph& graph, size_t start) {
  std::set<std::pair<int, int>> set;
  set.insert({0, start});

  const int cKMax = 2009000999;
  std::vector<bool> used(graph.Size());
  std::vector<int> dist(graph.Size(), cKMax);
  dist[start] = 0;
  int mst = 0;

  while (!set.empty()) {
    std::pair<int, int> top = *set.begin();
    size_t vertex = top.second;
    int cost = top.first;
    set.erase(set.begin());

    while (used[vertex] && !set.empty()) {
      vertex = set.begin()->second;
      cost = set.begin()->first;
      set.erase(set.begin());
    }

    if (used[vertex] && set.empty()) {
      break;
    }

    used[vertex] = true;
    for (auto elem : graph.graph[vertex]) {
      set.insert({elem.second, elem.first});
    }
    mst += cost;
  }

  return mst;
}

int main() {
  size_t num;
  size_t edge;
  std::cin >> num >> edge;

  Graph graph(num);
  for (size_t i = 0; i < edge; ++i) {
    size_t start;
    size_t end;
    int cost;
    std::cin >> start >> end >> cost;
    --start;
    --end;
    graph.AddEdge(start, end, cost);
  }

  std::cout << MST(graph, 0);
}

