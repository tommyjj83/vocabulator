/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 21. 07. 2024
 */

#pragma once

#include <exception>
#include <cstring>

class InvalidSyntax : public std::exception {
  public:
    explicit InvalidSyntax(const char * message)
    :   m_message{message} {}

    explicit InvalidSyntax(std::string message)
    :   m_message{std::move(message)} {}

    const char * what() const noexcept override {
        return m_message.c_str();
    }

  private:
    std::string m_message;
};
