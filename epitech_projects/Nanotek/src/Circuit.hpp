#pragma once

#include "Components/IComponent.hpp"
#include "ComponentFactory.hpp"
#include <vector>
#include <algorithm>

#define RED "\033[31m"
#define RESET "\033[0m"

class Circuit {
	typedef std::pair<std::string, std::unique_ptr<nts::IComponent> > component;

	private:
		std::size_t				tick;
		ComponentFactory		factory;
		std::vector<component>	components;

	public:
		Circuit() {
			this->tick = 0;
		}

		void	addComponent(const std::string & type, const std::string & name) {
			this->components.push_back(std::make_pair(name, this->factory.createComponent(type, name)));
		}

		std::unique_ptr<nts::IComponent> &	getComponent(const std::string & name) {
			for (auto begin = this->components.begin(); begin <= this->components.end(); begin++) {
				if ((*begin).first.compare(name) == 0) {
					return ((*begin).second);
				}
			}
			throw new nts::UnknownComponentNameException();
		}

		void	simulate(std::size_t tick) {
			for (std::size_t i = 0; i < tick; i++) {
					for (auto ite = this->components.begin(); i != this->components.end(); ite++) {
					if ((*ite).second->getType().compare("clock") != 0 && (*ite).second->getType().compare("output") != 0) {
						(*ite).second->simulate(1);
					}
				}
				for (auto ite = this->components.begin(); ite != this->components.end(); ite++) { // ? clock must be computed separately to prevent recomputing 
					if ((*ite).second->getType().compare("output") == 0) {
						(*ite).second->simulate(1);
					}
				}
				for (auto ite = this->components.begin(); ite != this->components.end(); ite++) { // ? clock must be computed separately to prevent recomputing 
					if ((*ite).second->getType().compare("clock") == 0) {
						(*ite).second->simulate(1);
					}
				}
				this->tick += 1;
			}
		}

		void	display() const {
			std::cout << "Tick : " << this->tick << std::endl;
			std::cout << "input(s):" << std::endl;
			std::string type;
			for (auto begin = this->components.begin(); begin < this->components.end(); begin++) {
				type = (*begin).second->getType();
				if (type.compare("input") != 0 && type.compare("clock") != 0) {
					continue;
				}
				std::cout << "	" << (*begin).first << std::endl; 
				for (auto pin = (*begin).second->pins.begin(); pin != (*begin).second->pins.end(); pin++) {
					Pin * link = (*pin).second->getLink();
					std::cout << "		linked to " << link->getParent()->getName() << ":" << link->getId() << std::endl;
					std::cout << "		value=";
					if ((*pin).second->getValue() == nts::UNDEFINED) {
						std::cout << "U";
					} else {
						std::cout << RED << (*pin).second->getValue() << RESET;
					}
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
			std::cout << "output(s):" << std::endl;
			for (auto begin = this->components.begin(); begin < this->components.end(); begin++) {
				type = (*begin).second->getType();
				if (type.compare("output") != 0) {
					continue;
				}
				std::cout << "	" << (*begin).first << std::endl; 
				for (auto pin = (*begin).second->pins.begin(); pin != (*begin).second->pins.end(); pin++) {
					Pin * link = (*pin).second->getLink();
					std::cout << "		linked to " << link->getParent()->getName() << ":" << link->getId() << std::endl;
					std::cout << "		value=";
					if ((*pin).second->getValue() == nts::UNDEFINED) {
						std::cout << "U";
					} else {
						std::cout << RED << (*pin).second->getValue() << RESET;
					}
				}
				std::cout << std::endl;
			}
		}

		bool nameExists(const std::string & name) const {
			for (auto begin = this->components.begin(); begin != this->components.end(); begin++) {
				if ((*begin).first.compare(name) == 0) {
					return true;
				}
			}
			return false;
		}

		std::size_t getTick() const {
			return this->tick;
		}
};
