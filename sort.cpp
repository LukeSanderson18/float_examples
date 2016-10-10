
#include <random>
#include <intrin.h>
#include <algorithm>
#include <cstdio>

int main() {
  std::vector<float> values(1024 * 1024);
  std::ranlux24 generator;
  std::uniform_real_distribution<float> distribution;
  std::for_each(values.begin(), values.end(), [&](float &v) { v = distribution(generator); });

  {
    auto start = __rdtsc();
    std::sort(values.begin(), values.end(), [](float a, float b) { return a < b; });
    auto time = __rdtsc() - start;
    printf("took %f megacycles\n", time * 1e-6);
  }
  
  {
    auto start = __rdtsc();
    std::sort((int*)values.data(), (int*)values.data() + values.size(), [](int a, int b) { return a < b; });
    auto time = __rdtsc() - start;
    printf("took %f megacycles\n", time * 1e-6);
  }
}


