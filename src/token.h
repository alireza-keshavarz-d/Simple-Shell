//
// Created by ka on 8/13/26.
//

#ifndef TOKEN_H
#define TOKEN_H

#include "typedefs.h"
#include <string>

enum class TokenType {
    Word
};

class Token {
public:
    explicit Token(TokenType type, std::string value) : m_type(type), m_value(std::move(value)) {}
    [[nodiscard]] TokenType type() const noexcept { return m_type; }
    [[nodiscard]] sv value() const noexcept { return m_value; }

private:
    TokenType m_type;
    std::string m_value;
};

#endif // TOKEN_H
