#include <iostream>
#include <set>
#include <vector>

// найти расстояния от указанной комнаты до 0-й, 1-й и т.д.

const int cKMax = 2009000999;

class Graph {
 public:
  explicit Graph(size_t size) : size_(size), graph_(size) {}

  void UpdateGraph(size_t start, size_t end, size_t length);

  size_t Size() const { return size_; }

  std::vector<std::pair<int, int>> Neighbours(size_t vertex) {
    return graph_[vertex];
  }

 private:
  size_t size_;
  std::vector<std::vector<std::pair<int, int>>> graph_;
};

void Graph::UpdateGraph(size_t start, size_t end, size_t length) {
  graph_[start].push_back({end, length});
  graph_[end].push_back({start, length});
}

std::vector<int> FindDist(size_t start, Graph& graph) {
  std::set<std::pair<int, int>> set;
  set.insert({0, start});
  std::vector<int> dist(graph.Size(), cKMax);
  dist[start] = 0;

  while (!set.empty()) {
    std::pair<int, int> top = *set.begin();
    int vertex = top.second;
    set.erase(set.begin());

    for (auto elem : graph.Neighbours(vertex)) {
      int new_dist = dist[vertex] + elem.second;
      if (new_dist < dist[elem.first]) {
        set.erase({dist[elem.first], elem.first});
        dist[elem.first] = new_dist;
        set.insert({new_dist, elem.first});
      }
    }
  }

  return dist;
}

void Accelerate() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Accelerate();

  size_t tests;
  std::cin >> tests;

  for (size_t i = 0; i < tests; ++i) {
    size_t rooms;
    size_t corridors;
    std::cin >> rooms >> corridors;
    Graph graph(rooms);

    for (size_t j = 0; j < corridors; ++j) {
      size_t start;
      size_t end;
      size_t length;
      std::cin >> start >> end >> length;

      graph.UpdateGraph(start, end, length);
    }

    size_t start;
    std::cin >> start;

    std::vector<int> dist = FindDist(start, graph);
    for (size_t j = 0; j < dist.size(); ++j) {
      std::cout << dist[j] << ' ';
    }
    std::cout << "\n";
  }
}
