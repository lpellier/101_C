#pragma once

#include "./../IComponent.hpp"
#include <vector>

class NAND_4011: public nts::IComponent {
	public:
		NAND_4011(const std::string & name, const std::string & type) {
			this->pins = std::map<std::size_t, std::unique_ptr<Pin> >();
			this->pins.emplace(1, std::make_unique<Pin>(1, this));
			this->pins.emplace(2, std::make_unique<Pin>(2, this));
			this->pins.emplace(3, std::make_unique<Pin>(3, this));
			this->pins.emplace(4, std::make_unique<Pin>(4, this));
			this->pins.emplace(5, std::make_unique<Pin>(5, this));
			this->pins.emplace(6, std::make_unique<Pin>(6, this));
			this->pins.emplace(8, std::make_unique<Pin>(8, this));
			this->pins.emplace(9, std::make_unique<Pin>(9, this));
			this->pins.emplace(10, std::make_unique<Pin>(10, this));
			this->pins.emplace(11, std::make_unique<Pin>(11, this));
			this->pins.emplace(12, std::make_unique<Pin>(12, this));
			this->pins.emplace(13, std::make_unique<Pin>(13, this));

			this->name = name;
			this->type = type;
		}

		void	simulate(std::size_t tick)  {
			for (std::size_t i = 0; i < tick; i++) {
				this->compute(3);
				this->compute(4);
				this->compute(10);
				this->compute(11);
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			if (pin == 3) {
				this->pins[3]->setValue(nts::gates::_nand(this->compute(1), this->compute(2)));
				return this->pins[3]->getValue();
			}
			else if (pin == 4) {
				this->pins[4]->setValue(nts::gates::_nand(this->compute(5), this->compute(6)));
				return this->pins[4]->getValue();
			}
			else if (pin == 10) {
				this->pins[10]->setValue(nts::gates::_nand(this->compute(8), this->compute(9)));
				return this->pins[10]->getValue();
			}
			else if (pin == 11) {
				this->pins[11]->setValue(nts::gates::_nand(this->compute(12), this->compute(13)));
				return this->pins[11]->getValue();
			}
			else if (pin == 1 || pin == 2 || pin == 5 || pin == 6 || pin == 13 || pin == 12 || pin == 9 || pin == 8) {
				Pin * link = this->pins[pin]->getLink();
				this->pins[pin]->setValue(link->getValue());
				return this->pins[pin]->getValue();
			}
			else {
				throw new nts::InvalidPinException();
			}
		}

		virtual void	dump() const {
			
		}
};

