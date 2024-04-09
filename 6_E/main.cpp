#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

// найти все мосты

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<int> used_;
  std::vector<int> ret_;

 public:
  int timer = 0;
  std::vector<std::pair<int, size_t>> time;
  std::vector<std::pair<int, int>> bridges;

  Graph(size_t size) : graph_(size), used_(size), ret_(size), time(size) {}

  void AddEdge(int vertex1, int vertex2);

  std::vector<int>& GetGraph(size_t vertex) { return graph_[vertex]; }

  std::vector<int>& GetUsed() { return used_; }

  std::vector<int>& GetRet() { return ret_; }
};

void Graph::AddEdge(int vertex1, int vertex2) {
  graph_[vertex1].push_back(vertex2);
  graph_[vertex2].push_back(vertex1);
}

void Dfs(Graph& graph, int vertex, int previous) {
  graph.GetUsed()[vertex] = 1;
  graph.time[vertex].first = graph.timer;
  ++graph.timer;
  graph.GetRet()[vertex] = graph.time[vertex].first;

  for (auto elem : graph.GetGraph(vertex)) {
    if (elem == previous) {
      continue;
    }

    if (graph.GetUsed()[elem] == 0) {
      Dfs(graph, elem, vertex);
      graph.GetRet()[vertex] =
          std::min(graph.GetRet()[vertex], graph.GetRet()[elem]);

      if (graph.GetRet()[elem] == graph.time[elem].first) {
        graph.bridges.push_back({vertex, elem});
      }
    } else {
      graph.GetRet()[vertex] =
          std::min(graph.GetRet()[vertex], graph.time[elem].first);
    }
  }
}

void CntBridges(Graph& graph, size_t size) {
  for (size_t i = 1; i < size; ++i) {
    if (graph.GetUsed()[i] == 0) {
      Dfs(graph, i, -1);
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

  CntBridges(graph, num_vertex + 1);

  std::vector<size_t> res;
  for (size_t i = 0; i < graph.bridges.size(); ++i) {
    if (double_edges.find({graph.bridges[i]}) != double_edges.end()) {
      continue;
    }
    res.push_back(num_edge.find(graph.bridges[i])->second);
  }

  std::cout << res.size() << "\n";
  std::sort(res.begin(), res.end());
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << ' ';
  }
}
