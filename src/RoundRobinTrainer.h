/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#pragma once

#include <stdexcept>
#include "TranslationUnit.h"
#include "VocabularyTrainer.h"

/**
 * Class providing implementation of VocabularyTrainer. Order of translation units provided by this class is using
 * round robin method.
 */
class RoundRobinTrainer : public VocabularyTrainer {
  public:
    RoundRobinTrainer() = delete;

    /**
     * @throws std::invalid_argument If the given vocabulary is empty. If the exception is thrown, the object should not be used
     */
    explicit RoundRobinTrainer(std::vector<TranslationUnit> vocabulary)
    :   m_vocabulary{std::move(vocabulary)},
        m_current_unit{0} {
        if (m_vocabulary.empty()) {
            throw std::invalid_argument("Given vocabulary is empty");
        }
    }

    ~RoundRobinTrainer() override = default;
    RoundRobinTrainer(const RoundRobinTrainer & other) = default;
    RoundRobinTrainer(RoundRobinTrainer && other) noexcept = default;

    const TranslationUnit & get_current() const override;

    void update() override;

    std::vector<TranslationUnit> get_vocabulary() const override;

    void adjust_weight(long difference) override;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    size_t m_current_unit;
};
