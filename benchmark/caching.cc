// This is a benchmark that compares random and sequential access on vectors of
// varying sizes. In the random access benchmarks, the throughput results at
// various sizes should reveal the processor's L1, L2, and L3 cache sizes.
#include <iostream>
#include <mutex>
#include <vector>

#include "absl/strings/str_format.h"
#include "absl/synchronization/mutex.h"
#include "benchmark/benchmark.h"

static void BM_RandomAccess(benchmark::State &state) {
  int size = state.range(0);
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));
  std::vector<int> items(size / sizeof(int), 0);

  std::vector<int> indices;
  indices.reserve(items.size());
  for (int i = 0; i < items.size(); ++i) {
    indices.push_back(std::rand() % items.size());
  }

  for (auto _ : state) {
    long sum = 0;
    for (int index : indices) {
      sum += items[index];
    }
    benchmark::DoNotOptimize(sum);
  }

  state.SetBytesProcessed(size * state.iterations());
}

static void BM_SequentialAccess(benchmark::State &state) {
  int size = state.range(0);
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));
  std::vector<int> items(size / sizeof(int), 0);

  // N.B.: To be fair to the random access benchmark, we also use a second
  // vector to hold the indices we will access.
  std::vector<int> indices;
  indices.reserve(items.size());
  for (int i = 0; i < items.size(); ++i) {
    indices.push_back(i);
  }

  for (auto _ : state) {
    long sum = 0;
    for (int index : indices) {
      sum += items[index];
    }
    benchmark::DoNotOptimize(sum);
  }

  state.SetBytesProcessed(size * state.iterations());
}

BENCHMARK(BM_RandomAccess)->RangeMultiplier(2)->Range(1 << 10, 1 << 26);
BENCHMARK(BM_SequentialAccess)->RangeMultiplier(2)->Range(1 << 10, 1 << 26);

BENCHMARK_MAIN();