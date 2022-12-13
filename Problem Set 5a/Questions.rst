

- At what problem size do the answers between the computed norms start to differ?

The absolute error increases from 10^(-15) to 10^(-14) around a problem size of 3000. 
However, for our purposes I wanted to see when it increases more than 10^(-14). The answers 
between the computed norms start to differ around a problem size of
70,000. Until then, the absolute error is to the order of machine precision or close to it but after
this point the absolute error is about 10^(-13).  

- How do the absolute and relative errors change as a function of problem size?

The absolute error increases with problem size whereas the relative error seems to be in the 
same order of magnitue (10^(-16)) regardless of problem size for smaller problems. In 
fact, when I went up to 60000000, I noticed that the relative error increased to the order 
of 10^(15).

- Does the Vector class behave strictly like a member of an abstract vector class?

No, the Vector class does not behave strictly like a member of an abstract vector class. This is because if they did
we would have that the norms of a sorted vector or a vector in reverse would be the same for any vector. This means that it would
remain the same regardless of the problem size. However, we have seen this to be not the case. We do see errors at the order of machine precision for 
smaller problem sizes and we can go upto a problem size of 70000 with an absolute error of 10^(-14). After increasing problem size from there on
the absolute error keeps increasing which means that the norm starts differing more and more. 

- Do you have any concerns about this kind of behavior?

Mostly no. I have some concerns because if we have real life problems 
that require really really large vectors the relative error does increase and we will have numerical error which can accumulate and cause problems in real life 
applications.However, the relative error for quite large problem sizes is at the order of machine precision. This means that we can break up a large vector to 
different components based on the maximum vector size that yields machine precision error and then compute the sum of squares and then bring them back together 
to compute the norm. Parallelization can potentially solve this issue of increasing relative errors with problem sizes after a certain size. 
