


1. What level of SIMD/vector support does the CPU your computer provide?

'AVX', 'SSE3', 'SSSE3', 'SSE41', 'SSE42' are supported by the CPU of my computer. 

2. What is the maximum operand size that your computer will support?

The maximum operand size the my computer will support is 256 bit operand. 

3. How many double-precision floating point numbers can fit into one operand given the maximum operand size that your CPU will support?

Since each double-precision floating point number takes 64 bits, we can fit 4 double-precision floating point numbers into one operand given the maximum operand size (256 bits). 

4.What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").

The clock speed of my CPU is 2.5 GHz. 

5. Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)

We see that the column bytes/sec sees a fall between 32K and 64K bytes and this is the first such fall in the values of this column. Therefore, we can expect L1 cache to be 32k bytes. The second drop in values occur between 512K bytes and 1024K bytes and so we can expect L2 cache to be about 512K bytes. The L1 bandwidth should be about 77GB/s and the L2 bandwidth is possibly about 40GB/s. The cache sizes are extremely small compared to the total memory of the CPU. The L1 cache corresponds to about 0.0004% of total memory and L2 cache is also a small portion of total memory. 

6. What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?

The potential maximum compute performance of the computer is 12.3 Gflops/sec. The L1 bandwidth is about 51 GB/s and L2 bandwidth is about 41.3 GB/s. The DRAM bandwidth is about 20GB/s.  These bandwidths are more or less the same specially for the L2 cache. However, the L1 cache bandwidth is lower. 

7. Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?  

The maximum Glop rate is 12.3 Gflops/sec. Then, 12.3 Gflops/sec / 2.5 GHz = 4.92 flops/cycle. We have SSE and AVX and so SSE contributes a factor of two and AVX contributes a factor of four. So we get a factor of eight to get (4.92*8) = 39.36 flops/cycle. This is the expected maximum number of floating point operations our CPU could perform per cycle. The answer would change for single precision. The answer should be four times as the assumptions above would change. We could assume that AVX would contribute twice a factor of four for single precision and SSE would contribute twice a factor of two for single precision. Therefore, this would lead to a factor of four increase from double precision. 

8. What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?

9. Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

THe best performing ones are the ones looping over j at the inner loop. If we focus on looping over j, we see that components of A are not depending on it. We only have C and B depending on it and looping over j means that we are moving through the columns for row i of C and row k of B. This is how the elements are stored in memory, that is, elements in each row are stored next to each other. Therefore, for given row k we are just moving over the elements of row k when we loop over j. Since, these are stored in memory in that order getting access to them is quicker cause they are stored next to one another. This explains the quick performance as the memory acces is advantageous. 

10. What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?

If we look at step (i,j,k) and the inner loop which loops over k we can notice that only components of A and B depend on it. We are accessing the ij-th element of C, ik-th element of A and jk-th element of B. At the (i,j, k+1) we are accessing i(k+1)th element of A and j(k+1)th element of B. The element of C being accessed does not change. This means that we are accessing the same rows (i and j) for A and B but the entry in the following column. This means that we are accessing elements of the row and this is how they are stored in memory meaning that accessing them is quicker. Therefore, these accesses are advantageous because we are looping over elements in a particular row instead of a column where we would have to move around in memory. 

11. Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

When we hoist C(i,j) up it means that in the inner loop we are not accessing this as this does not depend on k. But because of the ijk ordering, in the inner loop we are accessing elements of a particular row for A and B hence making it advantageous. But, also since the ordering is ijk we are going to be accessing elements of C in the form of (i, j+1) which is again elements of the row i. This makes data accessing easier for elements of C because they are stored in the order we are trying to access them. Since, this works the same for A and B too it is extremely beneficial. 

12. What optimization is applied in going from ``mult_2`` to ``mult_3``?

Even with hoisting and tiling, we will encounter an issue with large problem sizes. These problems will not fit into the cache regardless of other optimizations. Therefore, 'mult_3' breaks the problem down into smaller chunks that can be stored into cache and thereby improving locality for the whole problem by achieving locality for each of the blocks. We should expect 'mult_3' to perform better than 'mult_2' for substantially large problems. 

13. How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?

The maximum achieved performane for 'mult' (any version) is lower compared to what bandwidth and roofline predicted. This is even without taking into account the features supported by the CPU. The closest one was mult_transpose_2 for problem size 256 which achieved 11.4Gflops/sec compared to 12.3Gflops/sec. 


