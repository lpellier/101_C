/*
** EPITECH PROJECT, 2023
** 4094.hpp
** File description:
** 4094
*/

#pragma once

#include "IComponent.hpp"

namespace nts {
    class C4094 : public IComponent {
        public:
            C4094();
            virtual ~C4094() = default;
            virtual void simulate(std::size_t tick);
            virtual nts::Tristate compute(std::size_t pin);
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
            virtual void dump() const;

        private:
            std::vector<std::pair<std::size_t, std::size_t>> links;
            std::unordered_map<size_t, nts::Tristate> _inputs;
		std::unordered_map<size_t, nts::Tristate> _outputs;
    };
}
