This repository contains experimental code in preparation for some of the topics are a part of the ECE2010 Intro to ECE course at WPI.

# Using C in MATLAB: A Tutorial on using MEX Files
MATLAB is very convenient to test ideas as it is makes a lot of the menial tasks in writing code very simple to do by providing outstanding support for a lot of different domains. What is being traded off for convienece is the pure performace of the code that you write, from say, languages like C or C++, which are much more difficult to work with than MATLAB but much faster. However, MATLAB is still highly efficient for any kind of matrix operations. All the built-in functions that are in use like A .* B, or A \ B run on efficiently written code in the background which utilises a concept call *vectorisation*. What it means that any operation where vectors are involved, it runs very quick in MATLAB. So if you have a logic that you want to implement in MATLAB and you can think about it in forms of any kind of vector operation, you can gain huge performance. However, if you have a complicated code that has a lot of for loops running, your performance will be quite slow, because you have line which are being executed sequentially, and there is no way to vectorise what you want to achieve.
In situations like these, compiled languages such as C and C++ are quite fast and can turn out to outperform MATLAB scripts quite significantly. To help with this, MATLAB actually allows you to run C code directly inside MATLAB. So let's say you have a particular task that has a lot of for loops and is turning out to be a bottleneck in the performance of your code, you can write the same functions in C, and have it run directly from your MATLAB scripts. 
You can do this my creating whats called a MEX file. A MEX file is a compiled version of you C source code which is specially compiled such that it can be called directly from inside MATLAB, as a simple function. In order to successfully compile your source code as a MEX file, you have to take special care in your C code to address the variables in a way that is expected by MATLAB.
This tutorial is an introduction to how you can create your own MEX files.

### MATLAB and C Performance difference
1. `for_looop_example.m` shows a simple for loop which increments a variable's value for a total of 1000 x 16000000 times.
2. For one set of calculations, we calculate the time it took for our computer to execute it as one of the elements in the vector `time`.
3. We repeat this experiment 10 times and calculate the average execution times over the repititions. Note the execution time.
4. Now we have the same operations, but this time written in C in the file `for_loop.c`
5. Compile this on your computer using the following command ` gcc -O for_loop.c -o for_loop`. Run this file using `./for_loop` and see the execution time. 

### Using the C code to create a MEX file
1. You can't directly use any C source code in MATLAB. There are a few things that you have to change to make you C source code compatible with what MATLAB expects.
2. Look at the `for_loop_mex.c` file to see what the compatible version of the previous C code looks like. Look for things that have changed, and what has remained the same.
3. The `int main()` function is replaced with a `void mexFunction()` function which has 4 parameters. These parameters handle the exchange of variable between MATLAB and C. The specifics are explained below:
    1. `nlhs`: Number of terms on the left hand side of the command in MATLAB.
    2. `plhs` : All the left hand side variables.
    3. `nrhs` : Number of terms on the right hand side.
    4. `prhs` : All the variable on the right hand side of the equation.
4. You use the left hand side mxArray to output what you computes and the right hand side mxArray to get the MATLAB variable that you want to receive has arguments for the function.
5. For this example, there are no inputs, so we will just leave that for now.
6. Now we want to return the mean time that we calculated. We do this by using the `mxCreateDoubleScalar()` function from the `mex.h` library that was imported earlier.
7. Look at line 32. We are assigning the first variable on the left hand side(`plhs[0]`) the value of `mean_sec`.
8. That's it. This is enough for us to compile this as  MEX file.
9. Compile this source code using the following command `mex for_loop_mex.c`. You should now see something similar to for_loop_mex.mexa64 (the extension depends on your operating system).
10. You now have your first MEX file ready. Open your MATLAB window and write `mean_time = for_loop_mex()` in the command window. Check your execution time now.

### Handling Input and Output arguments correctly
1. Let's move on to a more involved function where were are replicating the elementwise multiplication for two vectors. What is interesting here is that we will be giving 'MATLAB variables' as arguments to the function, converting them into 'C variables', and then converting the results in 'C variables' to 'MATLAB variables' again.
2. Open the `multiplication_example.m` and see whats going there. We are defining two really long vectors, and multiplying them in three different ways.
    1. Using the in built operator `.*` which makes use the vectorisation approach we talked about earlier.
    2. Defining a MATLAB function doing the same thing, using only for loops.
    3. Writing C source code for and making use of a MEX function. 
2. Take a look at the `multiply_matlab.m` function to see how you can do this using for loops in MATLAB.
3. Now take a look at the`multiply_c.c` file to see what a C code doing the same thing might look like.
4. Open the `multiply_mex.c` side by side to see the differences that these two codes have.
5. As you could probably guess, we again replace the `main()` routine by the `mexFunction()` function. Try to recall what the 4 arguments here are.
6. To assign the first input vector from the MATLAB arguments, we take the first value in the right hand side array(`prhs`) and use the `mxGetPr()` function to properly 'convert' the MATLAB variable into a C array, `vector_1`. We repeat this for the second array.
7. Now returning the `output` array after multiplication is not really straightforward.
8. Since `plhs` directly supplies whatever is assigned to it to MATLAB, we can't really define  `plhs[0]` as a C array. We have to use `mex.h` functions to create an array that is understood by MATLAB. We do this by creating a 1 x N matrix using the `mxCreateDoubleMatrix(1, N, mxREAL)` function.
9. Now the problem is that what we have an `output` array which is an array of doubles as C knows it, but we can't assign that directly using `plhs[0] = output` because the variables on the either side are different data types.
10. This issue is addressed by using the `memcpy` function from the `string.h` library which __copies__ `N*sizeof(double)` amount of values stored in memory, __starting from__ the memory location of the first element of `output` array, to the __first memory location__ of the `plhs[0]` which we get from the `mxGetPr` function.
11. In order to copy the `output` values, we have to temporarily store all of its values in whats called the *heap memory* which we then have to 'release' using the `free(output)` command.
12. Now the source code is ready to be compiled as a MEX file. Again use `mex multiply_mex.c` in your command line to get a mex file.
13. Once you have the MEX file compiled according to your operating system, you can run the `multiplication_example.m` file to see the performance differences between the three different approaches. 

### Checklist
- [x] Write sample code to compare performance of C and MATLAB, prove that MATLAB is in fact slower for for loops. 
- [x] Create MATLAB sample function for elementwise operations. 
- [x] Create C sample function for elementwise operations. 
- [x] Write the details of making a function compatible for use as MEX file. 
- [x] Convert the C sample to a MEX file to be used in MATALB. 


### References
1. [Chalmers](http://www.math.chalmers.se/Stat/Grundutb/CTH/tms150/1112/howto_mex.pdf)
