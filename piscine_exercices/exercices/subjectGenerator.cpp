#include <string>
#include <iostream>
#include <vector>
#include <fstream>

size_t	width = 70;

void	printLine(std::ofstream & file, std::string line) {
	size_t	len = line.length();
	
	file << "| ";
	file << line;
	for (size_t i = len + 2; i < width - 1; i++) {
		file << " ";
	}
	file << " |" << std::endl;
}

// void	checkMultipleLine(std::ofstream & file, std::string line) {
// 	if (line.length() >= width - 4) {
// 		std::string					cur_line = line;
// 		std::string::iterator		from(cur_line.begin());
// 		std::string::iterator		until(cur_line.begin() + width - 2);
// 		int							count = 1;
// 		while (cur_line.length() >= width - 4) {
// 			printLine(file, from, until);
// 			cur_line = &line[count * (width - 2)];
// 			from = cur_line.begin();
// 			until = cur_line.begin() + width - 2;
// 			count++;
// 		}
// 	}
// 	else
// 		printLine(file, line);
// }

void	printName(std::ofstream & file, std::string name) {
	size_t	len = name.length();
	
	for (size_t i = 0; i < width / 2 - len / 2 - 1; i++) {
		file << "-";
	}
	file << " " << name << " ";
	for (size_t i = width / 2 + len / 2; i < width; i++) {
		file << "-";
	}
	file << std::endl;
}

int main(int ac, char **av) {
	// check errors
	if (ac < 2 || ac > 3) {
		std::cout << "Please input name of exercice (and width of output)" << std::endl;
		exit(EXIT_FAILURE);
	}

	// read content of subject : loop until user says stop

	std::ofstream	subject("subject.README");
	
	// name of exercice
	std::string		name = std::string(av[1]);
	printName(subject, name);
	printLine(subject, "Required files: " + name + ".c");
	printLine(subject, "");

	if (av[2] != 0)
		width = size_t(av[2]);

	std::string		cmd;
	// authorized functions
	std::cout << "Authorized functions (\"stop\" to move on)" << std::endl;
	printLine(subject, "Authorized functions: ");
	std::cin.clear();
	while (42) {
		std::getline(std::cin, cmd);
		if (cmd == "stop")
			break;
		printLine(subject, cmd);
		std::cin.clear();
	}
	std::cin.clear();
	printLine(subject, "");

	// // precisions
	std::cout << "Precisions (\"stop\" to move on)" << std::endl;
	// printLine(subject, "Precisions: ");
		
	while (42) {
		std::getline(std::cin, cmd);
		if (cmd == "stop")
			break;
		printLine(subject, cmd);
		std::cin.clear();
	}
	std::cin.clear();
	printLine(subject, "");
	
	// prototype
	std::cout << "Prototype (\"stop\" to move on)" << std::endl;
	std::getline(std::cin, cmd);
	if (cmd != "stop") {
		printLine(subject, "Prototype:");
		printLine(subject, cmd);
	}
	std::cin.clear();
	printLine(subject, "");

	// example if there should be one

	std::cout << "Example (\"stop\" to move on)" << std::endl;
	std::getline(std::cin, cmd);
	if (cmd != "stop") {
		printLine(subject, "Example:");
		printLine(subject, cmd);
		printLine(subject, "");
	}
	std::cin.clear();
	for (size_t i = 0; i < width; i++) {
		subject << "-";
	}
	subject << std::endl;

	exit(EXIT_SUCCESS);
}
