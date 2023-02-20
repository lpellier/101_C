#pragma once

#include <iostream>
#include <memory>

namespace nts {
    enum Tristate
    {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

	namespace gates {
		nts::Tristate _and(const nts::Tristate & lhs, const nts::Tristate & rhs) {
			if (lhs == nts::UNDEFINED || rhs == nts::UNDEFINED)
				return nts::UNDEFINED;
			else if (lhs == nts::TRUE && rhs == nts::TRUE)
				return nts::TRUE;
			return nts::FALSE;
		}
		nts::Tristate _or(const nts::Tristate & lhs, const nts::Tristate & rhs) {
			if (lhs == nts::UNDEFINED || rhs == nts::UNDEFINED)
				return nts::UNDEFINED;
			else if (lhs == nts::TRUE || rhs == nts::TRUE)
				return nts::TRUE;
			return nts::FALSE;
		}
		nts::Tristate _not(const nts::Tristate & lhs) {
			if (lhs == nts::UNDEFINED)
				return nts::UNDEFINED;
			else if (lhs == nts::TRUE)
				return nts::FALSE;
			else if (lhs == nts::FALSE)
				return nts::TRUE;
			return nts::UNDEFINED;
		}
		nts::Tristate _nor(const nts::Tristate & lhs, const nts::Tristate & rhs) {
			return _not(_or(lhs, rhs));
		}
		nts::Tristate _nand(const nts::Tristate & lhs, const nts::Tristate & rhs) {
			return _not(_and(lhs, rhs));
		}

		nts::Tristate _xor(const nts::Tristate & lhs, const nts::Tristate & rhs) {
			if (lhs == nts::UNDEFINED || rhs == nts::UNDEFINED)
				return nts::UNDEFINED;
			else if (lhs != rhs)
				return nts::TRUE;
			else
				return nts::FALSE;
		}
	};

	class InvalidCircuitFileException : public std::exception {
		virtual const char* what() const noexcept {
			return "Invalid circuit file.";
		}
	};
	
	class InvalidChipsetException : public std::exception {
		virtual const char* what() const noexcept {
			return "Invalid chipset in circuit file.";
		}
	};
	
	class InvalidLinkException : public std::exception {
		virtual const char* what() const noexcept {
			return "Invalid link in circuit file.";
		}
	};

	class UnknownComponentTypeException : public std::exception {
		virtual const char* what() const noexcept {
			return "Unknown component type.";
		}
	};

	class UnknownComponentNameException : public std::exception {
		virtual const char* what() const noexcept {
			return "Unknown component name.";
		}
	};

	class InvalidPinException : public std::exception {
		virtual const char* what() const noexcept {
			return "Requested pin does not exist.";
		}
	};
	
	class TooManyLinksException : public std::exception {
		virtual const char* what() const noexcept {
			return "Computed pin has too many links.";
		}
	};

	class MissingInputException : public std::exception {
		virtual const char* what() const noexcept {
			return "A pin is missing an input.";
		}
	};

	class SameNameComponentsException : public std::exception {
		virtual const char* what() const noexcept {
			return "Multiple components share the same name.";
		}
	};

	class NoChipsetException : public std::exception {
		virtual const char* what() const noexcept {
			return "Circuit is missing a chipset.";
		}
	};
}