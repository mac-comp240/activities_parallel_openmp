# Activity 23: OpenMP Basics
## Put your name(s) here

In this activity, you will experiment with OpenMP pragmas and how they implement parallelism using multithreaded computations. Discuss each question with your table and write your answers in this README file.

You will:
- Run, observe, modify, and experiment with small programs that illustrate
shared memory parallel structures
- Run, observe, modify, and experiment with "data decomposition," breaking an array of data into parts and operating in parallel on each part
- Run, observe, modify, and experiment with managing shared and private variables 

OpenMP is built into many compilers, including gcc. It has both library
functions and very special compiler directives called **pragmas**. These are
single lines added to C code to tell the compiler that a block of code should be
transformed into code that executes concurrently, or in parallel.

### Simple examples as patterns

These examples are drawn from work by Macalester professor Libby Shoop and her collaborators. 
They build on examples from the Parallel Computing for Beginners online, interactive
textbook. But here we will experiment on our own server.

## Provided Code

- `Makefile`
    - a makefile to compile all these programs
- `forkJoin.c`
    - a starter program showingn the fork-join pattern, similar to one from our reading
- `spmd.c`
    - a starter program illustrating the SPMD (single-program multiple-data) pattern, also
    similar to one from our reading



- `03.spmd2`
    - a folder for Patternlet 3, containing the `spmd2.c` program and its `Makefile`
- `04.barrier`
    - a folder for Patternlet 4, containing the `barrier.c` program and its `Makefile`
- `05.mainWorker`
    - a folder for Patternlet 5, containing the `mainWorker.c` program and its `Makefile`
    - **Ickiness warning!** This patternlet was created some time ago when accepted
    terminology for this pattern used the term "master" for the main thread. We have
    changed the terminology in this activity, but you will see it when you read the patternlet
- `06.parallelLoop-equalChunks`
    - a folder for Patternlet 6, containing the `parallelLoopEqualChunks.c` program and its `Makefile`
- `07.parallelLoop-chunksOf1`
    - a folder for Patternlet 7, containing the `parallelLoopChunksOf1.c` program and its `Makefile`
- `08.reduction`
    - a folder for Patternlet 8, containing the `reduction.c` program and its `Makefile`
- `11.private`
    - a folder for Patternlet 11, containing the `private.c` program and its `Makefile`




## Tasks

### Task 1: Exploring the fork-join pattern

The fork-join pattern uses an OpenMP pragma to set up a set of threads that all
perform the same block of code. The threads may or may not operate on shared data, here
we will avoid shared data.

* Examine the `forkJoin.c` program, then compile and run it
    - Notice that the code includes curly braces around the middle `printf`: this
    creates a block of code so that when we uncomment the OpenMP pragma we can
    include multiple lines of code if we want
* Notice that only one copy of "During" is printed
* Uncomment the `#pragma omp parallel` line, which tells OpenMP to create a 
default number of threads, and ask each one to run the line that follows
* Count how many threads are created by default (Record your answer here in this README)
* Modify the `forkJoin.c` program to add to the `printf` line that is performed 
in parallel. 
    - Add a call to `omp_get_thread_num`, which will return an `int`, 
    the unique number assigned to the current thread. Print that number.
    - Either add the call to the `printf` or assign a variable to hold it ** inside
    the pragma's code block**
* Compile and run the program, and use it to check that your thread count was correct
* Run the program multiple times: what happens to the order in which threads print? 
* Modify the program by adding to the pragma line `num_threads(5)`. This will 
allocate the given number of threads, rather than the default
* Compile and run the program and note how it differs
* Change the `printf` after the parallel section to say "After first parallel block..."
* After that, call `omp_set_num_threads` and set the number of threads to 8
* Copy the pragma and its code block and paste the copy below the call to `omp_set_num_threads`
* Add a final print statement to print "The end..."
* Compile and run the program. Notice how the serial and parallel sections of 
the code alternate with each other


### Task 2: Exploring the SPMD pattern

SPMD stands for "single-program multiple-data." This pattern builds on the 
fork-join pattern, but focuses on threads that all run the same program 
("single-program"), do the same operations, but each operates on its own data 
("multiple data").

* Examine the code in `spmd.c`. 
    - Look closely at the block of code after the parallel pragma
    - Notice that two variables are declared local to the parallel
    block: these variables are private to an individual thread, so their
    values don't interfere with each other
* Compile and run the code, with and without the pragma enabled
* Modify the code to add a shared variable:
    - Declare an `int` variable `shared_var` at the start of `main`. Because 
    this variable is declared in the parent thread, it will automatically be 
    shared by all the threads
    - Inside the parallel block, add a line to define `shared_var` to be `id`
    - Add to the print statement to print out the value of `shared_var`
    - Run the code to see if the values of `id` and `shared_var` are the same
    - Try adding a separate print statement after the first one to print `shared_var`
