# Philosophers, a classic programming problem

The first program I created, called "philo", is implemented with the use of threads and mutexes.
My strategy is based on the utilisation of a while loop (called by the check_end() function located in the main() function) checking, for each thread, "impersonating" a philosopher, that no more than "time_to_die" milliseconds have elapsed from the last time they have eaten (the time of the last meal is taken before a philosopher starts eating, just after the thread has gone through the mutexes in the eat() function).
It's in the routine() function that I check if every philosopher has eaten the right amount of meals in the event that the parameter "number_of_times_each_philosopher_must_eat" is present.
The pthread_join() function could be used to keep the main process from stopping before the threads have achieved their tasks. It creates a less resource-spending alternative to a loop in the main process. It is sufficient to put it after the loop containing the pthread_create() function, in a while loop or just isolated, since it isolates the thread processes from the central one.

As concerning the second program, the "bonus" version, it makes use of fork() functions and semaphores, every philosopher being assigned to a process.
In this case, I make use of a thread called by each child process to check how much time has elapsed since the philosopher's last meal and take action in case it has exceeded the time_to_die duration.
In the philosopher_manage() function, a loop takes the count of each philosopher's meal and compares it with the amount to reach, in case the variable "number_of_times_each_philosopher_must_eat" is present.
When a philosopher dies, or when everyone of them reaches the correct amount of meals, the "check" semaphore that restrains the main process from dying opens up, giving access to the function called "the_end()", where every child process is killed and the program is properly quit.

For an interesting example of use of the threads in C, as well as some course notes on threads, see (in French):
* <https://franckh.developpez.com/tutoriels/posix/pthreads>;
* <https://sites.uclouvain.be/SyllabusC/notes/Theorie>.

The CodeVault channel on Youtube offers a full video course on threads and processes in C with good examples and simple explanations:
* <https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2>;
* <https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY>.