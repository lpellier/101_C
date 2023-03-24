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
		Tristate _and(const Tristate &lhs, const Tristate &rhs) {
			if (lhs == FALSE || rhs == FALSE) return FALSE;
			else if (lhs == TRUE && rhs == TRUE) return TRUE;
			return UNDEFINED;
		}
		Tristate _or(const Tristate &lhs, const Tristate &rhs) {
			if (lhs == TRUE || rhs == TRUE) return TRUE;
			else if (lhs == FALSE && rhs == FALSE) return FALSE;
			return UNDEFINED;
		}
		Tristate _not(const Tristate &lhs) {
			if (lhs == UNDEFINED) return UNDEFINED;
			else if (lhs == TRUE) return FALSE;
			else return TRUE;
		}
		Tristate _nor(const Tristate &lhs, const Tristate &rhs) {
			return _not(_or(lhs, rhs));
		}
		Tristate _nand(const Tristate &lhs, const Tristate &rhs) {
			return _not(_and(lhs, rhs));
		}
		Tristate _xor(const Tristate &lhs, const Tristate &rhs) {
			if (lhs == UNDEFINED || rhs == UNDEFINED) return UNDEFINED;
			else if (lhs != rhs) return TRUE;
			else return FALSE;
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