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
