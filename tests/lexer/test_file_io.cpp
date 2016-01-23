//
// Created by Cory Forward on 1/23/16.
//
#include <iostream>
#include "assert.h"
#include "../../Lexer.h"

/*
 * These tests will verify the methods for traversing a file
 * work as expected
 *  - skip_char();
 *  - skip_to_char();
 *  - get();
 *  etc...
 */
void testSkipChar();

int main() {
    testSkipChar();
    return 0;
}


void testSkipChar() {
    Qwak::Lexer l("scripts\\lexer.qwak");
    assert(l.is_valid());

    std::string actual;

    while ( l.is_valid()  && l.peek() != ';') {
        actual += l.get();
    }

    assert(actual.compare("var x = 0") == 0);
}