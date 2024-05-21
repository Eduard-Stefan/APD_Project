## Table of contents

- [Topic](#topic)
- [Programming language](#programming-language)
- [Framework](#framework)
- [Description](#description)
- [Experimental results](#experimental-results)
- [Installation of MS-MPI](#installation-of-ms-mpi)
- [How to run](#how-to-run)

## Topic 
Counting the frequency of words in a text file
  
## Programming language
C++

## Framework
MS-MPI

## Description
   The project contains the sequential and parallel implementations, and the goal is to compare the execution time.
   - The sequencial implementation:
     This algorithm tokenizes the text into words using strtok, and counts the occurrences of each word. It uses a map data structure to store the word counts. The input is read from a text file, and the output is written in a text file too including the execution time.
   - The MPI parallel implementation:
     This algorithm uses the same strategy as the sequencial one, except the fact that each line of the input text is handled by a process based on their rank and instead of using the map data structure it uses arrays because MPI functions like MPI_Allreduce don't support maps.
   - The Threads parallel implementation:
     This implementation uses the same strategy as the MPI one, where first thread is processing the even lines and the second thread is processing the odd lines.

## Experimental results

### Machine specs:
- Processor: Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz
- RAM: 8GB DDR4 2400MHz
- SSD: 256GB

### Sequential execution times:

- 1K words: 10200 microseconds (0.0102 milliseconds)
- 2K words: 11547 microseconds (0.011547 milliseconds)
- 4K words: 14997 microseconds (0.014997 milliseconds)
- 8K words: 30241 microseconds (0.030241 milliseconds)
- 16K words: 76594 microseconds (0.076594 milliseconds)
- 32K words: 156215 microseconds (0.156215 milliseconds)
- 64K words: 321274 microseconds (0.321274 milliseconds)
- 1M words: 4511677 microseconds (4.51168 milliseconds)
- 16M words: 50413066 microseconds (50.4131 milliseconds)

### Parallel execution times (MPI):

- 1K words: 21244 microseconds (0.021244 milliseconds)
- 2K words: 24906 microseconds (0.024906 milliseconds)
- 4K words: 35603 microseconds (0.035603 milliseconds)
- 8K words: 44007 microseconds (0.044007 milliseconds)
- 16K words: 55630 microseconds (0.05563 milliseconds)
- 32K words: 97150 microseconds (0.09715 milliseconds)
- 64K words: 143656 microseconds (0.143656 milliseconds)
- 1M words: 2095759 microseconds (2.09576 milliseconds)
- 16M words: 29707599 microseconds (29.7076 milliseconds)

### Parallel 2 execution times (Threads):

- 1K words: 15547 microseconds (0.015547 milliseconds)
- 2K words: 21148 microseconds (0.021148 milliseconds)
- 4K words: 31140 microseconds (0.03114 milliseconds)
- 8K words: 33475 microseconds (0.033475 milliseconds)
- 16K words: 48694 microseconds (0.048694 milliseconds)
- 32K words: 106231 microseconds (0.106231 milliseconds)
- 64K words: 170897 microseconds (0.170897 milliseconds)
- 1M words: 3149111 microseconds (3.14911 milliseconds)
- 16M words: 42056671 microseconds (42.0567 milliseconds)

### Chart:
- Blue: Sequential
- Red: MPI
- Yellow: Threads

![Screenshot](screenshots/Chart.png)

Conclusions: Beyond 16K words the parallel implementations becomes faster and faster compared to the sequential implementation. The MPI implementation is slower compared to the Threads implementation until 32K words but beyond 32K words it becomes faster.

## Installation of MS-MPI

- Download and install both files: https://www.microsoft.com/en-us/download/details.aspx?id=105289
- After installing, open Command Prompt and type: set MSMPI

## How to run

It is recommended to run the programs using Visual Studio 2022.

For the MPI parallel program the followings should be added:

![Screenshot](screenshots/Debug.png)

The number "2" represents the number of processes and can be replaced with another number.
