# cpp-perf-tests

This repository contains a set of C++ benchmarks. The benchmarks are included in
the benchmarks/ directory. The next sections include the results of running each
benchmark on a 2020 Apple M1 processor. For more information about each
benchmark, refer to the comment in the C++ source code.

## branching

```s
$ bazel run benchmark:branching -c opt
Run on (8 X 2400 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x8)
  L1 Instruction 128 KiB (x8)
  L2 Unified 4096 KiB (x8)
Load Average: 1.41, 1.32, 1.47
------------------------------------------------------------------------------------------
Benchmark                                Time             CPU   Iterations UserCounters...
------------------------------------------------------------------------------------------
BM_FilteringWithBranching/0          82127 ns        82127 ns         8411 bytes_per_second=11.8909G/s 1024 KiB
BM_FilteringWithBranching/10        242700 ns       242700 ns         2894 bytes_per_second=4.02375G/s 1024 KiB
BM_FilteringWithBranching/20        388848 ns       388849 ns         1790 bytes_per_second=2.51142G/s 1024 KiB
BM_FilteringWithBranching/30        545909 ns       545905 ns         1276 bytes_per_second=1.78889G/s 1024 KiB
BM_FilteringWithBranching/40        726367 ns       726307 ns          944 bytes_per_second=1.34456G/s 1024 KiB
BM_FilteringWithBranching/50        835214 ns       835205 ns          838 bytes_per_second=1.16925G/s 1024 KiB
BM_FilteringWithBranching/60        761988 ns       761953 ns          941 bytes_per_second=1.28166G/s 1024 KiB
BM_FilteringWithBranching/70        577011 ns       576998 ns         1150 bytes_per_second=1.69249G/s 1024 KiB
BM_FilteringWithBranching/80        391869 ns       391837 ns         1766 bytes_per_second=2.49226G/s 1024 KiB
BM_FilteringWithBranching/90        242491 ns       242487 ns         2848 bytes_per_second=4.02727G/s 1024 KiB
BM_FilteringWithBranching/100       164824 ns       164808 ns         4265 bytes_per_second=5.92547G/s 1024 KiB
BM_FilteringWithNoBranching/0       120439 ns       120430 ns         5836 bytes_per_second=8.10898G/s 1024 KiB
BM_FilteringWithNoBranching/10      118230 ns       118219 ns         5851 bytes_per_second=8.26064G/s 1024 KiB
BM_FilteringWithNoBranching/20      118364 ns       118355 ns         5821 bytes_per_second=8.25111G/s 1024 KiB
BM_FilteringWithNoBranching/30      118973 ns       118968 ns         5846 bytes_per_second=8.2086G/s 1024 KiB
BM_FilteringWithNoBranching/40      118820 ns       118821 ns         5874 bytes_per_second=8.21879G/s 1024 KiB
BM_FilteringWithNoBranching/50      119887 ns       119887 ns         5792 bytes_per_second=8.14569G/s 1024 KiB
BM_FilteringWithNoBranching/60      120065 ns       120060 ns         5830 bytes_per_second=8.13397G/s 1024 KiB
BM_FilteringWithNoBranching/70      122337 ns       122309 ns         5826 bytes_per_second=7.98436G/s 1024 KiB
BM_FilteringWithNoBranching/80      122065 ns       122060 ns         5737 bytes_per_second=8.00067G/s 1024 KiB
BM_FilteringWithNoBranching/90      121988 ns       121986 ns         5730 bytes_per_second=8.00552G/s 1024 KiB
BM_FilteringWithNoBranching/100     124575 ns       124567 ns         5624 bytes_per_second=7.83967G/s 1024 KiB
```

## caching

