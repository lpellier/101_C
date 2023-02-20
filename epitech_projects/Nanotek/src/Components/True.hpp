#pragma once

#include "IComponent.hpp"

class True: public nts::IComponent {
	public:
		True(const std::string & name, const std::string & type) {
			this->pins = std::map<std::size_t, std::unique_ptr<Pin> >();
			this->pins.emplace(1, std::make_unique<Pin>(1, this));
			this->name = name;
			this->type = type;
		}

		void	simulate(std::size_t tick)  {
			for (std::size_t i = 0; i < tick; i++) {
				this->pins[1]->setValue(this->compute(1));
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			if (pin == 1) {
				return nts::TRUE;
			}
			else {
				throw new nts::InvalidPinException();
			}
		}

		virtual void	dump() const {
			
		}
};

