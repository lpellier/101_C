#pragma once

#include "./../IComponent.hpp"
#include <vector>

class NOT_4069: public nts::IComponent {
	public:
		NOT_4069(const std::string & name, const std::string & type) {
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
				this->compute(2);
				this->compute(4);
				this->compute(6);
				this->compute(8);
				this->compute(10);
				this->compute(12);
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			if (pin == 2 || pin == 4 || pin == 6) {
				this->pins[pin]->setValue(nts::gates::_not(this->compute(pin - 1)));
				return this->pins[pin]->getValue();
			}
			else if (pin == 8 || pin == 10 || pin == 12) {
				this->pins[pin]->setValue(nts::gates::_not(this->compute(pin + 1)));
				return this->pins[pin]->getValue();
			}
			else if (pin == 1 || pin == 3 || pin == 5 || pin == 7 || pin == 9 || pin == 11 || pin == 13) {
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

