# Sorting project

    Project made by Panait Ana-Maria, group 132

## Goal:

This project written in C++ will take a comparative look at 5 sorting algorithms and show
differences in performance between the 5 algorithms but also the native language sorting algorithm, STL.
The algoritms were tested with 30 tests with natural numbers. The studied algorithms are:

    - Radix Sort (Base 10 and 2^16)
    - Merge Sort
    - Shell Sort (N/2^k and Knuth)
    - Heap Sort
    - Quick Sort (Randomized and Median of three)
    - STL sort

The program will time each sort and check if the sort was done correctly
or shows a fail message.

## Vector generation
For each test a vector of nr_elem elements is generated in the interval [0, val_max),
using `mt19937_64` pseudo-random generator and `uniform_int_distribution`.

## Input data

The testing was done on 30 input sets, each test having the number of elements
n = 10^4, 10^5, 10^6, 10^7, 10^8, 10^9
and the maximum values of the input numbers 10^3, 10^5, 10^7, 10^8 and 10^9.

## Chronometer
Time is chronometered with the `chrono` library. It takes the
start time and the end time of each sorting algorithm and substracts them.
The duration is then displayed in `microseconds`.

## Radix Sort

For Radix Sort a function with a easy modifiable base without bit
operations has been implemented, which has been called for base 10,
and another function for only base 2^16 that uses bit operations.


The idea of Radix Sort is to do digit by digit sort
starting from least significant digit to most significant digit.
Radix sort uses counting sort as a subroutine to sort.


### Complexity:
𝑂 (𝑤*𝑛), where w is the number of digits of numbers and n is the number of numbers

Stable: No

## Merge Sort

Merge Sort is a well-known sorting algorithm, very useful because it has a stable complexity.
It is a Divide and Conquer algorithm, it divides the input array into two halves,
calls itself for the two halves, and then merges the two sorted halves.

### Complexity
Best case: 𝑂(𝑛log⁡ (𝑛))
Average case: 𝑂(𝑛log⁡ (𝑛))
Worst case: 𝑂(𝑛log⁡ (𝑛))

Auxiliary Space: 𝑂(𝑛)

Stable: Yes


## Shell Sort

For Shell Sort two gap selection methods were implemented: Shell's original sequence (N/2, N/4,...,1) and
Knuth's increments (1, 4, 13, ..., (3^k-1)/2).

### Complexity
Best case: 𝑂(𝑛log⁡ (𝑛))
Average case: 𝑂(𝑛log⁡ (𝑛))
Worst case: 𝑂(𝑛^2)

Auxiliary Space:𝑂(1)

Stable: No

## Heap Sort
Heap sort is a comparison-based sorting technique based on
Binary Heap data structure. It is similar to selection sort
where we first find the minimum element and place the minimum element at the beginning.
We repeat the same process for the remaining elements.

### Complexity
Best case: 𝑂(𝑛log⁡ (𝑛))
Average case: 𝑂(𝑛log⁡ (𝑛))
Worst case: 𝑂(𝑛log⁡ (𝑛))

Auxiliary Space:𝑂(1)

Stable: No

## Quick Sort

One of the best known efficient sorting algorithms, based on
Divide and Conquer algorithm. It picks an element as pivot and
partitions the given vector around the picked pivot.
In this project was implemented the method that picks a random element
as pivot and median of three as pivot.

### Complexity
Best case: 𝑂(𝑛 log⁡ (𝑛))
Average case: 𝑂(𝑛 log⁡ (𝑛))
Worst case: 𝑂(𝑛^2)

Auxiliary Space:𝑂(log(𝑛))

Stable: No

## STL Sort

### Complexity
Best case: 𝑂(𝑛log⁡ (𝑛))
Average case: 𝑂(𝑛log⁡ (𝑛))
Worst case: 𝑂(𝑛log⁡ (𝑛))

Auxiliary Space:𝑂(log(𝑛))

## Comparison

### numbers = 10^4 – 10^6, step = 10^4, max_val = 10^5

![image](https://github.com/anamariapanait10/Sorting-project/blob/main/10%5E4%20-10%5E6%2C%20step%20%3D%2010%5E4%2C%20val_max%20%3D%2010%5E5.png)

    Leadboard:
        1.   Radix Sort (Base 2^16)
        2.   STL Sort
        3.   Radix Sort (Base 10)
        4/5. Shell Sort (Knuth) / Quick Sort (median of 3)
        6/7. Heap Sort / Shell Sort
        8.   Merge Sort
        9.   Quick Sort (randomized)


### numbers = 10^6 – 10^7, step = 10^5, max_val = 10^14
![image](https://github.com/anamariapanait10/Sorting-project/blob/main/_10%5E6%20-%2010%5E7%2C%20step%20%3D%2010%5E5%2C%20max_val%3D%2010%5E14.png)

    Leadboard:
        1.   Radix Sort (Base 2^16) 
        2/3. Quick Sort (randomized) / STL Sort
        4.   Quick Sort (median of 3)
        5.   Merge Sort
        6.   Shell Sort (Knuth)
        7/8. Heap Sort / Shell Sort
        9.   Radix Sort (Base 10)

### numbers = 10^7 - 10^8, step = 5 * 10^6, max_val = 10^14
![image](https://github.com/anamariapanait10/Sorting-project/blob/main/numbers%20%3D%2010%5E7%20-%2010%5E8%2C%20step%20%3D%205%20_%2010%5E6%2C%20%20max_val%20%3D%2010%5E14.png)

    Leadboard:
        1.   Radix Sort (Base 2^16)
        2/3. Quick Sort (randomized) / STL Sort
        4.   Quick Sort (median of 3)
        5.   Merge Sort
        6.   Shell Sort (Knuth)
        7/8. Heap Sort / Shell Sort
        9.   Radix Sort (Base 10)


- Radix Sort in base 2^16 which uses bit operations is much more efficient
than the one implemented in base 10 and seems to be the most efficient sort
overall regardless of the number of numbers in the vector or the maximum value.
Radix Sort in base 10 works well on small numbers (max_val = 10^5) and it
greatly decreases its performance on large numbers (max_val = 10^14).
In other words, Radix Sort performance is depending on the number
of "digits" of the number based on which we use.

- Merge Sort is quite slow compared to the rest of the sorts
for the number of sorting elements up to 10^6. Also, Merge Sort
requires an additional memory space of 𝑂(𝑛) for the temporary array.
It goes through the whole process even if the array is sorted.

- Shell Sort that uses the Knuth gap sequence fluctuates much less than Shell Sort
that reduces the gap by half and is more efficient.

- Quick Sort randomized is very slow when the number of elements to sort
range between 10^4 and 10^6. For 10^6 and 10^7 it is surprisingly better
reaching the first places in the leadboard. Quick Sort median of three
is more consistent and does well on both number of numbers and values small and big.
Quick Sort performance decreases considerably when the vector is sorted or almost sorted.


## Conclusions

The conclusions of this project are that there is no optimal
sorting algorithm regardless of the situation and that for each
set of input data some algorithms are better than others which may
not be efficient in other cases.





