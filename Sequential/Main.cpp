#define _CRT_SECURE_NO_WARNINGS
#define INPUT_FILENAME "/Users/Edi/Documents/GitHub/APD_Project/input/input_16M.txt"
#define OUTPUT_FILENAME "/Users/Edi/Documents/GitHub/APD_Project/output sequential/output.txt"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

	map<string, int> word_count;
	string line;
	while (getline(input_file, line))
	{
		char* word = strtok(&line[0], delimiters);
		while (word != nullptr)
		{
			++word_count[word];
			word = strtok(nullptr, delimiters);
		}
	}

	input_file.close();

	ofstream output_file(OUTPUT_FILENAME);
	if (!output_file.is_open())
	{
		cout << "Could not create the file: " << OUTPUT_FILENAME << "\n";
		return -1;
	}

	for (const auto& pair : word_count)
	{
		output_file << pair.first << " : " << pair.second << "\n";
	}

	auto end_time = high_resolution_clock::now();
	auto duration_micro = duration_cast<microseconds>(end_time - start_time);

	output_file << "\nExecution time: " << duration_micro.count() << " microseconds ";
	output_file << "(" << duration_micro.count() / 1000000.0 << " milliseconds)\n";

	output_file.close();

	cout << "Output successfully written to: " << OUTPUT_FILENAME << "\n";

	return 0;
}
