/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#pragma once

#include "TranslationUnit.h"

/**
 * Abstract class for getting an order of translation units for training
 */
class VocabularyTrainer {
  public:
    VocabularyTrainer() = default;
    virtual ~VocabularyTrainer() = default;
    VocabularyTrainer(const VocabularyTrainer & other) = default;
    VocabularyTrainer(VocabularyTrainer && other) = default;

    /**
     * This function returns the current translation unit in order specified by implementation of each child class
     * @returns The current translation unit in order specified by implementation of each child class
     */
    virtual const TranslationUnit & get_current() const = 0;

    /**
     * This function updates internal structure, so that the next call of get_current() would return next translation unit in order
     */
    virtual void update() = 0;

    /**
     * This function gets the vocabulary in the state in which the trainer has it, with all the changes made.
     * @returns The vocabulary in a state in which it is after possible changes made
     */
    virtual std::vector<TranslationUnit> get_vocabulary() const = 0;

    /**
     * This function adjusts weight of TranslationUnit returned by calling get_current() and if given trainer needs to,
     * it update its structures. If the new weight should be less than allowed range, the weight will be set to the minimal
     * allowed value. The same goes for the other side of the range.
     * @param[in] difference The difference to add to current weight
     */
    virtual void adjust_weight(long difference) = 0;
};
