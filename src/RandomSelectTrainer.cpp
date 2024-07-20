/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "RandomSelectTrainer.h"


const TranslationUnit & RandomSelectTrainer::get_current() {
    return m_vocabulary[m_generator.current()];
}


void RandomSelectTrainer::update() {
    m_generator.next();
}
