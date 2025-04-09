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

* `Makefile`
    - a makefile to compile all these programs
* `forkJoin.c`
    - a starter program showingn the fork-join pattern, similar to one from our reading
* `spmd.c`
    - a starter program illustrating the SPMD (single-program multiple-data) pattern, also
    similar to one from our reading
* `arraySPMD.c`
    - a starter program illustrating the SPMD pattern on an array of data
* `private.c`
    - a starter program about private versus shared data
* `iterPatterns.c`
    - a starter program to experiment with different patterns for dividing up iterations
    of a loop across threads
* `leaderWorker.c`
    - a starter program to illustrate the leader-worker pattern
* `reduction.c`
    - a starter program to illustrate how to use reduction to combine results from different threads 


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
    - Either add the call to the `printf` or assign a variable to hold it 
    **inside the pragma's code block**
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
* To simplify the output, use the `num_threads` option on the pragma line
to reduce the number of threads to 4 or 8
* Modify the code to add a shared variable:
    - Declare an `int` variable `sharedVar` at the start of `main`. Because 
    this variable is declared in the parent thread, it will automatically be 
    shared by all the threads
    - Inside the parallel block, add a line to define `sharedVar` to be `id`
    - Add to the print statement to print out the value of `sharedVar`
    - Run the code to see if the values of `id` and `sharedVar` are the same
    - Try adding an additional print statement after the first one to print out
    `sharedVar` again
* When you run the program: what happens? Discuss with your teammates what you 
see, and report your observations and why you think it happened here.

Variables that are declared before and outside of a parallel code block are by 
default shared by all threads. Variables declared inside the parallel code block
are by default private to each thread (each thread has its own copy). 

We can also declare variables before the code block, and then use the pragma
to control what is shared and what is private. The pragma can have two optional
modifiers: `private(...)`, which lists the variables that should be private to
each thread, and `shared(...`), which lists the variables that are shared across all threads.

* Modify this program to declare `id`, `numThreads`, and `sharedVar` at the 
start of `main`.
* Run the code without using the pragma modifiers at all. You should see even worse
race conditions than before!
* Next, add modifiers to the pragma line to set `id` and `numThreads` to be private
and `sharedVar` to be shared.
* What happens?

Lastly, let's make two final changes: change `sharedVar` so that it computes 
something useful, and fix the race condition so that it works correctly.

* Change `sharedVar` so that it is initialized to zero before the parallel block.
Instead of every thread setting it to its id, add an `if` statement inside the
parallel block that asks if the current thread's id number is even. If it is, then
it should add one to `sharedVar`.

If you run the code, it will still exhibit the issues caused by the race condition:
uncontrolled access to a shared variable leads to bad things. What we really want
is to require that only one thread adds to the shared variable at any given time.

OpenMP provides a pragma, `#pragma omp critical` that marks a code block that
is a "critical section" that must be limited to one thread at a time.

* Add this pragma around the line that increments `sharedVar`, and run the program
again. Now it should accurately report how many even-numbered thread ids there are.
(Try different numbers of threads to test this.)


### Task 3: SPMD with for loops and shared array

A common SPMD pattern is to split up the iterations of a for loop across different
threads, or to split up sections of an array so that different threads perform 
the same task on different parts of the array.

* Examine the `arraySPMD.c` program. This is similar to a task from an earlier
homework assignment. It creates a large array of doubles, and then loops over the
array and fills each slot with the square of its index.
* Try running this program as is, in its serial form
* Add in an OpenMP pragma just before the for loop: `#pragma omp parallel for`
* Run the program again: with the default array size, it runs fast enough serially
that we can't really tell if there is any improvement running in parallel.

OpenMP provides a function we can use to time how long the parallel segment takes:
`omp_get_wtime()`. It returns a `double` indicating the current time. We can record the
time just before the parallel code section, and then record the time again just after
it ends, and look at the difference between the two as the elapsed time.

* Assign a variable to hold `omp_get_wtime()` just before the pragma (and after the `printf` statement).

* Assign a different variable to hold `omp_get_wtime()` just after the for loop ends (and before the last `printf` statement).

* Compute the difference, and add it to the final print statement.
* Run the program without the OpenMP pragma (serially) and look at the time taken,
then run it again using the parallel for. Is there a difference? What if you increase
the size of the array? Add a couple more zeros to the array size: what happens.
Record your discussion in this README file.

