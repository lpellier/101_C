#pragma once

#include "IComponent.hpp"

class Clock: public nts::IComponent {
	public:
		Clock(const std::string & name, const std::string & type) {
			this->pins = std::map<std::size_t, std::unique_ptr<Pin> >();
			this->pins.emplace(1, std::make_unique<Pin>(1, this));
			this->pins[1]->setValue(nts::UNDEFINED);
			this->name = name;
			this->type = type;
		}

		void	simulate(std::size_t tick)  {
			for (std::size_t i = 0; i < tick; i++) {
				this->compute(1);
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			if (pin == 1) {
				nts::Tristate oldValue = this->pins[1]->getValue();
				if (oldValue == nts::FALSE)		this->pins[1]->setValue(nts::TRUE);
				else if (oldValue == nts::TRUE)	this->pins[1]->setValue(nts::FALSE);
				return oldValue;
			}
			else {
				throw new nts::InvalidPinException();
			}
		}

		virtual void	dump() const {
			
		}
};

