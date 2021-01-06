// ======================================================================
// You must modify this file and then submit it for grading to D2L.
// ======================================================================
//Author: Quenten welch 30054505
//Date: november 13th
//Code taken from lecture slides and example code posted by Gabriela Wcislo
// count_pi() calculates the number of pixels that fall into a circle
// using the algorithm explained here:
//
// https://en.wikipedia.org/wiki/Approximations_of_%CF%80
//
// count_pi() takes 2 paramters:
//  r         =  the radius of the circle
//  n_threads =  the number of threads you should create
//
// Currently the function ignores the n_threads parameter. Your job is to
// parallelize the function so that it uses n_threads threads to do
// the computation.

#include "calcpi.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Task { 
  
  int start_row, end_row, radius; 
  uint64_t partial_count = 0; 

};

Task tasks[256];



void * count_task(void * targ) {
  
  struct Task * task = (struct Task *) targ;

  uint64_t pcount = 0;
  int r = task->radius;

  double rsq = double(r) * r;
  
  for (double x = task->start_row; x < task->end_row; x++) {
    for (double y = -task->radius; y <= task->radius; y++) {
      if ((x*x + y*y) <= rsq) { 
        pcount ++;
      }
    }
  }

  task->partial_count = pcount;

  return 0;
}


uint64_t count_pi(int r, int n_threads)
{

  pthread_t threads[n_threads];

  for (int i = 0; i < n_threads; i++) {
    
    tasks[i].start_row = -r + (2*r+1) * i / n_threads;
    tasks[i].end_row = -r + (2*r+1) * (i+1) / n_threads;
    tasks[i].radius = r;
        
    if (0 != pthread_create(& threads[i], NULL, count_task, & tasks[i])) {
      printf("Error: failed to create thread\n"); 
      exit(-1);
    } 
  }

  uint64_t count = 0;

  for (int i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
    count += tasks[i].partial_count;
  }

  

  return count;   


  /* double rsq = double(r) * r;
  uint64_t count = 0;
  for( double x = -r ; x <= r ; x ++)
    for( double y = -r ; y <= r ; y ++) 
      if( x*x + y*y <= rsq) count ++;
    
  return count; */ 
}
