#pragma once

#include "Components/IComponent.hpp"
#include "Components/Chipsets/NOR_4001.hpp"
#include "Components/Chipsets/ADDER_4008.hpp"
#include "Components/Chipsets/NAND_4011.hpp"
#include "Components/Chipsets/FLIPFLOP_4013.hpp"
#include "Components/Chipsets/XOR_4030.hpp"
#include "Components/Chipsets/COUNTER_4040.hpp"
#include "Components/Chipsets/NOT_4069.hpp"
#include "Components/Chipsets/OR_4071.hpp"
#include "Components/Chipsets/AND_4081.hpp"
#include "Components/True.hpp"
#include "Components/False.hpp"
#include "Components/Input.hpp"
#include "Components/Clock.hpp"
#include "Components/Output.hpp"

class ComponentFactory {
	private:
		std::unique_ptr<nts::IComponent> createInput(const std::string & name) const noexcept {
			return std::make_unique<Input>(name, "input");
		}
		std::unique_ptr<nts::IComponent> createClock(const std::string & name) const noexcept {
			return std::make_unique<Clock>(name, "clock");
		}
		std::unique_ptr<nts::IComponent> createOutput(const std::string & name) const noexcept {
			return std::make_unique<Output>(name, "output");
		}
		std::unique_ptr<nts::IComponent> createTrue(const std::string & name) const noexcept {
			return std::make_unique<True>(name, "true");
		}
		std::unique_ptr<nts::IComponent> createFalse(const std::string & name) const noexcept {
			return std::make_unique<False>(name, "false");
		}
		std::unique_ptr<nts::IComponent> create4001(const std::string & name) const noexcept {
			return std::make_unique<NOR_4001>(name, "4001");
		}
		std::unique_ptr<nts::IComponent> create4008(const std::string & name) const noexcept {
			return std::make_unique<ADDER_4008>(name, "4008");
		}
		std::unique_ptr<nts::IComponent> create4011(const std::string & name) const noexcept {
			return std::make_unique<NAND_4011>(name, "4011");
		}
		std::unique_ptr<nts::IComponent> create4013(const std::string & name) const noexcept {
			return std::make_unique<FLIPFLOP_4013>(name, "4013");
		}
		std::unique_ptr<nts::IComponent> create4030(const std::string & name) const noexcept {
			return std::make_unique<XOR_4030>(name, "4030");
		}
		std::unique_ptr<nts::IComponent> create4040(const std::string & name) const noexcept {
			return std::make_unique<COUNTER_4040>(name, "4040");
		}
		std::unique_ptr<nts::IComponent> create4069(const std::string & name) const noexcept {
			return std::make_unique<NOT_4069>(name, "4069");
		}
		std::unique_ptr<nts::IComponent> create4071(const std::string & name) const noexcept {
			return std::make_unique<OR_4071>(name, "4071");
		}
		std::unique_ptr<nts::IComponent> create4081(const std::string & name) const noexcept {
			return std::make_unique<AND_4081>(name, "4081");
		}

	public:
		std::unique_ptr<nts::IComponent> createComponent(const std::string & type, const std::string & name) {
			if (type.compare("true") == 0) return this->createTrue(name); 
			else if (type.compare("false") == 0) return this->createFalse(name); 
			else if (type.compare("input") == 0) return this->createInput(name);  
			else if (type.compare("clock") == 0) return this->createClock(name); 
			else if (type.compare("output") == 0) return this->createOutput(name); 
			else if (type.compare("4001") == 0) return this->create4001(name);
			else if (type.compare("4008") == 0) return this->create4008(name);
			else if (type.compare("4011") == 0) return this->create4011(name);
			else if (type.compare("4013") == 0) return this->create4013(name);
			else if (type.compare("4030") == 0) return this->create4030(name);
			else if (type.compare("4040") == 0) return this->create4040(name);
			else if (type.compare("4069") == 0) return this->create4069(name);
			else if (type.compare("4071") == 0) return this->create4071(name);
			else if (type.compare("4081") == 0) return this->create4081(name);
			else {
				throw new nts::InvalidChipsetException();
			}
		}
};
