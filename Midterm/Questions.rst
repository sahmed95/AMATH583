
To do 6: Does the transpose matrix vector product perform better than the matrix vector product? 

Yes, the transpose matrix vector product seems to be performing better. In particular for COO and AOS the transpose matrix vector 
product performs better but for CSR and CSR the difference in performance does not seem to differ by much. 

How does the performance (in GFLOP/s) for sparse-matrix by vector
product compare to what you previously achieved for dense-matrix by
dense-matrix product?  Explain, and quantify if you can, (e.g., using
the roofline model).

The performance for sparse-matrix by vector product does better than what was previously achieved for dense-matrix by dense-matrix product without any optimization. 
Even though the numbers for the GFlops/s for mult0 in the previous homework are close to the numbers generated here for sparse matrix by vector product we have to take into account the matrix sizes. We start off with a matrix size of 4096 which outperforms the dense matrix by matrix product for a matrix size of 256. 
Using the roofline model, we can see that the dense-matrix by dense matrix product without optimization has 1/12 Flops/Byte which gives us 0.4 GFlops/s if we are loading from DRAM.
We can get better performance if we load from the cache. However, for the spare-matrix by vector product we have approximately 1/14 Flops/Byte giving us 1.2 Gflops/sec if we are loading from DRAM. 
We can see using the roofline model that the sparse-matrix by vector product will achieve better performance than dense-matrix by dense-matrix product. 

How does the performance (in GFLOP/s) for sparse-matrix by vector
product for COO compare to CSR?  Explain, and quantify if you can,
(e.g., using the roofline model).

CSR achieves better performance than COO with regards to spare-matrix by vector product in terms of GFLOP/s. For example, for a matrix size of 4096 COO reports 
0.935 Gflops/s whereas CSR reports 1.19 GFlops/s. This boils down to the difference in Flops/Byte (numerical intensity) using the roofline model. The number of flops within 
a loop does not change and so it boils down to how we are accessing data. Notice that for the CSR storage we have 2 flops in the innermost loop and 
3 doubles and 1 int. If we consider the whole setup, we have 2N*NNZ flops = 10N^2 Flops. For data access, we have N*NNZ 
doubles + 2N^2 doubles = 7N^2 doubles . However, in this case we have only 1 index being accessed so N*NNZ
index . This gives us a numerical intensity of 1/10 Flops/Bytes. This should give a better Gflops/s because
the roofline model has positive slope so a greater numerical intensity gives a greater Gflops/s value. 

How does the performance (in GFLOP/s) for sparse-matrix by dense
matrix product (**SPMM**) compare to sparse-matrix by vector product
(**SPMV**)? The performance for SPMM should be about the same as for
SPMV in the case of a 1 column dense matrix.  What is the trend with
increasing numbers of columns?  Explain, and quantify if you can,
using the roofline model.


The SPMV performs better than SPMM. For CSR and CSC, upto a certain matrix size the difference is really big. This is true 
for C00 too. However, after a certain matrix size they seem to come close together specially for C00. This is true
for AOS too. For CSR and CSC we do still see quite a bit of difference. One thing noticeable is that the performance
in Gflops/s as we increase matrix size does not change much for SPMM. However, it decreases quite a lot for SPMV. 


How does the performance of sparse matrix by dense matrix product (in
GFLOP/s) compare to the results you got dense matrix-matrix product in
previous assignments?  Explain, and quantify if you can, using the
roofline model.

The matrix sizes for sparse matrices were considerably bigger than the ones we had for dense matrix matrix product. That said, the performance of the sparse matrix by dense matrix product seems to perform better than dense matrix-matrix product because 
the performance for 256N in dense matrix matrix is comparable if not worse than the performance for much larger matrices in sparse matrix dense matrix product. 
. The numerical intensity of dense matrix-matrix product is 1/12 Flops/Byte which gives us 0.4GFlops/s using the roofline model if data
is loaded from DRAM. For SPMM (COO), we have 2 flops in the inner loop and overall 2N*NNZ =10N^2 flops. In the inner loop, we have 
3 doubles and 2 indexes. So, overall, we have 2*N*NNZ doubles + N*NNZ double= 15N^2doubles and 2*N*NNZ = 10N^2 indexes. Maybe, the numerical intensity is about 10/(8*25) = 1/20Flops/Byte. 



To do 10: 
a) The most important thing I learned: somehow adding loops can sometimes reduce work which seems counterintuitive to me. Obviously, we have done this before using hoisting, tiling and blocking but in this case for CSR and CSC we are adding a loop which does not seem to do any of those and yet we get better performance. It's all about locality! 
b) One thing I am still not clear about is how to get the numerical intensity. I really struggled with computing it because the notes, specially on sparse matrices, 
were left as an exercise. 

Notes/Comments:

I have optimized the matrix vector product and matrix matrix product for CSR. The code for that part is commented. 
I only completed optimization by hoisiting and I witnessed improved performance in terms of GFlops/s. 
