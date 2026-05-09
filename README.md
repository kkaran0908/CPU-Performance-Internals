### Cache Hierarchy:

If CPU had to access RAM for every operation, it would spend most of its time simply waiting for data to arrive, wasting a huge number of CPU cycles. To reduce this waiting time, modern CPUs use small but extremely fast memories called caches (L1/L2/L3). Frequently accessed data is stored inside these caches so the CPU can access it much faster.

Approximate access latency of different memory hierarchies:
CPU Register ~ 0.3 ns
L1 Cache ~ 1 ns
L2 Cache ~ 4 ns
L3 Cache ~ 10–20 ns
RAM ~ 60–100+ ns

But there’s a limitation, caches are very small compared to RAM, so they cannot hold all the data. As the working data size increases and stops fitting inside the caches, the CPU is forced to fetch data from slower levels of memory, eventually reaching RAM.
