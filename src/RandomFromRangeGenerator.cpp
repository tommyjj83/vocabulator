/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "RandomFromRangeGenerator.h"


size_t RandomFromRangeGenerator::current() const {
    return m_current_value;
}


size_t RandomFromRangeGenerator::next() {
    m_current_value = m_range(m_prng);
    return m_current_value;
}
