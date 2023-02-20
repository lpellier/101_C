#pragma once

#include "IComponent.hpp"
#include "../general.hpp"
#include <vector>

namespace nts {
	class IComponent; 
}

class Pin {
	private:
		nts::Tristate	value;
		std::size_t id;
		nts::IComponent *	parent;
		Pin * link;

	public:
		Pin(std::size_t id, nts::IComponent * parent) {
			this->value = nts::UNDEFINED;
			this->parent = parent;
			this->id = id;
		}

		void setId(std::size_t id) {
			this->id = id;
		}

		void setLink(Pin * pin) {
			this->link = pin;
		}

		void	setValue(nts::Tristate value) {
			this->value = value;
		}

		Pin *	getLink() {
			return this->link;
		}

		nts::IComponent * getParent() {
			return this->parent;
		}

		std::size_t getId() const {
			return this->id;
		}

		nts::Tristate getValue() const {
			return this->value;
		}

};