To test your understanding of the role of shared versus private data, examine
the `private.c` program. This declares a two-dimensional array, and then initializes
every entry in the array to be 1. It then tests to see if the initialization worked
correctly.

* Run the `private.c` program as it is initially, with no pragmas in it. Confirm that it does
work correctly.
* We want to parallelize the first set of `for` loops. Add a `#pragma omp parallel for` before the first outer loop.
* What happens when you run the program again? Why?

* Fix the problem by declaring the necessary variables as private using the appropriate pragma modifier.


### Task 4: Parallel loop variations

Here we will look at ways to control how iterations of a loop are broken up and
allocated to threads.

* Examine the `iterPatterns.c` code, which prints out the thread ID and the
loop variable for each iteration of the loop. Test this with different numbers
of threads to understand how iterations of the loop are assigned to threads.

* What is the pattern for the default behavior: which loop iterations are assigned to which threads? Record your observations here.
* The loop repeats 16 times. Try various numbers of threads, including some that divide 16 evenly and some that do not.
* When the iterations don't divide evenly, what is the default decomposition?

Next we will modify this code to assign chunks of iterations differently. Instead
of splitting up the iterations into equal-sized chunks, we can assign shorter
sequences of iterations to different threads.

* Add the modifier `schedule(static, 1)` to the existing pragma
* Experiment with the program to see the effect. How are iterations
mapped onto threads here? Record your observations here.
* Try changing 1 to 2 in the schedule modifier: what is that effect?

* Finally, change the word `static` to `dynamic`, and observe the results.

Dynamic scheduling has more overhead, as chunks are assigned to threads in a 
greedy manner: whenever a thread is ready for another chunk, it is given it.

* Experiment as we did with static scheduling. Record your observations here.

### Task 5: Leader-worker pattern

* Examine the `leaderWorker.c` program. This shows how a single program can produce different
behavior from different threads. 
* Run the starter program, which doesn't have any parallel blocks
    - Notice that the serial thread is numbered 0, which we are using for the leader
* Add a pragma to declare a parallel block
    - Add curly braces to enclose the body of `main` except the `return` at the end.
    - You might want to set the number of threads to something smaller to make it easier
* Run the program again, and see what the threads do!


### Task 6: Reduction pattern

* Read through all of the `reduction.c` program, carefully. This builds an array of 
random values, and then adds the values serially and in parallel. 
* Run the original version of the program. Notice that we have the same
kind of 
race condition here with the shared variable, `sum`, as we had with
`sharedVar` in the earlier example.
* Try the same fix that we used before: marking the line that adds to `sum` as critical
* This fixed the race condition, but slows down the performance as the threads have
to line up to access `sum`
* Add `omp_get_wtime` calls before, between, and after the calls to `sequentialSum` and `parallelSum`, and use them to compute the elapsed
time for each function. Modify the print statements to report the elapsed times.
* Is parallelizing worth it if we have to mark the `sum` line as critical? Add your response here.

Reduction offers us an alternative structure. If we ask OpenMP to use
reduction in computing `sum`, it will automatically give each thread a local
copy of the `sum` variable, solving the race condition, and it will have
the leader thread combine the other threads' results using the operation
we give it.

* Add to the `parallel for` pragma a reduction modifier: `reduction(+:sum)`
    - This says to use reduction in the calculation of `sum`, so that each thread has its own local copy of `sum`
    - The `+` says for the leader thread to combine the other partial results using +
    - Be sure to remove the `critical` pragma, as we no longer need it
* What happens? Is parallelizing worth it now? Try running on larger values of `SIZE`.

## References

- OpenMP Tutorials
    - [_Dive into Systems_, Section 14.7](https://diveintosystems.org/book/C14-SharedMemory/openmp.html)
    - [Geeks for Geeks OpenMP Hello World Program](https://www.geeksforgeeks.org/openmp-hello-world-program/)
    - [IBM Shared and Private Variables in a Parallel Environment](https://www.ibm.com/docs/en/zos/2.2.0?topic=programs-shared-private-variables-in-parallel-environment)
- Command-line arguments in C
    - [*Dive into Systems*, Section 2.9.2](https://diveintosystems.org/book/C2-C_depth/advanced_cmd_line_args.html#_c_cmd_line_args_)
    - [Command-Line Arguments in C/C++, by Geeks for Geeks](https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/)
