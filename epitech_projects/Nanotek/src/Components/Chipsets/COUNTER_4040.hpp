#pragma once

#include "./../IComponent.hpp"
#include <vector>

class COUNTER_4040: public nts::IComponent {
	private:
		bool	stop;
		std::size_t		transposedArray[12];

	public:
		COUNTER_4040(const std::string & name, const std::string & type): transposedArray{9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1} {
			this->pins = std::map<std::size_t, std::unique_ptr<Pin> >();
			this->pins.emplace(1, std::make_unique<Pin>(1, this));
			this->pins.emplace(2, std::make_unique<Pin>(2, this));
			this->pins.emplace(3, std::make_unique<Pin>(3, this));
			this->pins.emplace(4, std::make_unique<Pin>(4, this));
			this->pins.emplace(5, std::make_unique<Pin>(5, this));
			this->pins.emplace(6, std::make_unique<Pin>(6, this));
			this->pins.emplace(7, std::make_unique<Pin>(7, this));
			this->pins.emplace(9, std::make_unique<Pin>(9, this));
			this->pins.emplace(10, std::make_unique<Pin>(10, this));
			this->pins.emplace(11, std::make_unique<Pin>(11, this));
			this->pins.emplace(12, std::make_unique<Pin>(12, this));
			this->pins.emplace(13, std::make_unique<Pin>(13, this));
			this->pins.emplace(14, std::make_unique<Pin>(14, this));
			this->pins.emplace(15, std::make_unique<Pin>(15, this));

			this->name = name;
			this->type = type;
			this->stop = false;
		}

		void	simulate(std::size_t tick)  {
			for (std::size_t i = 0; i < tick; i++) {
				this->stop = false;
				nts::Tristate oldValue = this->pins[10]->getValue();
				this->pins[10]->setValue(this->pins[10]->getLink()->getValue());
				this->pins[11]->setValue(this->pins[11]->getLink()->getValue());
				if (this->pins[11]->getValue() == nts::TRUE) this->reset();
				else if (oldValue == nts::FALSE && this->pins[10]->getValue() == nts::TRUE) { // ? low to high
					this->compute(9);
					this->compute(7);
					this->compute(6);
					this->compute(5);
					this->compute(3);
					this->compute(2);
					this->compute(4);
					this->compute(13);
					this->compute(12);
					this->compute(14);
					this->compute(15);
					this->compute(1);
				}
			}
		}

		nts::Tristate	compute(std::size_t pin)  {
			if (!this->stop) {
				std::size_t index = 0;
				for (; transposedArray[index] != pin; index++); 
				bool beforeIsTrue = true;
				std::cout << pin << std::endl;
				for (int i = index - 1; i >= 0; i--) {
					if (this->pins[this->transposedArray[i]]->getValue() != nts::TRUE) {
						beforeIsTrue = false;
					}
				}
				if (beforeIsTrue) {
					if (index == 11 && this->pins[pin]->getValue() == nts::TRUE) { // ? Case where the whole counter is done
						this->stop = true;
						for (size_t i = 0; i < 12; i++) {
							this->pins[this->transposedArray[i]]->setValue(nts::FALSE);
						}
					} else if (this->pins[pin]->getValue() == nts::UNDEFINED || this->pins[pin]->getValue() == nts::FALSE) {
						this->pins[pin]->setValue(nts::TRUE);
						this->stop = true;
						for (int i = index - 1; i >= 0; i--) {
							this->pins[this->transposedArray[i]]->setValue(nts::FALSE);
						}
					}
				}
			}

			return this->pins[pin]->getValue();
		}

		void	reset() {
			for (auto ite = this->pins.begin(); ite != this->pins.end(); ite++) {
				(*ite).second->setValue(nts::FALSE); // ? Undefined or FALSE ?
			}
			this->stop = false;
		}

		virtual void	dump() const {
			
		}
};

