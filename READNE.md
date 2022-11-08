
# CS313fa22 -- Assignment 6


Name: Thomas Nguyen

Bonus Completed: Yes


## A description of how you modified and compiled your code.
  I modified the code in `thread_incr_psem.c` so that it uses a variable number of threads instead of the default 2 threads. 

  I compiled this program with `cc -pthread ./thread_incr_psem.c`,.
 
## A set of all the assumptions made to run the code.
  I assume that the program will use 3 instances of a 20000000, 40000000, 80000000, 160000000 loops for 2, 4, 8, 16 threads. 

## Any bugs or corner cases you have handled.
  I also assume that even though I account for errors when creating and joining threads, I do not expect for there to be any errors to occur throughout this process.

## Definition of semaphores.
  According to Zybooks, "A semaphore S is an integer variable that, apart from initialization, is accessed only through two standard atomic operations: wait() and signal()."

  In my own words, I would say that sempahores are used when two threads are trying to access the same resource and semaphores ensure that only one thread has access to that shared resource at any given time. 


## Definitions of "real time", "kernel time", "user time".
  Real time - is the actual time that a process takes from it's starting time to it's end time

  Kernel time - is the time that the CPU spent on a process in kernel mode

  User time - is the time that the CPU spent on a process in user mode

## Include plots from the results.
![plot 1](plot.png)


## Descriptions of trends of the plots.
Duis sollicitudin mi in augue tincidunt lacinia. Nam porta euismod viverra. 
Sed eleifend dolor libero, at porttitor orci porttitor vel. Fusce et feugiat risus, quis finibus felis.


## Explanation of the trend results.
Etiam aliquet dui molestie, commodo metus sit amet, posuere sem. Vestibulum et mauris nec enim pharetra commodo eu sit amet eros.
Nam id ornare lorem. Nullam ornare massa dolor, volutpat aliquet lorem ullamcorper vehicula.
