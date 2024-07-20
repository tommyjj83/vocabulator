/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "PRNG.h"

std::uniform_int_distribution<size_t> PRNG::get_uniform_range_generator(size_t from, size_t to) {
    return std::uniform_int_distribution<size_t>(from, to);
}


size_t PRNG::get_random_in_range(std::uniform_int_distribution<size_t> & range) {
    return range(m_prng_engine);
}