//
// Created by Cory Forward on 1/23/16.
//

#include "Lexer.h"
#include "errors.h"
#include "keywords.h"

namespace Qwak {
    // to be implemented
    Lexer::Lexer(const std::string &fName) : current_col(0), current_row(0) {
        this->str_workingFile = fName;
        this->f_fileStream.open(fName);

        if (this->f_fileStream.is_open()) {
            Keywords::init();
            this->build_tokens();
        }
        else {
            throw FILE_NOT_FOUND;
        }
    }

    /*
     * Retrieves the current location in our input stream
     */
    location Lexer::get_cur_loc() {
        return location(this->current_col, this->current_row);
    }

    /*
     * Updates our location depending on our character, i.e. newlines, tabs, etc...
     */
    void Lexer::update_location(char character) {
        if (character == '\n') {
            this->current_row++;
            this->current_col = 0;
        } else if (character == '\t') {
            this->current_col += 4;         // assuming we have 4 spaced tabs
        } else {
            this->current_col++;
        }
    }

    /*
     * We will attempt to desired_char in our input stream (resulting in our
     * input stream pointing to desired_char + 1). If it does not exist, and we reach the
     * end of the file, we will return false, otherwise true if successfully skipped to
     * that position.
     */
    bool Lexer::skip_to(char desired_char) {
        if (this->f_fileStream.peek() == EOF) {
            return false;
        }

        char input_char;
        while (this->f_fileStream.good()) {
            this->f_fileStream.get(input_char);
            update_location(input_char);
            if (input_char == desired_char)
                return true;
        }   // we've reached the EOF

        return false;
    }

    /*
     * Skips the next character in our input stream
     */
    void Lexer::skip_char() {
        current_col++;
        this->f_fileStream.get();
    }

    bool Lexer::is_valid() {
        return this->f_fileStream.good();
    }

    /*
     * Peeks the next character in the input stream
     */
    char Lexer::peek() {
        return this->f_fileStream.peek();
    }

    /*
     * Pops and returns the next character in our input stream
     */
    char Lexer::get() {
        return this->f_fileStream.get();
    }

    void Lexer::emit(token_identifier identifier) {
        this->m_tokenQueue.push(Token::make_token(identifier, this->get_cur_loc()));
    }

    /*
     * Starts the build process for generating our token queue. Will return a boolean, true signifying a successful
     * queue generation, false should we have some syntactical issues in our input stream
     */
    bool Lexer::build_tokens() {
        char current_char;

        this->m_tokenQueue.push(Token::make_token(token_identifier::FIRST_TOKEN, this->get_cur_loc()));

        while (this->f_fileStream.good()) {
            current_char = get();
            update_location(current_char);
            /*
             * Punctuation
             */
            switch (current_char) {
                case ' ':
                    continue;
                case '\t':
                    continue;
                case '\n':
                    emit(token_identifier::NEW_LINE);
                    break;
                case '+': {
                    emit(token_identifier::ADDITION_OP);
                    break;
                }

                case '-': {
                    emit(token_identifier::SUBTRACTION_OP);
                    break;
                }

                case ';': {
                    emit(token_identifier::SEMICOLON);
                    break;
                }

                case '(': {
                    emit(token_identifier::LEFT_PAREN);
                    break;
                }

                case ')': {
                    emit(token_identifier::RIGHT_PARAN);
                    break;
                }

                case '=': {
                    if (peek() == '=') {
                        skip_char();
                        emit(token_identifier::EQUALITY_OP);
                    } else {
                        emit(token_identifier::ASSIGNMENT_OP);
                    }
                    break;
                }

                case '&': {
                    emit(token_identifier::AND_OP);break;
                }

                case '|': {
                    if (peek() == '|') {
                        emit(token_identifier::OR_OP);
                        skip_char();
                    } else {
                        emit(token_identifier::INVALID_TOKEN);
                        skip_to('\n');                                       // missing matching bar
                    }
                    break;
                }

                case '<': {
                    if (peek() == '=') {
                        emit(token_identifier::LESS_THAN_EQ);
                        skip_char();
                    } else {
                        emit(token_identifier::LESS_THAN);
                    }
                    break;
                }

                case '>': {
                    if (peek() == '=') {
                        emit(token_identifier::GREATER_THAN_EQ);
                        skip_char();
                    } else {
                        emit(token_identifier::GREATER_THAN);
                    }
                    break;
                }

                case '!': {
                    if (peek() == '!') {
                        emit(token_identifier::NOT_EQ);
                        skip_char();
                    } else {
                        emit(token_identifier::INVALID_TOKEN);
                        skip_to('\n');
                    }
                    break;
                }
            }


            /*
             * Keywords and identifiers
             */
            if (isalpha(current_char) || current_char == '_') {
                std::string string_val;
                string_val.reserve(16);
                string_val += current_char;

                current_char = peek();
                while ((isalpha(current_char) || current_char == '_') && this->f_fileStream.good()) {
                    string_val += current_char;
                    skip_char();
                    current_char = peek();
                }

                auto type = Keywords::get_token_identifier(string_val);
                if (type == IDENTIFIER) {
                    this->m_tokenQueue.push(Token::create_identifier(this->get_cur_loc(), string_val));
                } else {
                    emit(type);
                }
            }

            /*
             * Integers
             */
            if (isdigit(current_char)) {
                std::string num_val;
                num_val.reserve(12);
                num_val += current_char;

                current_char = peek();
                while(isdigit(current_char) && this->f_fileStream.good()) {
                    num_val += current_char;
                    skip_char();
                    current_char = peek();
                }

                this->m_tokenQueue.push(Token::create_integer(this->get_cur_loc(), num_val));
            }

            /*
             * String literals
             */
            if (current_char == '\"') {
                std::string string_val;
                string_val.reserve(16);

                current_char = peek();
                while (current_char != '\n' && current_char != '"' && this->f_fileStream.good()) {
                    string_val += current_char;
                    skip_char();
                    current_char = peek();
                }

                if (current_char == '\n')
                {
                    throw ERROR_NON_TERMINATED_STRING;
                }

                if (current_char == '"')
                {
                    skip_char();
                }

                this->m_tokenQueue.push(Token::create_string(this->get_cur_loc(), string_val));
            }
        }

        this->m_tokenQueue.push(Token::make_token(token_identifier::END_OF_FILE, this->get_cur_loc()));
        this->m_tokenQueue.push(Token::make_token(token_identifier::LAST_TOKEN, this->get_cur_loc()));
        return true;
    }

    TokenPointer Lexer::peek_token() {
        return this->m_tokenQueue.empty() ? nullptr : this->m_tokenQueue.front();
    }

    TokenPointer Lexer::pop_token() {
        if (this->m_tokenQueue.empty())
                    return nullptr;
        auto token = this->m_tokenQueue.front();
        this->m_tokenQueue.pop();
        return token;
    }

    void Lexer::skip_token() {
        if (!this->m_tokenQueue.empty())
            this->m_tokenQueue.pop();
    }

}