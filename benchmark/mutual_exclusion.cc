// This is a benchmark that tests the latency of various methods for achieving
// mutual exclusion on shared resources.
//
// The benchmarks all attempt to set values inside of a vector. All of the
// benchmarks are single-threaded, however, we use the mutual exclusion
// technique under test for each update. This allows us to do comparative
// analysis between the various techniques.
#include <iostream>
#include <mutex>
#include <vector>

#include "absl/strings/str_format.h"
#include "absl/synchronization/mutex.h"
#include "benchmark/benchmark.h"

constexpr auto kInitValue = 100;

static void BM_InitVectorWithStdMutex(benchmark::State &state) {
  int size = state.range(0);
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));

  std::mutex mutex;

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> items(size / sizeof(int), 0);
    state.ResumeTiming();

    for (int i = 0; i < items.size(); ++i) {
      const std::lock_guard<std::mutex> lock(mutex);
      items[i] = kInitValue;
    }
  }

  state.SetBytesProcessed(size * state.iterations());
}

static void BM_InitVectorWithAbslMutex(benchmark::State &state) {
  int size = state.range(0);
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));
  absl::Mutex mutex;

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> items(size / sizeof(int), 0);
    state.ResumeTiming();

    for (int i = 0; i < items.size(); ++i) {
      const absl::MutexLock lock(&mutex);
      items[i] = kInitValue;
    }
  }

  state.SetBytesProcessed(size * state.iterations());
}

static void BM_InitVectorWithCompareAndSet(benchmark::State &state) {
  int size = state.range(0);
  state.SetLabel(absl::StrFormat("%d KiB", size / (1 << 10)));

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::atomic<int>> items(size / sizeof(int));
    state.ResumeTiming();

    for (int i = 0; i < items.size(); ++i) {
      int expected = 0;
      int desired = kInitValue;
      if (!items[i].compare_exchange_strong(expected, desired)) {
        // This should never happen!
        std::abort();
      }
    }
  }

  state.SetBytesProcessed(size * state.iterations());
}

BENCHMARK(BM_InitVectorWithStdMutex)
    ->RangeMultiplier(8)
    ->Range(1 << 10, 1 << 26);
BENCHMARK(BM_InitVectorWithAbslMutex)
    ->RangeMultiplier(8)
    ->Range(1 << 10, 1 << 26);
BENCHMARK(BM_InitVectorWithCompareAndSet)
    ->RangeMultiplier(8)
    ->Range(1 << 10, 1 << 26);

BENCHMARK_MAIN();