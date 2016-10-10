
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
    float tot = 0;
    for (size_t i = 0; i != values.size(); ++i) {
      tot += values[i];
    }
    auto time = __rdtsc() - start;
    printf("took %f megacycles (res=%f)\n", time * 1e-6, tot);
  }
  
  {
    auto start = __rdtsc();
    float t0 = 0, t1 = 0, t2 = 0, t3 = 0;
    for (size_t i = 0; i != values.size(); i += 4) {
      t0 += values[i];
      t1 += values[i+1];
      t2 += values[i+2];
      t3 += values[i+3];
    }
    float tot = t0 + t1 + t2 + t3;
    auto time = __rdtsc() - start;
    printf("took %f megacycles (res=%f)\n", time * 1e-6, tot);
  }
}


