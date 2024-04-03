#include <algorithm>
#include <iostream>
#include <vector>

//найти компоненты сильной связанности

class Graph {
private:
  size_t size_;
  std::vector<std::vector<int>> graph_;
  std::vector<int> used_;
  std::vector<int> color_;
  int timer_ = 0;

public:
  std::vector<std::pair<int, size_t>> time;

  Graph(size_t size)
      : size_(size), graph_(size), used_(size), color_(size), time(size - 1) {}

  void AddEdge(int vertex1, int vertex2);

  void Dfs(size_t vertex);

  void DfsCnt(size_t vertex, size_t cnt);

  void TimeCnt();

  void CountComponents();
};

void Graph::AddEdge(int vertex1, int vertex2) {
  graph_[vertex1].push_back(vertex2);
}

void Graph::Dfs(size_t vertex) {
  used_[vertex] = 1;
  ++timer_;
  for (auto elem : graph_[vertex]) {
    if (used_[elem] == 0) {
      Dfs(elem);
    }
  }
  used_[vertex] = 2;
  time[vertex - 1] = {timer_++, vertex};
}

void Graph::DfsCnt(size_t vertex, size_t cnt) {
  color_[vertex] = cnt;
  for (auto elem : graph_[vertex]) {
    if (color_[elem] == 0) {
      DfsCnt(elem, cnt);
    }
  }
}

void Graph::TimeCnt() {
  for (size_t i = 1; i < size_; ++i) {
    if (used_[i] == 0) {
      Dfs(i);
    }
  }
  std::sort(time.rbegin(), time.rend());
}

void Graph::CountComponents() {
  size_t cnt = 1;
  for (size_t i = 0; i < size_ - 1; ++i) {
    if (color_[time[i].second] == 0) {
      DfsCnt(time[i].second, cnt);
      ++cnt;
    }
  }
  std::cout << cnt - 1 << "\n";
  for (size_t i = 1; i < size_; ++i) {
    std::cout << color_[i] << ' ';
  }
}

int main() {
  size_t num_vertex;
  size_t edge;
  std::cin >> num_vertex >> edge;
  Graph graph(num_vertex + 1);
  Graph graph_reverse(num_vertex + 1);
  for (size_t i = 0; i < edge; ++i) {
    int start;
    int finish;
    std::cin >> start >> finish;
    graph.AddEdge(start, finish);
    graph_reverse.AddEdge(finish, start);
  }
  graph.TimeCnt();
  graph_reverse.time = graph.time;
  graph_reverse.CountComponents();
}
