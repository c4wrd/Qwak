//
// Created by Cory Forward on 1/23/16.
//

#ifndef QWAK_TOKEN_H
#define QWAK_TOKEN_H

#include <string>
#include <memory>
#include "location.h"

namespace Qwak {

/*
 * This is a list of our current implemented keywords for our lexer.
 * TOKEN_KEYWORD(VALUE, description)
 */

    #define TOKEN_LIST                                  \
        TOKEN(FIRST_TOKEN, "<first-token-marker>")      \
        TOKEN(END_OF_FILE, "<eof>")                     \
        TOKEN(LAST_TOKEN, "<last-token-marker")         \
        TOKEN(INVALID_TOKEN, "invalid token")           \
                                                        \
        TOKEN(IDENTIFIER, "IDENTIFIER")                 \
        TOKEN(STRING_LITERAL, "string_literal")         \
        TOKEN(INTEGER, "integer_literal")               \
                                                        \
        TOKEN(SEMICOLON, ";")                           \
        TOKEN(LEFT_PAREN, "(")                          \
        TOKEN(RIGHT_PARAN, ")")                         \
        TOKEN(ASSIGNMENT_OP, "=")                       \
        TOKEN(NEW_LINE, "new_line")                     \
        TOKEN(QUOTE, "\"")                              \
                                                        \
        TOKEN(EQUALITY_OP, "==")                        \
        TOKEN(AND_OP, "&")                              \
        TOKEN(OR_OP, "||")                              \
        TOKEN(LESS_THAN, "<")                           \
        TOKEN(LESS_THAN_EQ, "<=")                       \
        TOKEN(GREATER_THAN, ">")                        \
        TOKEN(GREATER_THAN_EQ, ">=")                    \
        TOKEN(NOT_EQ, "!=")                             \
        TOKEN(ADDITION_OP, "+")                         \
        TOKEN(SUBTRACTION_OP, "-")                      \
        TOKEN(MULTIPLICATION_OP, "*")                   \
        TOKEN(DIVISION_OP, "\"")                        \
                                                        \
        TOKEN_KEYWORD(VAR_DECL, "var")                  \
        TOKEN_KEYWORD(FUNC_DECL, "func")                \
        TOKEN_KEYWORD(END, "end")                       \
        TOKEN_KEYWORD(IF, "if")                         \
        TOKEN_KEYWORD(THEN, "then")


    // X Macro to quickly build our token_identifier enum values

    enum token_identifier {
#define TOKEN(ENUM, _) ENUM,
#define TOKEN_KEYWORD(ENUM, _) ENUM,
    TOKEN_LIST
#undef TOKEN_KEYWORD
#undef TOKEN
    };

    const char * get_token_description(const token_identifier id);
    const char * get_token_as_string(const token_identifier id);

    class Token;
    typedef std::shared_ptr<const Token> TokenPointer;
    typedef std::shared_ptr<const Token> const_TokenPointer;

    class Token {
        const token_identifier m_tokenId;
        const location l_location;
        const std::string m_buffer;

        Token(token_identifier id, location loc) : \
        m_tokenId(id), l_location(loc) {};

        Token(token_identifier id, location loc, const std::string& string_val) : \
        m_tokenId(id), l_location(loc), m_buffer(string_val) {};

        // We don't want them to call these, no copying between tokens
        Token();
        Token (const Token &);
        Token &operator=(const Token &);

    public:

        static TokenPointer
        make_token ( token_identifier identifer, location token_loc);

        static TokenPointer
        create_identifier (location _loc, const std::string &identifier);

        static TokenPointer
        create_string (location _loc, const std::string &string_value);

        static TokenPointer
        create_integer (location _loc, const std::string &int_string);

        const std::string& get_str() const;
        const token_identifier& getId() const;
        const location& get_location() const;

        const std::string& get_token_description();
        const std::string& get_token_name_str();
    };

}
#endif //QWAK_TOKEN_H
