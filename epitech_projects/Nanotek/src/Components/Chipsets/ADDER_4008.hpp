#pragma once

#include "./../IComponent.hpp"
#include <vector>

class ADDER_4008: public nts::IComponent {
	private:
		nts::Tristate carry_out;

	public:
		ADDER_4008(const std::string & name, const std::string & type) {
			this->pins = std::map<std::size_t, std::unique_ptr<Pin> >();
			this->pins.emplace(1, std::make_unique<Pin>(1, this));
			this->pins.emplace(2, std::make_unique<Pin>(2, this));
			this->pins.emplace(3, std::make_unique<Pin>(3, this));
			this->pins.emplace(4, std::make_unique<Pin>(4, this));
			this->pins.emplace(5, std::make_unique<Pin>(5, this));
			this->pins.emplace(6, std::make_unique<Pin>(6, this));
			this->pins.emplace(7, std::make_unique<Pin>(8, this));
			this->pins.emplace(9, std::make_unique<Pin>(9, this));
			this->pins.emplace(10, std::make_unique<Pin>(10, this));
			this->pins.emplace(11, std::make_unique<Pin>(11, this));
			this->pins.emplace(12, std::make_unique<Pin>(12, this));
			this->pins.emplace(13, std::make_unique<Pin>(13, this));
			this->pins.emplace(14, std::make_unique<Pin>(14, this));
			this->pins.emplace(15, std::make_unique<Pin>(15, this));

			this->name = name;
			this->type = type;
		}

		void	simulate(std::size_t tick)  {
			for (std::size_t i = 0; i < tick; i++) {
				this->pins[10]->setValue(this->compute(10));
				this->pins[11]->setValue(this->compute(11));
				this->pins[12]->setValue(this->compute(12));
				this->pins[13]->setValue(this->compute(13));
				this->pins[14]->setValue(this->carry_out);
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			nts::Tristate a_bit, b_bit, carry_in, sum;
			if (pin == 10) { // ? 10 -> output
				a_bit = this->compute(7);
				b_bit = this->compute(6);
				carry_in = this->compute(9);
				// ? Following formula to add two numbers while only using binary operators
				sum = nts::gates::_xor(carry_in, nts::gates::_xor(a_bit, b_bit));
				this->carry_out = nts::gates::_or(nts::gates::_and(a_bit, b_bit), nts::gates::_and(carry_in, nts::gates::_xor(a_bit, b_bit)));
				return sum;
			}
			else if (pin == 11) {
				a_bit = this->compute(5);
				b_bit = this->compute(4);
				carry_in = this->carry_out;
				sum = nts::gates::_xor(carry_in, nts::gates::_xor(a_bit, b_bit));
				this->carry_out = nts::gates::_or(nts::gates::_and(a_bit, b_bit), nts::gates::_and(carry_in, nts::gates::_xor(a_bit, b_bit)));
				return sum;
			}
			else if (pin == 12) {
				a_bit = this->compute(3);
				b_bit = this->compute(2);
				carry_in = this->carry_out;
				sum = nts::gates::_xor(carry_in, nts::gates::_xor(a_bit, b_bit));
				this->carry_out = nts::gates::_or(nts::gates::_and(a_bit, b_bit), nts::gates::_and(carry_in, nts::gates::_xor(a_bit, b_bit)));
				return sum;
			}
			else if (pin == 13) {
				a_bit = this->compute(1);
				b_bit = this->compute(15);
				carry_in = this->carry_out;
				sum = nts::gates::_xor(carry_in, nts::gates::_xor(a_bit, b_bit));
				this->carry_out = nts::gates::_or(nts::gates::_and(a_bit, b_bit), nts::gates::_and(carry_in, nts::gates::_xor(a_bit, b_bit)));
				return sum;
			}
			else if (pin == 9 || pin == 7 || pin == 6 || pin == 5 || pin == 4 || pin == 3 || pin == 2 || pin == 1 || pin == 15) {
				Pin * link = this->pins[pin]->getLink();
				if (!link) return nts::UNDEFINED;
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

