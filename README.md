This repository contains experimental code in preparation for some of the topics are a part of the ECE2010 Intro to ECE course at WPI.

# Using C in MATLAB: A Tutorial on using MEX Files
MATLAB is very convenient to test ideas as it makes a lot of the menial tasks in writing software very simple to do by providing outstanding support for a lot of different domains. What is being traded off for convienece is the pure performace of the code that you write, from say, languages like C or C++, which are much more difficult to work with than MATLAB but much faster. 

However, MATLAB is still highly efficient for any kind of matrix operations. All the built-in functions that are in use like A .* B, or A \ B run on efficiently written code in the background which utilises a concept call *vectorisation*. What it means in simple terms is that any operation where vectors are involved, it runs very quick in MATLAB. However, if you have a large proejct that has a lot of for loops running, your performance will be quite slow, because you have lines which are being executed sequentially, and there is no way to vectorise what you want to achieve.

In situations like these, compiled languages such as C and C++ are quite fast and can outperform MATLAB scripts significantly. To help with this, MATLAB actually allows you to run C code directly inside MATLAB. So let's say you have a particular task that has a lot of for loops and is turning out to be a bottleneck in the performance of your code, you can write the same functions in C, and have it run directly from your inside your MATLAB scripts.

This is done by creating whats called a MEX file. A MEX file is a compiled version of a C source code which is specially compiled such that it can be called directly from inside MATLAB, as a typical MATALB function.

This tutorial is an introduction to how you can create your own MEX files.

### Create a vector multiplication function.
1. By now, you should be familiar with the `.*` operation which can do elementwise multiplication between two vectors.
2. We will start by creating our own MATLAB function which can do the same thing. Let's call it `multiply_matlab`. To help you with this, look at the starter code `multiply_matlab.m` which defines such a function. 
    1. The function takes in 3 arguments, vector A, vector B and length of the vector.
    2. The output is a vector that contains the multiplication of the corresponding elements of the input vectors.
3. However, you will notice it doesn't really do anything right now. Add you own implementation of the multiplication without changing the input arguments or the output format.

### Using your own function in a different script.
1. Once you are done, open the `multiplication_example.m` file and see what's going on there. There are comments to help you out.
2. Run this file to see if everything works correctly. Note the execution time.

### Using a C source code to create a MEX file
1. Now time to move on to the fun part. Notice that you are also provided a `multiply_mex.c` file which is a C source file which implements the same function of multiplying two vectors.
2. To compile this source code as a MEX, type the following command in your command window.
```
mex multiply_mex.c
```
3. You will notice that this generates a new file of the same name but with a different extension. Sweet! You created your first MEX file.
4. Now you can open the `multiply_mex.c` file using any text editor(Sublime Text, Atom, etc.) to see how the source code actually looks. If you are familiar with C, the comments can help you understand whats going on in there. If not, you don't have to worry about it right now.

### Using the MEX function in your script.
1. Again, open your `multiplication_example.m` file and change the line where you are calling your `multiply_matlab` function and change that to callling the `multiply_mex` function instead.
2. Your final line should look something like
```
C = multiply_mex(A, B, N);
```
3. Notice that you literally didn't have to change anything else in your MATLAB script. Try to run the `multiplication_example.m` file again. Notice the change in execution time! 

### Conclusion
In this example, you learnt 
- [x] What a MEX file is, and what are the advantages in using it.
- [x] Creating your own MEX file using a C source code.
- [x] Using the MEX file function in your script.

### Assignment


### References
1. [Chalmers](http://www.math.chalmers.se/Stat/Grundutb/CTH/tms150/1112/howto_mex.pdf)
2. [University of Cambridge](http://www-h.eng.cam.ac.uk/help/tpl/programs/Matlab/mex.html)
