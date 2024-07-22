/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include "TrainerType.h"

class Settings {
  public:
    TrainerType m_trainer_type = TrainerType::WEIGHTED_RANDOM_SELECT;
    std::string m_path_to_input_file;
    static const unsigned MINIMUM_WEIGHT = 1;  // For correct functionality of WeightedRandomSelectTrainer should be >= 1
    static const unsigned MAXIMUM_WEIGHT = 100;
};
