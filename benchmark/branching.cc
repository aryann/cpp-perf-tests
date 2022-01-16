// This is a benchmark that compares two simple filtering algorithms. In each
// benchmark, we generate a vector of random integers in the range [0, 100) and
// copy a subset of the elements into a new vector based off of a
// benchmark-specified selectivity ratio starting with 0% and ending at 100%.
//
// The BM_FilteringWithBranching uses an if-statement to determine whether a
// value should be selected. BM_FilteringWithNoBranching optimistically copies
// each element into the destination and then optionally increments the
// destination vector's index based off of the results of a comparison involving
// the value and the selectivity ratio. We expect most modern compilers to
// produce branchless code for the BM_FilteringWithNoBranching benchmark. We
// also expect the branchless benchmark to be faster in most cases.
#include <iostream>
#include <mutex>
#include <vector>

#include "absl/strings/str_format.h"
#include "absl/synchronization/mutex.h"
#include "benchmark/benchmark.h"

static void BM_FilteringWithBranching(benchmark::State &state) {
  int selectivity = state.range(0);

  int size = 1 << 20;
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));
  std::vector<int> items(size / sizeof(int), 0);
  for (int &item : items) {
    item = std::rand() % 100;
  }

  std::vector<int> results(items.size(), 0);

  for (auto _ : state) {
    int resultsIndex = 0;
    for (int i = 0; i < items.size(); ++i) {
      if (items[i] < selectivity) {
        results[resultsIndex] = (items[i]);
        ++resultsIndex;
      }
    }

    results.resize(resultsIndex);
    benchmark::DoNotOptimize(results);
  }

  state.SetBytesProcessed(size * state.iterations());
}

static void BM_FilteringWithNoBranching(benchmark::State &state) {
  int selectivity = state.range(0);

  int size = 1 << 20;
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));
  std::vector<int> items(size / sizeof(int), 0);
  for (int &item : items) {
    item = std::rand() % 100;
  }

  std::vector<int> results(items.size(), 0);

  for (auto _ : state) {
    int resultsIndex = 0;
    for (int i = 0; i < items.size(); ++i) {
      results[resultsIndex] = items[i];
      resultsIndex += items[i] < selectivity ? 1 : 0;
    }

    results.resize(resultsIndex);
    benchmark::DoNotOptimize(results);
  }

  state.SetBytesProcessed(size * state.iterations());
}

BENCHMARK(BM_FilteringWithBranching)
    ->DenseRange(/* start = */ 0, /* limit = */ 100, /* step = */ 10);
BENCHMARK(BM_FilteringWithNoBranching)
    ->DenseRange(/* start = */ 0, /* limit = */ 100, /* step = */ 10);

BENCHMARK_MAIN();