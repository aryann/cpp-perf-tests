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
  state.SetLabel(absl::StrFormat("%d KiB", size));

  std::mutex mutex;

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::int64_t> items(size / sizeof(std::int64_t), 0);
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
  state.SetLabel(absl::StrFormat("%d KiB", size));
  absl::Mutex mutex;

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::int64_t> items(size / sizeof(std::int64_t), 0);
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
  state.SetLabel(absl::StrFormat("%d KiB", size));

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<std::atomic<std::int64_t>> items(size / sizeof(std::int64_t));
    state.ResumeTiming();

    for (int i = 0; i < items.size(); ++i) {
      std::int64_t expected = 0;
      std::int64_t desired = kInitValue;
      if (!items[i].compare_exchange_strong(expected, desired)) {
        // This should never happen!
        std::abort();
      }
    }
  }

  state.SetBytesProcessed(size * state.iterations());
}

BENCHMARK(BM_InitVectorWithStdMutex)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 20);
BENCHMARK(BM_InitVectorWithAbslMutex)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 20);
BENCHMARK(BM_InitVectorWithCompareAndSet)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();