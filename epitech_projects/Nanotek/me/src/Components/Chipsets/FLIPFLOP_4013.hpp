#pragma once

#include "./../IComponent.hpp"
#include <vector>

class FLIPFLOP_4013: public nts::IComponent {
	public:
		FLIPFLOP_4013(const std::string & name, const std::string & type) {
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
				nts::Tristate	oldClk1 = this->pins[3]->getValue();
				this->pins[3]->setValue(this->compute(3));

				nts::Tristate	set1 = this->compute(6);
				nts::Tristate	reset1 = this->compute(4);
				if (set1 == nts::TRUE)			this->pins[1]->setValue(nts::TRUE);
				else if (reset1 == nts::TRUE)	this->pins[1]->setValue(nts::FALSE);
				else if (oldClk1 == nts::FALSE && this->pins[3]->getValue() == nts::TRUE) this->pins[1]->setValue(this->compute(1));
				this->pins[2]->setValue(nts::gates::_not(this->pins[1]->getValue()));

				nts::Tristate	oldClk2 = this->pins[11]->getValue();
				this->pins[11]->setValue(this->compute(11));
				nts::Tristate	set2 = this->compute(8);
				nts::Tristate	reset2 = this->compute(10);
				if (set2 == nts::TRUE)			this->pins[13]->setValue(nts::TRUE);
				else if (reset2 == nts::TRUE)	this->pins[13]->setValue(nts::FALSE);
				else if (oldClk2 == nts::FALSE && this->pins[11]->getValue() == nts::TRUE) this->pins[13]->setValue(this->compute(1));
				this->pins[12]->setValue(nts::gates::_not(this->pins[13]->getValue()));
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			if (pin == 1) {
				return this->compute(5);
			}
			else if (pin == 13) {
				return this->compute(9);
			}
			else if (pin == 3 || pin == 5 || pin == 6 || pin == 4 || pin == 9 || pin == 8 || pin == 10 || pin == 11) {
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

