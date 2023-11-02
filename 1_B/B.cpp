#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  size_t number_of_mandrakes;
  std::cin >> number_of_mandrakes;
  std::vector<double> mandrakes(number_of_mandrakes);
  for (size_t i = 0; i < number_of_mandrakes; ++i) {
    double loudness;
    std::cin >> loudness;
    mandrakes[i] = log2(loudness);
  }
  std::vector<double> prefix_sum(number_of_mandrakes + 1, 0);
  prefix_sum[1] = mandrakes[0];
  for (size_t i = 2; i <= number_of_mandrakes; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + mandrakes[i - 1];
  }
  size_t requests;
  std::cin >> requests;
  const int kPrecision = 8;
  for (size_t i = 0; i < requests; ++i) {
    double left;
    double right;
    std::cin >> left >> right;
    ++left;
    ++right;
    double power = (prefix_sum[int(right)] - prefix_sum[int(left) - 1]) /
                   (right - left + 1);
    double mid_loudness = pow(2, power);
    std::cout << std::setprecision(kPrecision) << mid_loudness << std::endl;
  }
}
