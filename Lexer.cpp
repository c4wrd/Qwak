//
// Created by Cory Forward on 1/23/16.
//

#include "Lexer.h"

namespace Qwak {
    // to be implemented
    Lexer::Lexer(const std::string &fName) : current_col(1), current_row(1) {
        this->str_workingFile = fName;
        this->f_fileStream.open(fName);
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

    /*
     * Starts the build process for generating our token queue. Will return a boolean, true signifying a successful
     * queue generation, false should we have some syntactical issues in our input stream
     */
    bool Lexer::build_tokens() {
        int current_char;

        // to be implemented
    }
}