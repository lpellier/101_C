#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "Pin.hpp"

namespace nts
{

    class IComponent {
		protected:
			std::string	name;
			std::string	type;

		public:
			std::map<std::size_t, std::unique_ptr<Pin> >	pins;
			virtual 				~IComponent() = default;

			virtual void			simulate(std::size_t tick) = 0;
			virtual nts::Tristate	compute(std::size_t pin) = 0;
			virtual void			setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
				if (this->pins.find(pin) != this->pins.end() && other.pins.find(otherPin) != other.pins.end()) {
					(this->pins[pin])->setLink(other.pins[otherPin].get());
					(other.pins[otherPin])->setLink(this->pins[pin].get());
				}
				else {
					throw nts::InvalidPinException();	
				}
			}
			virtual void			dump() const = 0;

			virtual std::string		getName() const {
				return this->name;
			}
			virtual std::string		getType() const {
				return this->type;
			}
		};


};
