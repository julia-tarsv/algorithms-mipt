#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

// найти все мосты

int timer = 0;
class Graph {
 private:
  std::vector<std::vector<int>> graph_;

 public:
  Graph(size_t size) : graph_(size) {}

  void AddEdge(int vertex1, int vertex2);

  std::vector<int>& GetGraph(size_t vertex) { return graph_[vertex]; }
};

void Graph::AddEdge(int vertex1, int vertex2) {
  graph_[vertex1].push_back(vertex2);
  graph_[vertex2].push_back(vertex1);
}

void Dfs(Graph& graph, std::pair<int, int> vertex_previous,
         std::vector<int>& used, std::vector<int>& ret,
         std::vector<std::pair<int, size_t>>& time,
         std::vector<std::pair<int, int>>& bridges) {
  used[vertex_previous.first] = 1;
  time[vertex_previous.first].first = timer;
  ++timer;
  ret[vertex_previous.first] = time[vertex_previous.first].first;

  for (auto elem : graph.GetGraph(vertex_previous.first)) {
    if (elem == vertex_previous.second) {
      continue;
    }

    if (used[elem] == 0) {
      Dfs(graph, {elem, vertex_previous.first}, used, ret, time, bridges);
      ret[vertex_previous.first] =
          std::min(ret[vertex_previous.first], ret[elem]);

      if (ret[elem] == time[elem].first) {
        bridges.push_back({vertex_previous.first, elem});
      }
    } else {
      ret[vertex_previous.first] =
          std::min(ret[vertex_previous.first], time[elem].first);
    }
  }
}

void CntBridges(Graph& graph, size_t size, std::vector<int>& used,
                std::vector<int>& ret,
                std::vector<std::pair<int, size_t>>& time,
                std::vector<std::pair<int, int>>& bridges) {
  for (size_t i = 1; i < size; ++i) {
    if (used[i] == 0) {
      Dfs(graph, {i, -1}, used, ret, time, bridges);
    }
  }
}

int main() {
  size_t num_vertex;
  size_t edge;
  std::cin >> num_vertex >> edge;
  Graph graph(num_vertex + 1);
  std::map<std::pair<size_t, size_t>, size_t> num_edge;
  std::set<std::pair<size_t, size_t>> double_edges;

  std::vector<int> used(num_vertex + 1);
  std::vector<int> ret(num_vertex + 1);
  std::vector<std::pair<int, size_t>> time(num_vertex + 1);
  std::vector<std::pair<int, int>> bridges;

  for (size_t i = 0; i < edge; ++i) {
    int start;
    int finish;
    std::cin >> start >> finish;

    if (num_edge.find({start, finish}) != num_edge.end() ||
        num_edge.find({finish, start}) != num_edge.end()) {
      double_edges.insert({start, finish});
      double_edges.insert({finish, start});
      continue;
    }

    graph.AddEdge(start, finish);
    num_edge.insert({{start, finish}, i + 1});
    num_edge.insert({{finish, start}, i + 1});
  }

  CntBridges(graph, num_vertex + 1, used, ret, time, bridges);

  std::vector<size_t> res;
  for (size_t i = 0; i < bridges.size(); ++i) {
    if (double_edges.find({bridges[i]}) != double_edges.end()) {
      continue;
    }
    res.push_back(num_edge.find(bridges[i])->second);
  }

  std::cout << res.size() << "\n";
  std::sort(res.begin(), res.end());
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << ' ';
  }
}