- When you run the program: what happens? Discuss with your teammates what you see, and
report your observations and why you think it happened here.

### Patternlet 3

This patternlet just illustrates how to use command-line arguments to a C program
to give user-defined inputs to the program. In this case the user can specify the
number of threads in the command line.

- Examine the code, and make sure you understand how the command-line arguments work
- Compile and run the program, running it multiple times with multiple values for the number of threads
- Look for a time when the thread numbers appear wrong: this is a race condition!
- Why does this happen (discuss with teammates)? 
- Fix the problem!

### Patternlet 4

This patternlet shows how to implement a "barrier," a point in the code that all
threads must reach before any move on to the next statement. Each thread reaches that
point and then blocks if there are threads that have not reached it yet. Once all threads
reach the barrier point, then they all can move on to the next step.

- Examine the code, and run it several times without the barrier pragma. Watch for
"before" and "after" print statements to interleave with each other
- Uncomment the barrier pragma, and run the code again
- Observe what happens

### Patternlet 5

**Warning again:** The CS in Parallel text refers to the pattern here as "Master-Worker,"
which was the typical terms used until recently. We are now moving away from the term
master, so this pattern will be called here "Main-Worker", as in "main thread" and 
"worker threads". 

- Examine the code and predict what will print if you run it without the parallel pragma activated
- Run it to check the results
- Then uncomment the pragma and run it again

### Patternlet 6

This patternlet introduces the pragma for parallelizing iterations of a for loop. In this case,
each thread is assigned one "chunk" of iterations of the for loop, and performs them sequentially.

Data decomposition refers to the process of deciding, as a programmer, how to break up the
data across different threads to most effectively and efficiently solve the problem at hand.

The `parallelLoopEqualChunks.c` program uses the "default" data decomposition.

- Read through the program, then compile and run it
- What is the pattern for the default behavior: which loop iterations are assigned to which threads?
Record your observations here.
- The loop repeats 16 times. Try various numbers of threads, including some that divide 
16 evenly and some that do not.
- Experiment, running the code multiple times. When the iterations don't divide evenly, what
is the default decomposition?

### Patternlet 7

This patternlet shows a different way to parallelize the iterations of a loop. 
It assigns sequential iterations of the loop to different threads, then repeats
the process.

- Read through the code and note what is different here
- Run the code and observe the behavior: record your observations here
- Comment out lines 31 through 36, and uncomment lines 38 through 50
- Verify that the results are the same
- Restore the code to its original form, and change the word `static` to `dynamic`
- Record what happens
- Change the 1 to a 2 or a 4 and record how that changes the behavior of the code

### Patternlet 8

This patternlet shows how to combine the results of parallel iteration safely. The
threads need to communicate to access the shared `sum` variable without interfering
with each other. This is called a "reduction" because we are reducing a collection of
values to a single aggregate value.

The program initializes the array to random values, and then computes the sum of the
values sequentially. It then parallelizes the calculation of the sum.

- Compile and run the program; note that correct output is produced
- Uncomment the pragma in function `parallelSum`, but leave its reduction clause commented out
- Recompile and rerun: now an incorrect sum is reported!
- Uncomment the `reduction(+:sum)` clause of the pragma
- Recompile and rerun it: The correct output is produced again

### Patternlet 11

This patternlet shows how to work with an array of data, and how to ensure that 
variables that can't be shared across threads are made private to each thread.

- Examine the program, and run it with all pragmas commented out; verify the correct result
- Experiment with uncommenting the A pragma: What do you observe? Record your observations here
- Experiment with uncommenting the B pragma: What do you observe?
- What happens if you only declare one of the two variables to be private?
- What happens if you enclose the for loops in a block, and declare the `i` and `j` variables
inside the block that is parallelized?

## References

- OpenMP Tutorials
    - [_Dive into Systems_, Section 14.7](https://diveintosystems.org/book/C14-SharedMemory/openmp.html)
    - [Geeks for Geeks OpenMP Hello World Program](https://www.geeksforgeeks.org/openmp-hello-world-program/)
    - [IBM Shared and Private Variables in a Parallel Environment](https://www.ibm.com/docs/en/zos/2.2.0?topic=programs-shared-private-variables-in-parallel-environment)
- Command-line arguments in C
    - [*Dive into Systems*, Section 2.9.2](https://diveintosystems.org/book/C2-C_depth/advanced_cmd_line_args.html#_c_cmd_line_args_)
    - [Command-Line Arguments in C/C++, by Geeks for Geeks](https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/)
