/*
** EPITECH PROJECT, 2023
** 4017.hpp
** File description:
** 4017
*/

#pragma once

#include "IComponent.hpp"

namespace nts {
    class C4017 : public IComponent {
        public:
            C4017();
            virtual ~C4017() = default;
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
