/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include <chrono>
#include <random>

class PRNG {
  public:
    /**
     * Initializes instance using system time, but in such way, that each run of the application will generate different sequence
     */
    PRNG() {
        // Inspired by https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
        std::random_device rd;
        std::mt19937::result_type seed = rd() ^ (
                (std::mt19937::result_type)
                        std::chrono::duration_cast<std::chrono::seconds>(
                                std::chrono::system_clock::now().time_since_epoch()
                        ).count() +
                (std::mt19937::result_type)
                        std::chrono::duration_cast<std::chrono::microseconds>(
                                std::chrono::high_resolution_clock::now().time_since_epoch()
                        ).count() );

        m_prng_engine = std::mt19937{seed};
    }

    ~PRNG() = default;
    PRNG(const PRNG & other) = delete;
    PRNG(PRNG && other) = delete;

    /**
     * Returns an object that can be latter used when calling get_random_in_range. This object is used to generate numbers
     * in a given range from to uniformly, each of them with the same probability.
     * @param[in] from The number to start the range with. It is included in the range, eg. it is the lowes number that
     * can be latter generated
     * @param[in] to The number to end the range with. It is included in the range, eg. it is the highest number that
     * can be latter generated
     * @returns std::uniform_int_distribution object, that can be used for latter generation of random numbers from given range
     */
    static std::uniform_int_distribution<size_t> get_uniform_range_generator(size_t from, size_t to);

    /**
     * Generates a random number using given distribution object
     * @param[in,out] range Range in which and how the number should be generated. The object can be obtained by calling
     * PRNG::get_x_range_generator()
     * @returns Number in a given range
     */
    size_t get_random_in_range(std::uniform_int_distribution<size_t> & range);

  private:
    std::mt19937 m_prng_engine;
};
