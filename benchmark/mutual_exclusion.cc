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

#include "absl/synchronization/mutex.h"
#include "benchmark/benchmark.h"

constexpr auto kInitValue = 100;

static void BM_InitVectorWithStdMutex(benchmark::State& state) {
    std::mutex mutex;

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<std::int64_t> items(state.range(0), 0);
        state.ResumeTiming();

        for (int i = 0; i < items.size(); ++i) {
            const std::lock_guard<std::mutex> lock(mutex);
            items[i] = kInitValue;
        }
    }
}

static void BM_InitVectorWithAbslMutex(benchmark::State& state) {
    absl::Mutex mutex;

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<std::int64_t> items(state.range(0), 0);
        state.ResumeTiming();

        for (int i = 0; i < items.size(); ++i) {
            const absl::MutexLock lock(&mutex);
            items[i] = kInitValue;
        }
    }
}

static void BM_InitVectorWithCompareAndSet(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<std::atomic<std::int64_t>> items(state.range(0));
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
}

BENCHMARK(BM_InitVectorWithStdMutex)
    ->Range(2 << 10, 2 << 20);
BENCHMARK(BM_InitVectorWithAbslMutex)
    ->Range(2 << 10, 2 << 20);
BENCHMARK(BM_InitVectorWithCompareAndSet)
    ->Range(2 << 10, 2 << 20);

BENCHMARK_MAIN();