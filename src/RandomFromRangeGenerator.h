/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include <random>

/**
 * This class encapsulates the work with range generators
 */
class RandomFromRangeGenerator {
  public:
    RandomFromRangeGenerator() = delete;

    /**
     * @param[in] from The number to start the range with. It is included in the range, eg. it is the lowes number that
     * can be latter generated
     * @param[in] to The number to end the range with. It is included in the range, eg. it is the highest number that
     * can be latter generated
     * @param[in,out] prng Pseudo random number generator to use for generating values
     */
    explicit RandomFromRangeGenerator(size_t from, size_t to, std::mt19937 & prng)
    :   m_prng{prng},
        m_range{from, to} {
        next();
    }

    ~RandomFromRangeGenerator() = default;
    RandomFromRangeGenerator(const RandomFromRangeGenerator & other) = default;
    RandomFromRangeGenerator(RandomFromRangeGenerator && other) = default;
    RandomFromRangeGenerator & operator=(RandomFromRangeGenerator other) {
        std::swap(m_current_value, other.m_current_value);
        std::swap(m_range, other.m_range);
        std::swap(m_prng, other.m_prng);

        return *this;
    }

    /**
     * @returns Returns the current value. The value does not change after multiple calls of the function.
     */
    size_t current() const;

    /**
     * @returns Returns the next value. After each call a new value is generated and stored, so it can be latter obtained
     * by calling current()
     */
    size_t next();

  private:
    std::mt19937 & m_prng;
    std::uniform_int_distribution<size_t> m_range;
    size_t m_current_value = 0;
};
