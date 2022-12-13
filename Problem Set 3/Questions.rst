
PS3 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer.

argv
----

1. What does `argv[0]` always contain?

'argv[0]' always contains the path to the executable file, that is, the command we run int the shell to execute the program. If we provide the relative path, it will contain the relative path that is, './repeat.exe'. If we provide the absolute path then it will contain the absolute path. 

2. Which entry of `argv` holds the first argument passed to the program?

The second entry of 'argv' holds the first argument passed to the program, that is, 'argv[1]' contains the first argument passed. 

3. Which entry of `argv` holds the second argument passed to the program?

The third entry of 'argv' holds the second argument passed to the program, that is, 'argv[2]'.

4. How would you print just the last argument passed to a program?

We would get rid of the loop and just print the 'argv[argc-1]' element. This is because there are 'argc' arguments being passed and since there is zero indexing we just print 'argc -1' to get the final argument. The number 'argc' also takes into account the path to the executable and so 'argc-1' would still work because the path to the executable is always the first element of 'argv'. If we do not want to print 'argv[argc-1]:"argument"' and just want to print "argument" we can remove that in our code. However, we have kept it for this assigment. 

float vs double
----------------

5.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with no optimization*? Explain.

The ratio in execution times between double and single precision for construction with no optimization is 1.11, that is, it takes 1.11 times longer to construct double precision. I computed the ratio several times with different program sizes and the number was approximately the same. One of the reasons could be due to the hierarchical memory set up. The single float has 32 bits whereas double precision has 64 bits. It is possible that while the computer fetches double precision numbers from memory it cannot find it in L1 cache because of its size and has to go to L2 cache and so on. It is also possible, that double precision is not on one line in the L1 cache so there would still be an added time to construct double precision. On the other hand, floating point requries fewer bits so it is possible that it is in the L1 cache and so the CPU does not have to look farther and construction is faster. 

6.  What is the difference (ratio) in execution times
between single and double precision for    *multiplication with no optimization*? Explain.

The ratio in execution times for double over single precision for multiplication with no optimization is about 1.08-1.1. This is similar to the ratio we found above and the same reasoning could be applied. 

7.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with optimization*? Explain.

The ratio in execution times for double over single precision for construction with optimization is about 2. This means that it took twice as long to construct double precision arrays than single precision arrays. This goes hand in hand with the fact that double precision requires 2 times the number of bits for single precision. It is possible that single precisions are being optimized more than double. Due to smaller size, it is easier to improve locality of single precision than for doubles. So, the execution time for single precision is improved by a greater factor compared to the execution time of doubles.  

8.  What is the difference (ratio) in execution times 
between single and double precision for    *multiplication with optimization*? Explain. 

The ratio in execution times for double over single precision for multiplication with optimization is also about 2. Again, this goes hand in hand with the number of bits for double precision vs number of bits for single precision. A similar argument holds for this case too as single precision multiplication might be getting optimized more. 

9.  What is the difference (ratio) in execution times 
for double precision   multiplication with and without optimization? Explain. 

If takes about four times longer to execute double precision multiplication with optimization compared to multiplication without optimization. This can also be seen in the flops/cycle we are computing in the program as it is four times higher in the case of optimization. This makes sense as optimization allows for better locality and so less time is taken trying to load from memory. Floating point operations/Total operations ratio has improved by a factor of 4. Hence, we get a quicker time. The flops per cycle are also four times higher and I am wondering whether the loops is being done at all. This is because the computations in the loop are never used in the program so the optimization might just get rid of the loop. 

Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?

Number of operations = N^3 and so if we double the problem size we get (2N^3) = 8N^3 operations. So, it will perform 8 times the operation. 

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?

It should take aobut 8 times more time. However, it should be more because of the time to laod the entries and larger entries mean that more trips to memory as their will be more entries in each row. 

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.

The ratio was about 15-16 times greater when we doubled the problem size. I was referring to this in the previous problem. As we increase the problem size, there are more entries per row. That means that L1 cache cannot hold all the entries at one time required for a particular row operation. Therefore, there are more trips to load the data as L2 cache and so on searched after. The ratio is twice as great as predicted by pure operation count and this might be becuase twice as many trips are required to load the data.  

13.  What raio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?

The ratio is pretty close to 8 which is the ratio predicted by pure operation count. This was not the same for 'mult_0'. The function hoists, tiles and does blocking which benefits the performance. Hoisting involves recognizing that within the final loop C_{ij} is not rqeuired and so we could take it out of the inner loop. Therefore, within that loop it does not need to be loaded again. Tiling recognizes that we use each row of A and each column of B twice. So, we can keep these close that is in the L1 cache to improve locality by reusing two rows and two columns of A and B respectively. 

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.

'mult_1' actually does worse in the beginning as we move from 128 to 256. We get a ratio of about 20. In fact, we saw this for 'mult_1'  as well, that is, the jump from 128 to 256 was the most costly. This maybe due to the size of L1 cache in my computer and increasing the size required it to look in L2. However, increasing size more for 'mult_1' brings the ratio to 11 for 256 to 512. However, the ratio goes back up for 512 to 1024 and again this might be due to the size of L2 cache and the computer has to move farther to search. 
'mult_2': from 128 to 256 the ratio is about 14. From 256 to 512 is still 14. From 512 to 1024 is about 15. So we get slightly better results for some increases. 


All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?

Clearly, hoisiting, tiling and blocking gives the best performance. The algorithms that involves all three do the best regardless of what is passed in. The algorthims involving hoisting and tiling also do well.  It does not seem like there is a huge difference between making a transpose, copying or just passing in A. If we look at the best performing algorithm the one that involves hoisting, tiling and blocking we pretty much get the same numbers. There does not seem to be a huge difference between passing it in twice or passing it in once as the numbers are pretty much the same. In fact, passing it in twice outperformed by a small marging for most matrix sizes. 

16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?

'm_t_3(A,A)' performs the best for the case of 1024 images. The operation count is (Number of images)^2*(Dimension of image)^2. So, if we have 10 times as many images the execution time would be 10^2 =100 times more. Similarly, for 60 times as many images we would have (60)^2 = 3600 times the execution time. If we double the dimension of the image we would have (2)^2 = 4 times the execution time. 

About PS3
---------


17. The most important thing I learned from this assignment was ...

How the way we write code and affect performance. Even though the time is in milliseconds and it might not seem much to us, we saw what the factor of increase is and how it could matter with extremely large real world problems. 


18. One thing I am still not clear on is ...

Flops/cycle and how to calculate it and how it relates to clock rate. Most importantly, what is peak performance. 