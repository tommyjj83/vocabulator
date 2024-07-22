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
};
