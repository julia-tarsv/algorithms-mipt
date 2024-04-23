#include <algorithm>
#include <iostream>
#include <vector>

// найти цикл с восстановлением вершин в нём

class Graph {
private:
  size_t size_;

  struct Edge {
    int start;
    int finish;
    int cost;
  };

public:
  std::vector<Edge> graph;

  explicit Graph(size_t size) : size_(size), graph(size) {}

  void AddEdge(int start, int finish, int cost);

  size_t Size() const { return size_; }
};

void Graph::AddEdge(int start, int finish, int cost) {
  graph.push_back({start, finish, cost});
}

std::vector<int> FordBellman(const Graph& graph, std::vector<int>& dp,
                             std::vector<int>& parents) {
  for (size_t k = 1; k <= dp.size() - 1; ++k) {
    for (auto elem : graph.graph) {
      if (dp[elem.start] + elem.cost < dp[elem.finish]) {
        dp[elem.finish] = dp[elem.start] + elem.cost;
        parents[elem.finish] = elem.start;
      }
    }
  }

  std::vector<int> ans;
  for (auto elem : graph.graph) {
    if (dp[elem.start] + elem.cost < dp[elem.finish]) {
      int vertex = elem.finish;
      for (size_t j = 0; j < graph.Size() - 1; ++j) {
        vertex = parents[vertex];
      }
      int u = vertex;

      while (u != parents[vertex]) {
        ans.push_back(vertex);
        vertex = parents[vertex];
      }

      ans.push_back(vertex);
      ans.push_back(u);

      std::reverse(ans.begin(), ans.end());

      return ans;
    }
  }

  return ans;
}

int main() {
  size_t num;
  std::cin >> num;

  Graph graph(num + 1);

  const int cKInf = 1e5;

  for (size_t i = 1; i <= num; ++i) {
    for (size_t j = 1; j <= num; ++j) {
      int cost;
      std::cin >> cost;

      if (cost != cKInf) {
        graph.AddEdge(i, j, cost);
      }
    }
  }

  std::vector<int> dp(num + 1);
  std::vector<int> parents(num + 1, -1);

  std::vector<int> res = FordBellman(graph, dp, parents);
  if (!res.empty()) {
    std::cout << "YES"
              << "\n"
              << res.size() << "\n";
    for (size_t j = 0; j < res.size(); ++j) {
      std::cout << res[j] << ' ';
    }
    return 0;
  }

  std::cout << "NO";
}