```s
$ bazel run benchmark:caching -c opt
Run on (8 X 2400 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x8)
  L1 Instruction 128 KiB (x8)
  L2 Unified 4096 KiB (x8)
Load Average: 1.80, 1.46, 1.48
---------------------------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations UserCounters...
---------------------------------------------------------------------------------------
BM_RandomAccess/1024               90.1 ns         90.1 ns      7773200 bytes_per_second=10.5827G/s 1 KiB
BM_RandomAccess/2048                179 ns          178 ns      4049426 bytes_per_second=10.7365G/s 2 KiB
BM_RandomAccess/4096                341 ns          340 ns      2047933 bytes_per_second=11.2207G/s 4 KiB
BM_RandomAccess/8192                674 ns          672 ns      1034493 bytes_per_second=11.3488G/s 8 KiB
BM_RandomAccess/16384              1354 ns         1353 ns       520485 bytes_per_second=11.276G/s 16 KiB
BM_RandomAccess/32768              2785 ns         2783 ns       251689 bytes_per_second=10.9652G/s 32 KiB
BM_RandomAccess/65536              5584 ns         5583 ns       122796 bytes_per_second=10.9318G/s 64 KiB
BM_RandomAccess/131072            11648 ns        11646 ns        59483 bytes_per_second=10.4816G/s 128 KiB
BM_RandomAccess/262144            30686 ns        30633 ns        22840 bytes_per_second=7.96984G/s 256 KiB
BM_RandomAccess/524288            73494 ns        73488 ns         9472 bytes_per_second=6.64432G/s 512 KiB
BM_RandomAccess/1048576          165636 ns       165623 ns         4261 bytes_per_second=5.8963G/s 1024 KiB
BM_RandomAccess/2097152          378869 ns       378869 ns         1839 bytes_per_second=5.15514G/s 2048 KiB
BM_RandomAccess/4194304          831805 ns       826804 ns          872 bytes_per_second=4.72452G/s 4096 KiB
BM_RandomAccess/8388608         1838844 ns      1838545 ns          365 bytes_per_second=4.24928G/s 8192 KiB
BM_RandomAccess/16777216        6839258 ns      6839257 ns          101 bytes_per_second=2.2846G/s 16384 KiB
BM_RandomAccess/33554432       24591940 ns     24590960 ns           25 bytes_per_second=1.27079G/s 32768 KiB
BM_RandomAccess/67108864       60774657 ns     60772556 ns            9 bytes_per_second=1053.11M/s 65536 KiB
BM_SequentialAccess/1024           89.7 ns         89.7 ns      7825076 bytes_per_second=10.6359G/s 1 KiB
BM_SequentialAccess/2048            173 ns          172 ns      4057924 bytes_per_second=11.0818G/s 2 KiB
BM_SequentialAccess/4096            333 ns          333 ns      2097322 bytes_per_second=11.4716G/s 4 KiB
BM_SequentialAccess/8192            656 ns          656 ns      1068719 bytes_per_second=11.6347G/s 8 KiB
BM_SequentialAccess/16384          1316 ns         1315 ns       537795 bytes_per_second=11.6024G/s 16 KiB
BM_SequentialAccess/32768          2751 ns         2668 ns       258723 bytes_per_second=11.4393G/s 32 KiB
BM_SequentialAccess/65536          5494 ns         5490 ns       127028 bytes_per_second=11.1174G/s 64 KiB
BM_SequentialAccess/131072        11142 ns        11140 ns        62138 bytes_per_second=10.9581G/s 128 KiB
BM_SequentialAccess/262144        23802 ns        23071 ns        31322 bytes_per_second=10.5823G/s 256 KiB
BM_SequentialAccess/524288        46401 ns        46393 ns        15047 bytes_per_second=10.5249G/s 512 KiB
BM_SequentialAccess/1048576       93511 ns        93511 ns         7540 bytes_per_second=10.4433G/s 1024 KiB
BM_SequentialAccess/2097152      188496 ns       188496 ns         3723 bytes_per_second=10.3616G/s 2048 KiB
BM_SequentialAccess/4194304      391242 ns       391243 ns         1851 bytes_per_second=9.98422G/s 4096 KiB
BM_SequentialAccess/8388608      782269 ns       782270 ns          900 bytes_per_second=9.98696G/s 8192 KiB
BM_SequentialAccess/16777216    1532112 ns      1531748 ns          457 bytes_per_second=10.2008G/s 16384 KiB
BM_SequentialAccess/33554432    3087197 ns      3081787 ns          235 bytes_per_second=10.1402G/s 32768 KiB
BM_SequentialAccess/67108864    6172644 ns      6162684 ns          114 bytes_per_second=10.1417G/s 65536 KiB
```

