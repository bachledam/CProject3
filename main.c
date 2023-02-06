// integer-sorts.c - demonstrate basic sorting algorithms
/* The idea of sorting is simple: take unordered objects, and arrange them in an
   order.  It has a lot of uses, so there's been a lot of work done with it.  Here,
   we're going to demonstrate a few of the simpler, more classic sorting
techniques.
   */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "leak_detector_c.h"

void quick_sort(int *list, int n);
void bubble_sort(int *list, int n);
void selection_sort(int *list, int n);
void insertion_sort(int *list, int n);
void merge_sort(int *list, int n);
void merge_insertion_sort(int *list, int n);
/* Tracking functions. */
int Comparisons;
int Copies;
int Block_Copies;
int Swaps;
int Mallocs;
clock_t Start_Cpu;
void clear_stats()
{
    Comparisons = 0;
    Copies = 0;
    Block_Copies = 0;
    Swaps = 0;
    Mallocs = 0;
    Start_Cpu = clock();
}
void print_stats()
{
  clock_t end_cpu = clock();
  printf("Sort complete with:\n");
  printf("  %10d comparisons\n", Comparisons);
  printf("  %10d block copies\n", Block_Copies);
  printf("  %10d total copies\n", Copies);
  printf("  %10d swaps\n", Swaps);
  printf("  %10d allocations\n", Mallocs);
  printf("  %10.2lfs CPU time used\n", ((double) (end_cpu - Start_Cpu)) /
CLOCKS_PER_SEC);
}
/* Output a list of integers. */
void output_integer_list(int *list, int n, char *title) {
  printf("List %s:\n", title);
  for(int i = 0; i < n; i++) {
    printf("  Value %3d: %10d\n", i, list[i]);
  }
  printf("\n");
}
int *make_some_integers(int n)
{
  int *integers = malloc(sizeof(int) * n);
  time_t t;
  srand((unsigned) time(&t));
  for(int i = 0; i < n; i++)
  {
    integers[i] = rand();
  }
  return integers;
}
/* Main program. */
int main(void) {
  atexit(report_mem_leak);
  int n = 50000;
  int *our_list = make_some_integers(n);
  int *our_unsorted_list = malloc(sizeof(int) * n);
//  output_integer_list(our_list, n, "unsorted values");
  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  bubble_sort(our_unsorted_list, n);
  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  selection_sort(our_unsorted_list, n);
  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  quick_sort(our_unsorted_list, n);
  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  insertion_sort(our_unsorted_list, n);
  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  merge_sort(our_unsorted_list, n);
  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  merge_insertion_sort(our_unsorted_list, n);
//  output_integer_list(our_unsorted_list, n, "sorted values");
  free(our_list);
  free(our_unsorted_list);
  return 0;
}
