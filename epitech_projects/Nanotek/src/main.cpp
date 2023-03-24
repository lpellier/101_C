#include "FileParser.hpp"
#include <signal.h>
#include <chrono>
#include <thread>

bool sigint;

void my_handler(int s){
	(void)s;
	sigint = true;
}

int main(int argc, char **argv) {
	if (argc != 2)
		throw new std::exception();
	FileParser parser(argv[1]);
	Circuit circuit = parser.instantiateCircuit();
	std::string cmd;

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	while (42) {
		std::cout << "> ";
		sigint = false;
		if (!std::getline(std::cin, cmd) || cmd.compare("exit") == 0) {
			break ;
		}
		else if (cmd.compare("display") == 0) {
			circuit.display();
		}
		else if (cmd.compare("simulate") == 0) {
			circuit.simulate(1);
		}
		else if (cmd.compare("loop") == 0) {
			while (!sigint) {
				circuit.simulate(1);
				circuit.display();
				// std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			sigint = false;
		}
		else if (cmd.find('=') != std::string::npos) {
			try {
				std::string name = cmd.substr(0, cmd.find('='));
				std::string value = cmd.substr(cmd.find('=') + 1);
				if (!circuit.nameExists(name) || 
					(circuit.getComponent(name)->getType().compare("input") != 0 && 
					circuit.getComponent(name)->getType().compare("clock") != 0) || 
					value.length() > 1) {
					std::cout << "Error in assignment." << std::endl;
				}
				else {
					if (value.compare("0") == 0) circuit.getComponent(name)->pins[1]->setValue(nts::FALSE);
					else if (value.compare("1") == 0) circuit.getComponent(name)->pins[1]->setValue(nts::TRUE);
					else if (value.compare("U") == 0) circuit.getComponent(name)->pins[1]->setValue(nts::UNDEFINED);
					else {
						std::cout << "Error in assignment" << std::endl;
					}
				}
			} catch (std::exception & e) {
				std::cout << "Error in assignment" << std::endl;
			}
		}
	}
}
