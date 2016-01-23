//
// Created by Cory Forward on 1/23/16.
//

#include "Token.h"

namespace Qwak {

#define TOKEN_KEYWORD(e, v)     \
            case e:             \
                return v;

    const char * get_token_description(token_identifier id) {
        switch(id) {
            TOKEN_LIST;
            default:
                return "invalid_token_id";
        }
    }

#undef TOKEN_KEYWORD

#define TOKEN_KEYWORD(e, v)     \
    case e:                     \
        return #v;

    const char * get_token_as_string(token_identifier id) {
        switch(id) {
            TOKEN_LIST
        }
    }

#undef TOKEN_KEYWORD


    TokenPointer Token::make_token(token_identifier identifier, location _loc) {
        return TokenPointer(new Token(identifier, _loc));
    }

    TokenPointer Token::create_identifier(location _loc, const std::string &identifier) {
        return TokenPointer(
                new Token(
                        token_identifier::IDENTIFIER,
                        _loc,
                        identifier
                )
        );
    }

    TokenPointer Token::create_string(location _loc, const std::string &string_value) {
        return TokenPointer(
                new Token(
                        token_identifier::STRING_LITERAL,
                        _loc,
                        string_value
                )
        );
    }

    TokenPointer Token::create_integer(location _loc, const std::string &int_string) {
        return TokenPointer(
                new Token(
                        token_identifier::IDENTIFIER,
                        _loc,
                        int_string
                )
        );
    }

    const std::string &Token::get_str() {
        return this->m_buffer;
    }

    token_identifier Token::getId() const {
        return this->m_tokenId;
    }

    location &Token::get_location() {
        return this->l_location;
    }

    const std::string &Token::get_token_description() {
        return Qwak::get_token_description(this->m_tokenId);
    }

    const std::string &Token::get_token_name_str() {
        return Qwak::get_token_as_string(this->m_tokenId);
    }

}