## mutual_exclusion

```s
$ bazel run benchmark:mutual_exclusion -c opt
Run on (8 X 2400 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x8)
  L1 Instruction 128 KiB (x8)
  L2 Unified 4096 KiB (x8)
Load Average: 1.41, 1.43, 1.46
--------------------------------------------------------------------------------------------------
Benchmark                                        Time             CPU   Iterations UserCounters...
--------------------------------------------------------------------------------------------------
BM_InitVectorWithStdMutex/1024                4429 ns         4420 ns       162333 bytes_per_second=220.939M/s 1 KiB
BM_InitVectorWithStdMutex/4096               14576 ns        14575 ns        47331 bytes_per_second=268.013M/s 4 KiB
BM_InitVectorWithStdMutex/32768             111337 ns       111239 ns         6415 bytes_per_second=280.928M/s 32 KiB
BM_InitVectorWithStdMutex/262144            880231 ns       878716 ns          798 bytes_per_second=284.506M/s 256 KiB
BM_InitVectorWithStdMutex/2097152          7000718 ns      6995485 ns          101 bytes_per_second=285.899M/s 2048 KiB
BM_InitVectorWithStdMutex/16777216        56104503 ns     56035417 ns           12 bytes_per_second=285.534M/s 16384 KiB
BM_InitVectorWithStdMutex/67108864       223320361 ns    223274667 ns            3 bytes_per_second=286.642M/s 65536 KiB
BM_InitVectorWithAbslMutex/1024               4252 ns         4253 ns       161592 bytes_per_second=229.618M/s 1 KiB
BM_InitVectorWithAbslMutex/4096              14507 ns        14500 ns        48635 bytes_per_second=269.392M/s 4 KiB
BM_InitVectorWithAbslMutex/32768            109362 ns       109363 ns         6349 bytes_per_second=285.746M/s 32 KiB
BM_InitVectorWithAbslMutex/262144           880448 ns       880388 ns          802 bytes_per_second=283.966M/s 256 KiB
BM_InitVectorWithAbslMutex/2097152         7160598 ns      7118545 ns           99 bytes_per_second=280.956M/s 2048 KiB
BM_InitVectorWithAbslMutex/16777216       55966024 ns     55953083 ns           12 bytes_per_second=285.954M/s 16384 KiB
BM_InitVectorWithAbslMutex/67108864      224049624 ns    223853333 ns            3 bytes_per_second=285.901M/s 65536 KiB
BM_InitVectorWithCompareAndSet/1024           1447 ns         1447 ns       484657 bytes_per_second=674.817M/s 1 KiB
BM_InitVectorWithCompareAndSet/4096           3134 ns         3142 ns       223521 bytes_per_second=1.21393G/s 4 KiB
BM_InitVectorWithCompareAndSet/32768         18946 ns        18949 ns        36964 bytes_per_second=1.61049G/s 32 KiB
BM_InitVectorWithCompareAndSet/262144       145194 ns       145178 ns         4822 bytes_per_second=1.68167G/s 256 KiB
BM_InitVectorWithCompareAndSet/2097152     1175630 ns      1174617 ns          595 bytes_per_second=1.66278G/s 2048 KiB
BM_InitVectorWithCompareAndSet/16777216    9409445 ns      9402520 ns           75 bytes_per_second=1.66179G/s 16384 KiB
BM_InitVectorWithCompareAndSet/67108864   37177697 ns     37163632 ns           19 bytes_per_second=1.68175G/s 65536 KiB
```
