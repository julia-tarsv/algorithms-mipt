#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

// найти все мосты в графе

class Graph {
private:
  size_t size_;
  std::vector<std::vector<int>> graph_;
  std::vector<int> used_;
  std::vector<int> ret_;
  int timer_ = 0;

public:
  std::vector<std::pair<int, size_t>> time;
  std::vector<std::pair<int, int>> bridges;

  Graph(size_t size)
      : size_(size), graph_(size), used_(size), ret_(size), time(size) {}

  void AddEdge(int vertex1, int vertex2);

  void Dfs(int vertex, int previous);

  void CntBridges();
};

void Graph::AddEdge(int vertex1, int vertex2) {
  graph_[vertex1].push_back(vertex2);
  graph_[vertex2].push_back(vertex1);
}

void Graph::Dfs(int vertex, int previous) {
  used_[vertex] = 1;
  time[vertex].first = timer_;
  ++timer_;
  ret_[vertex] = time[vertex].first;
  for (auto elem : graph_[vertex]) {
    if (elem == previous) {
      continue;
    }
    if (used_[elem] == 0) {
      Dfs(elem, vertex);
      ret_[vertex] = std::min(ret_[vertex], ret_[elem]);
      if (ret_[elem] == time[elem].first) {
        bridges.push_back({vertex, elem});
      }
    } else {
      ret_[vertex] = std::min(ret_[vertex], time[elem].first);
    }
  }
}

void Graph::CntBridges() {
  for (size_t i = 1; i < size_; ++i) {
    if (used_[i] == 0) {
      Dfs(i, -1);
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
  graph.CntBridges();

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