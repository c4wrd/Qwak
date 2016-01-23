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

    #define TOKEN_LIST                                          \
        TOKEN_KEYWORD(FIRST_TOKEN, "<first-token-marker>")      \
        TOKEN_KEYWORD(END_OF_FILE, "<eof>")                     \
        TOKEN_KEYWORD(LAST_TOKEN, "<last-token-marker")         \
                                                                \
        TOKEN_KEYWORD(IDENTIFIER, "IDENTIFIER")                 \
        TOKEN_KEYWORD(STRING_LITERAL, "string literal")         \
        TOKEN_KEYWORD(INTEGER, "integer literal")               \
                                                                \
        TOKEN_KEYWORD(SEMICOLON, ";")                           \
        TOKEN_KEYWORD(LEFT_PAREN, "(")                          \
        TOKEN_KEYWORD(RIGHT_PARAN, ")")                         \
        TOKEN_KEYWORD(ASSIGNMENT_OP, "=")                       \
                                                                \
        TOKEN_KEYWORD(AND_OP, "&")                              \
        TOKEN_KEYWORD(OR_OP, "||")                              \
        TOKEN_KEYWORD(LESS_THAN, "<")                           \
        TOKEN_KEYWORD(LESS_THAN_EQ, "<=")                       \
        TOKEN_KEYWORD(GREATER_THAN, ">")                        \
        TOKEN_KEYWORD(GREATER_THAN_EQ, ">=")                    \
        TOKEN_KEYWORD(NOT_EQ, "!=")                             \
        TOKEN_KEYWORD(ADDITION_OP, "+")                         \
        TOKEN_KEYWORD(SUBTRACTION_OP, "-")                      \
        TOKEN_KEYWORD(MULTIPLICATION_OP, "*")                   \
        TOKEN_KEYWORD(DIVISION_OP, "\"")


    // X Macro to quickly build our token_identifier enum values

    enum token_identifier {
    #define TOKEN_ENUM(enum_val, _) enum_val,
    #define TOKEN_KEYWORD(e, v) TOKEN_ENUM(e, v)
        TOKEN_LIST
    #undef TOKEN_KEYWORD
    #undef TOKEN_ENUM
    };

    const char * get_token_description(token_identifier id);
    const char * get_token_as_string(token_identifier id);

    class Token;
    typedef std::shared_ptr<const Token> TokenPointer;
    typedef std::shared_ptr<const Token> const_TokenPointer;

    class Token {
        token_identifier m_tokenId;
        location l_location;
        std::string m_buffer;

        Token(token_identifier id, location loc) : \
        m_tokenId(id), l_location(loc), m_buffer(0) {};

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

        const std::string& get_str();
        token_identifier getId() const;
        location& get_location();

        const std::string& get_token_description();
        const std::string& get_token_name_str();
    };

}
#endif //QWAK_TOKEN_H
