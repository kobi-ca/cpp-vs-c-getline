# cpp-vs-c-getline
Investigating https://towardsdatascience.com/when-speed-matters-use-c-f040d9381680

Using https://www.stats.govt.nz/large-datasets/csv-files-for-download/

Geographic units, by industry and statistical area: 2000 – 2020 descending order – CSV

For sync with io
===================
https://gcc.gnu.org/bugzilla/show_bug.cgi?id=45574#c0

But it did not work

For perf
===============
1486  sudo apt install -y linux-tools  
1487  sudo apt install -y linux-tools-generic  
1488  perf probe -x /lib64/libc.so.6 'malloc allocated=%di:u64'  
1489  sudo apt install -y linux-tools-5.8.0-44-generic  
1490  sudo apt install -y linux-cloud-tools-generic linux-tools-generic  
1491  perf probe -x /lib64/libc.so.6 'malloc allocated=%di:u64'  
1492  perf probe --exec=/lib64/libc-2.17.so --add malloc  
1493  ldd ./cpp-vs-c-getline  
1494  perf probe --exec=/lib/x86_64-linux-gnu/libc.so.6 --add malloc  
1495  sudo perf probe --exec=/lib/x86_64-linux-gnu/libc.so.6 --add malloc  
1496  perf record -e probe_libc:malloc -aR ./cpp-vs-c-getline ./Data7602DescendingYearOrder.csv > ./out  2>&1  
1500  sudo mount -o remount,mode=755 /sys/kernel/tracing/  
1504  echo -1 | sudo tee -a /proc/sys/kernel/perf_event_paranoid  
1511  perf report -n  
1521  ls -l  /proc/kallsyms  
1522  cat /proc/kallsyms | head  
1523  ls -l  /proc/kallsyms  
1524  perf report -n  
1525  cat /proc/sys/kernel/kptr_restrict  
1526  echo 0 | tee -a /proc/sys/kernel/kptr_restrict  
1527  echo 0 | sudo tee -a /proc/sys/kernel/kptr_restrict  
1528  cat /proc/sys/kernel/kptr_restrict  

https://stackoverflow.com/questions/21284906/perf-couldnt-record-kernel-reference-relocation-symbol

https://askubuntu.com/questions/1171494/how-to-get-perf-fully-working-with-all-features

http://www.brendangregg.com/perf.html

https://stackoverflow.com/questions/50489287/how-to-print-malloc-size-function-with-perf-probe

https://developers.redhat.com/blog/2019/04/23/how-to-use-the-linux-perf-tool-to-count-software-events/


# Using uftrace with apt install
➜  fgets git:(main) ✗ uftrace report | head
  Total time   Self time       Calls  Function
  ==========  ==========  ==========  ====================
  647.449 ms    1.174 us           1  main
  647.421 ms  332.737 ms           1  _GLOBAL__N_1::test_load_file_c
  310.358 ms  303.685 ms     5429254  fgets
   10.700 ms   10.700 ms         109  linux:schedule
  252.784 us   22.865 us         164  std::operator<<
  221.048 us  221.048 us         164  std::__ostream_insert
   48.015 us    0.231 us           1  _GLOBAL__sub_I_main
   47.784 us    1.007 us           1  __static_initialization_and_destruction_0
➜  fgets git:(main) ✗ cd ../getline 
➜  getline git:(main) ✗ uftrace report | head
  Total time   Self time       Calls  Function
  ==========  ==========  ==========  ====================
    3.188  s    1.020 us           1  main
    3.188  s  349.174 ms           1  _GLOBAL__N_1::test_load_file_cpp_original
    2.049  s  916.580 ms    10858508  std::getline
    1.106  s  279.089 ms     5429254  std::basic_ios::operator(cast)
  827.688 ms  620.005 ms     5429254  std::basic_ios::fail
  815.107 ms  606.584 ms     5429254  std::basic_ios::widen
  105.145 ms  105.136 ms     5429254  std::ctype::widen
  104.454 ms  104.448 ms     5429254  std::basic_ios::rdstate

