#define _CRT_SECURE_NO_WARNINGS
#define INPUT_FILENAME "/Users/Edi/Documents/GitHub/APD_Project/input/input_1M.txt"
#define OUTPUT_FILENAME "/Users/Edi/Documents/GitHub/APD_Project/output parallel 2/output.txt"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <thread>
#include <string>
#include <vector>
#include <mutex>

using namespace std;
using namespace std::chrono;

const int MAX_WORDS = 8000;
const int MAX_WORD_LENGTH = 50;

void process_lines(const vector<string>& lines, const char* delimiters, int start, int step, int* local_word_count, char** local_words)
{
	for (size_t i = start; i < lines.size(); i += step)
	{
		const string& line = lines[i];
		char* word = strtok(const_cast<char*>(line.c_str()), delimiters);
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
}

int main()
{
	auto start_time = high_resolution_clock::now();

	ifstream input_file(INPUT_FILENAME);
	if (!input_file.is_open())
	{
		cout << "Could not open the file: " << INPUT_FILENAME << "\n";
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

	vector<string> lines;
	string line;
	while (getline(input_file, line))
	{
		lines.push_back(line);
	}
	input_file.close();

	int* local_word_count[2] = {new int[MAX_WORDS](), new int[MAX_WORDS]()};
	char** local_words[2] = {new char*[MAX_WORDS], new char*[MAX_WORDS]};
	for (int i = 0; i < MAX_WORDS; ++i)
	{
		local_words[0][i] = new char[MAX_WORD_LENGTH];
		local_words[1][i] = new char[MAX_WORD_LENGTH];
	}

	thread t1(process_lines, ref(lines), delimiters, 0, 2, local_word_count[0], local_words[0]);
	thread t2(process_lines, ref(lines), delimiters, 1, 2, local_word_count[1], local_words[1]);

	t1.join();
	t2.join();

	int global_word_count[MAX_WORDS] = {0};
	for (int i = 0; i < MAX_WORDS; ++i)
	{
		global_word_count[i] = local_word_count[0][i] + local_word_count[1][i];
	}

	char all_words[MAX_WORDS][MAX_WORD_LENGTH] = {};
	for (int i = 0; i < MAX_WORDS; ++i)
	{
		if (local_word_count[0][i] > 0)
		{
			strcpy(all_words[i], local_words[0][i]);
		}
		if (local_word_count[1][i] > 0)
		{
			strcpy(all_words[i], local_words[1][i]);
		}
	}

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

	for (int i = 0; i < MAX_WORDS; ++i)
	{
		delete[] local_words[0][i];
		delete[] local_words[1][i];
	}
	delete[] local_word_count[0];
	delete[] local_word_count[1];
	delete[] local_words[0];
	delete[] local_words[1];

	return 0;
}
