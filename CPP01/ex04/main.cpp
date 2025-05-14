#include <iostream>
#include <fstream>
#include <string>

bool replaceStringsInFile(const std::string& filename, const std::string& s1, const std::string& s2) {
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open()) {
		std::cerr << "Error: Could not open input file: " << filename << std::endl;
		return false;
	}

	std::string outputFilename = filename + ".replace";
	std::ofstream outputFile(outputFilename.c_str());
	if (!outputFile.is_open()) {
		std::cerr << "Error: Could not create output file: " << outputFilename << std::endl;
		inputFile.close();
		return false;
	}

	// Read input file and replace all occurrences of s1 with s2
	std::string line;
	while (std::getline(inputFile, line)) {
		size_t pos = 0;

		// Find and replace all occurrences of s1 in the current line
		while ((pos = line.find(s1, pos)) != std::string::npos) {
			line.erase(pos, s1.length());
			line.insert(pos, s2);
			pos += s2.length();
		}

		// Write the modified line to the output file
		outputFile << line;

		// Add newline if not EOF
		if (!inputFile.eof()) {
			outputFile << std::endl;
		}
	}
	inputFile.close();
	outputFile.close();

	std::cout << "Replacement completed. Output saved to " << outputFilename << std::endl;
	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " <filename> <string_to_replace> <replacement_string>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty()) {
		std::cerr << "Error: 'string_to_replace' cannot be empty" << std::endl;
		return 1;
	}

	if (!replaceStringsInFile(filename, s1, s2)) {
		return 1;
	}

	return 0;
}
