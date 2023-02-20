#pragma once

#include <iostream>
#include <fstream>

#include "Circuit.hpp"

class FileParser {
	private:
		bool	reading_chipsets;
		bool	reading_links;
		std::string file_name;
		std::ifstream file;

	public:
		FileParser(void) = delete;
		FileParser(const std::string & file_name) {
			this->file.open(file_name);
			if (!this->file) {
				throw new nts::InvalidCircuitFileException();
			}

			this->reading_chipsets = false;
			this->reading_links = false;
		}

		Circuit instantiateCircuit() {
			Circuit circuit;

			std::string type, name, link_one, link_one_name, link_two, link_two_name;
			int link_one_pin, link_two_pin;

			for (std::string line; std::getline(this->file, line); ) {
				if (line.compare(".chipsets:") == 0) {
					this->reading_chipsets = true;
					this->reading_links = false;
				}
				else if (line.compare(".links:") == 0) {
					this->reading_chipsets = false;
					this->reading_links = true;
				}
				else if (line.length() == 0);
				else if (reading_chipsets) {
					try {
						type = line.substr(0, line.find(' '));
						name = line.substr(type.length() + 1);
						circuit.addComponent(type, name);
					} catch (std::exception & e) {
						throw new nts::InvalidCircuitFileException();
					}
				}
				else if (reading_links) {
					try {
						link_one = line.substr(0, line.find(' '));
						link_two = line.substr(link_one.length() + 1, line.length());

						link_one_name = link_one.substr(0, link_one.find(':'));
						link_one_pin = std::stoi(link_one.substr(link_one.find(':') + 1, link_one.length()));
						
						link_two_name = link_two.substr(0, link_two.find(':'));
						link_two_pin = std::stoi(link_two.substr(link_two.find(':') + 1, link_two.length()));
					} catch (std::exception & e) {
						throw new nts::InvalidCircuitFileException();
					}		
					if (link_one_pin <= 0 || link_two_pin <= 0) {
						throw new nts::InvalidLinkException();
					}
					circuit.getComponent(link_one_name)->setLink(link_one_pin, *(circuit.getComponent(link_two_name)), link_two_pin);
				}
			}
			return circuit;
		}
};

