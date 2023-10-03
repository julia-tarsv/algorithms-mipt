#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;
  std::vector<double> mandragors(number);
  for (int i = 0; i < number; ++i) {
    double loud;
    std::cin >> loud;
    mandragors[i] = log2(loud);
  }
  std::vector<double> prefix_sum(number);
  prefix_sum[0] = mandragors[0];
  for (int i = 1; i < number; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + mandragors[i];
  }
  int requests;
  std::cin >> requests;
  std::vector<double> mid_loud(requests);
  for (int i = 0; i < requests; ++i) {
    double left;
    double right;
    std::cin >> left >> right;
    double stepen;
    if (left == 0) {
      stepen = prefix_sum[int(right)] / (right - left + 1);
    } else {
      stepen = (prefix_sum[int(right)] - prefix_sum[int(left) - 1]) /
               (right - left + 1);
    }
    mid_loud[i] = pow(2, stepen);
  }
  const int kPres = 8;
  for (int i = 0; i < requests; ++i) {
    std::cout << std::setprecision(kPres) << mid_loud[i] << std::endl;
  }
}
