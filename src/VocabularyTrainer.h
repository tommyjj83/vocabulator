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
    virtual const TranslationUnit & get_current() = 0;

    /**
     * This function updates internal structure, so that the next call of get_current() would return next translation unit in order
     */
    virtual void update() = 0;
};
