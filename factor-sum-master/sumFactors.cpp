// ======================================================================
// You must modify this file and then submit it for grading to D2L.
// ======================================================================
//author: Quenten welch 30054505 
//Code taken from @pfedererl and Tutorial examples provided by Grabriella
//examples.
//    n =  1         --> result = 0
//    n =  2         --> result = 0
//    n =  9         --> result = 3
//    n = 35         --> result = 5
//    n = 8589934591 --> result = 7

#include "sumFactors.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

//init glbal variables
int64_t global_sum;
bool global_finished;
pthread_barrier_t barr_id;
int64_t num;

struct Task{
  int64_t input, output;
};
Task tasks[256];




int64_t get_smallest_divisor(int64_t n)
{
  if( n <= 3) return 0; // 2 and 3 are primes
  if( n % 2 == 0) return 2; // handle multiples of 2
  if( n % 3 == 0) return 3; // handle multiples of 3
  int64_t i = 5;
  int64_t max = sqrt(n);
  while( i <= max) {
    if (n % i == 0) return i;
    if (n % (i+2) == 0) return i + 2;
    i += 6;
  }
  return 0;
}


void * thread_function(void * arg) {

  long tid = (long) arg;

  while (1) {

    // Serial Task 1
    int res = pthread_barrier_wait(& barr_id);
    if (res == PTHREAD_BARRIER_SERIAL_THREAD) {

      int64_t num;
      
      if (! (std::cin >> num)) {
        global_finished = true;
        
      } else {
        //divide work
        global_sum = global_sum + get_smallest_divisor(num);
      }     
    }
      // Parallel Task 
      pthread_barrier_wait(& barr_id);
      if (global_finished) {
        pthread_exit(NULL);
      } else {
        tasks[tid].output = get_smallest_divisor(tasks[tid].input);
      }
    
    
    // Serial task 2
    if (pthread_barrier_wait(& barr_id) == PTHREAD_BARRIER_SERIAL_THREAD) {
      printf("Task: %ld on input %ld has smallest div = %ld\n", tid, tasks[tid].input, tasks[tid].output);
      global_sum += tasks[tid].output;
    }
  }
  
  return NULL;

}


int64_t sum_factors(int n_threads)
{

  pthread_t threads[n_threads];
  global_sum = 0;
  global_finished = false;

  pthread_barrier_init(& barr_id, NULL, n_threads);

  for (long i = 0; i < n_threads; i++) {
    pthread_create(&threads[i], NULL, thread_function, (void *)i);
  }

  for (long i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
    
  }

  pthread_barrier_destroy(& barr_id);

  return global_sum;

  /* int64_t sum = 0;
  while( 1) {
    int64_t num;
    if( ! (std::cin >> num) ) break;
    //std::cout << num << std::endl;
    int64_t div = get_smallest_divisor(num);
    sum += div;
  }
  return sum; */
}
