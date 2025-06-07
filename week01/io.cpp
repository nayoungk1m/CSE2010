#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(string str, char delimiter){
	vector<string> internal;
	stringstream ss(str);
	string tok;
	while(getline(ss, tok, delimiter)){
		internal.push_back(tok);
	}
	return internal;
}

int main(int argc, char* argv[]){
	string line;
	ifstream file(argv[1]);
	vector<string> lines;

	// open input.txt
	if (file.is_open()){
		while(getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	
	// calculate prices
	vector<string> output_lines;
	for (int i = 0; i < lines.size(); i++){
		vector<string> tokens = split(lines[i], ' ');
		if (tokens.size() == 3){
			string name = tokens[0];
			double price = stof(tokens[1]);
			long long quantity = stoll(tokens[2]);
			double total = price * quantity;
			output_lines.push_back(name + " " + to_string(total));
		}
	}

	// write output.txt
	ofstream output_file(argv[2]);
	if (output_file.is_open()){
		for (int i = 0; i < output_lines.size(); i++){
			output_file << output_lines[i] + "\n";
		}
		output_file.close();
	}

	return 0;
}