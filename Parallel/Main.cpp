#define _CRT_SECURE_NO_WARNINGS
#define INPUT_FILENAME "/Users/Edi/Documents/GitHub/APD_Project/input/input_1M.txt"
#define OUTPUT_FILENAME "/Users/Edi/Documents/GitHub/APD_Project/output parallel/output.txt"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <mpi.h>
#include <string>

using namespace std;
using namespace std::chrono;

const int MAX_WORDS = 8000;
const int MAX_WORD_LENGTH = 50;

int main(int argc, char** argv)
{
	auto start_time = high_resolution_clock::now();

	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	ifstream input_file(INPUT_FILENAME);
	if (!input_file.is_open())
	{
		cout << "Could not open the file: " << INPUT_FILENAME << "\n";
		MPI_Finalize();
		return -1;
	}

	char delimiters[162] = {};
	int index = 0;
	for (int ascii_character = 32; ascii_character < 256; ++ascii_character)
	{
		if (!isalnum(ascii_character))
		{
			delimiters[index++] = static_cast<char>(ascii_character);
		}
	}

	char local_words[MAX_WORDS][MAX_WORD_LENGTH] = {};
	int local_word_count[MAX_WORDS] = {0};
	string line;
	int line_count = 0;
	while (getline(input_file, line))
	{
		if (line_count % size == rank)
		{
			char* word = strtok(&line[0], delimiters);
			while (word != nullptr)
			{
				int hash = 0;
				for (int i = 0; word[i] != '\0'; ++i)
				{
					hash = (hash * 2 + word[i]) % 997;
				}

				++local_word_count[hash];
				strcpy(local_words[hash], word);

				word = strtok(nullptr, delimiters);
			}
		}
		line_count++;
	}

	input_file.close();

	int global_word_count[MAX_WORDS] = {0};
	MPI_Allreduce(local_word_count, global_word_count, MAX_WORDS, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	char all_words[MAX_WORDS][MAX_WORD_LENGTH] = {};
	MPI_Allreduce(local_words, all_words, MAX_WORDS * MAX_WORD_LENGTH, MPI_CHAR, MPI_MAX, MPI_COMM_WORLD);

	if (rank == 0)
	{
		ofstream output_file(OUTPUT_FILENAME);
		if (!output_file.is_open())
		{
			cout << "Could not create the file: " << OUTPUT_FILENAME << "\n";
			return -1;
		}

		for (int i = 0; i < MAX_WORDS; ++i)
		{
			if (global_word_count[i] > 0)
			{
				output_file << all_words[i] << " : " << global_word_count[i] << "\n";
			}
		}

		auto end_time = high_resolution_clock::now();
		auto duration_micro = duration_cast<microseconds>(end_time - start_time);

		output_file << "\nExecution time: " << duration_micro.count() << " microseconds ";
		output_file << "(" << duration_micro.count() / 1000000.0 << " milliseconds)\n";

		output_file.close();

		cout << "Output successfully written to: " << OUTPUT_FILENAME << "\n";
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
