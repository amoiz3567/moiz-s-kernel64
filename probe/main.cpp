#include <iostream>
#include <algorithm>
#include <dirent.h>
#include <vector>

// ASSERT macro.

#define EXPECT(condition, message) \
        if (condition == false) do {std::cerr << message << std::endl; exit(1);} while (1)

std::vector<std::string> list_dirs(std::string dir) {
	std::vector<std::string> files;
	DIR *Dir = opendir(dir.c_str());
	if (Dir == nullptr) {
		return files;
	}
	struct dirent *entry;
	while ((entry = readdir(Dir)) != nullptr) {
		files.push_back(entry->d_name);
	}
	closedir(Dir);
	return files;
}

const std::vector<std::string> disallow = {".", ".."};
std::vector<std::string> cats;
std::string prev;
void run_cats(const std::string directory) {
	//
	for (auto &a: list_dirs(directory)) {
		cats.push_back(directory+"/"+a);
		std::cout << directory<< "/" << a << std::endl;
	}
}
void run_probe(const std::string& directory, const int& gro=0) {
	unsigned short int g = gro;
        for (auto &a: list_dirs(directory)) {
		if (g == 2)
			std::cout << directory << std::endl;
                EXPECT(a != "", "[E] directory error empty.");
                unsigned const int c = count(disallow.begin(), disallow.end(), a);
                if (c == 0) {
			std::cout << prev << a << "/";
			g = 1;
			prev = prev+"/"+a;
			run_probe(directory+"/"+a);
			prev = "";
                }
	}
	if (g != 1)
		std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	EXPECT(argc >= 2, "No Arguement was Given...");
	EXPECT(argc <= 2, "Arguements exceeded... (too many args provided)");
	EXPECT(argc == 2, "ERROR...");
	std::string directory = std::string()+ argv[1];
	run_cats(directory);
	return 0;
}
