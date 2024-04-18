#include <algorithm>
#include <iostream>
#include <vector>

// найти компоненты сильной связности

class Graph {
 private:
  std::vector<std::vector<int>> graph_;

 public:
  int timer = 0;
  std::vector<std::pair<int, size_t>> time;

  explicit Graph(size_t size) : graph_(size), time(size - 1) {}

  void AddEdge(int vertex1, int vertex2);

  std::vector<int>& GetNeighbours(size_t vertex);
};

void Graph::AddEdge(int vertex1, int vertex2) {
  graph_[vertex1].push_back(vertex2);
}

void Dfs(Graph& graph, size_t vertex, std::vector<int>& used) {
  used[vertex] = 1;
  ++graph.timer;
  for (auto elem : graph.GetNeighbours(vertex)) {
    if (used[elem] == 0) {
      Dfs(graph, elem, used);
    }
  }

  used[vertex] = 2;
  graph.time[vertex - 1] = {graph.timer++, vertex};
}

void DfsCnt(Graph& graph, size_t vertex, size_t cnt, std::vector<int>& color) {
  color[vertex] = cnt;
  for (auto elem : graph.GetNeighbours(vertex)) {
    if (color[elem] == 0) {
      DfsCnt(graph, elem, cnt, color);
    }
  }
}

std::vector<int>& Graph::GetNeighbours(size_t vertex) { return graph_[vertex]; }

void TimeCnt(Graph& graph, size_t size, std::vector<int>& used) {
  for (size_t i = 1; i < size; ++i) {
    if (used[i] == 0) {
      Dfs(graph, i, used);
    }
  }

  std::sort(graph.time.rbegin(), graph.time.rend());
}

std::vector<int> CountComponents(Graph& graph, size_t size,
                                 std::vector<int>& color) {
  std::vector<int> res_components;

  size_t cnt = 1;
  for (size_t i = 0; i < size - 1; ++i) {
    if (color[graph.time[i].second] == 0) {
      DfsCnt(graph, graph.time[i].second, cnt, color);
      ++cnt;
    }
  }

  for (size_t i = 1; i < size; ++i) {
    res_components.push_back(color[i]);
  }

  return res_components;
}

int main() {
  size_t num_vertex;
  size_t edge;
  std::cin >> num_vertex >> edge;
  Graph graph(num_vertex + 1);
  Graph graph_reverse(num_vertex + 1);
  std::vector<int> used(num_vertex + 1);
  std::vector<int> color(num_vertex + 1);

  for (size_t i = 0; i < edge; ++i) {
    int start;
    int finish;
    std::cin >> start >> finish;
    graph.AddEdge(start, finish);
    graph_reverse.AddEdge(finish, start);
  }

  TimeCnt(graph, num_vertex + 1, used);
  graph_reverse.time = graph.time;

  std::vector<int> res = CountComponents(graph_reverse, num_vertex + 1, color);

  int cnt_components = 0;
  for (size_t i = 0; i < res.size(); ++i) {
    cnt_components = std::max(cnt_components, res[i]);
  }

  std::cout << cnt_components << "\n";
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << ' ';
  }
}
