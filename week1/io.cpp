#include <iostream>
#include <fstream>

int main(int argc, char** argv){
	std::string line;
	std::ifstream file(argv[1]);
	if (file.is_open()){
		while(getline(file, line)) {
			std::cout << line << std::endl;
		}
		file.close();
	}
	return 0;
}
