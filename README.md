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
   The project contains both the sequential and parallel implementations, and the goal is to compare the execution time.
   - The sequencial implementation:
     This algorithm tokenizes the text into words using strtok, and counts the occurrences of each word. It uses a map data structure to store the word counts. The input is read from a text file, and the output is written in a text file too including the execution time.
   - The parallel implementation:
     This algorithm uses the same strategy as the sequencial one, except the fact that each line of the input text is handled by a process based on their rank and instead of using the map data structure it uses arrays because MPI functions like MPI_Allreduce don't support maps.

## Experimental results
   The execution time of the sequencial and parallel programs are similar, both achiving a performance less than 0.1 ms. Sometimes the sequencial is slightly faster, sometimes the parallel is slightly faster.

## Installation of MS-MPI

- Download and install both files: https://www.microsoft.com/en-us/download/details.aspx?id=105289
- After installing, open Command Prompt and type: set MSMPI

## How to run

It is recommended to run the programs using Visual Studio 2022.

For the parallel program the followings should be added:

![Screenshot](screenshots/Debug.png)

The number "2" represents the number of processes and can be replaced with another number.
