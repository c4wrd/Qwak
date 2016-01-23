//
// Created by Cory Forward on 1/23/16.
//

#ifndef QWAK_LEXER_H
#define QWAK_LEXER_H

#include <memory>
#include <string>
#include <queue>
#include <fstream>
#include "stdio.h"
#include "Token.h"
#include "location.h"

namespace Qwak {
    // to be implemented

    class Lexer {
        std::string str_workingFile;
        std::queue<TokenPointer> m_tokenQueue;
        std::ifstream f_fileStream;    // lets read our file character by character
                                       // not storing it all in RAM at once!
    public:
        int current_col;
        int current_row;
        location get_cur_loc();
        void update_location(char c);   // updates our location based on the character value

        bool skip_to(char desired_char);   // skips to a specified character
        void skip_char();               // skips next character in the stream

        bool is_valid();                // alternative to peeking, this will return whether the ifstream is valid
        char peek();                    // peeks next character in the stream
        char get();                     // gets the next character in the input stream

   // public:
        Lexer(const std::string &fName);
        bool build_tokens();
        std::queue<TokenPointer> &get_token_queue() { return this->m_tokenQueue; }
    };
}


#endif //QWAK_LEXER_H
