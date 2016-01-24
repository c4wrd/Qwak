//
// Created by Cory Forward on 1/23/16.
//

#ifndef QWAK_KEYWORDS_H
#define QWAK_KEYWORDS_H

#include <map>
#include "token.h"

namespace Qwak {

    class Keywords {

    private:
        static std::map<std::string, token_identifier> keyword_map;

    public:

#define TOKEN(a, _)
#define TOKEN_KEYWORD(E, V) keyword_map[V] = E;
        static void init() {
                TOKEN_LIST
        }
#undef TOKEN_KEYWORD
#undef TOKEN

        /*
         * This will iterate through our list of keywords (e.g. 'var') and return the TokenType for that
         * if it is that specified keyword, otherwise it's an identifier
         */
        const static token_identifier get_token_identifier(const std::string &identifier) {
            if(keyword_map.count(identifier)) {
                return keyword_map.at(identifier);
            } else {
                return IDENTIFIER;
            }
        }
    };

    std::map<std::string, token_identifier> Keywords::keyword_map = std::map<std::string, token_identifier>();

}

#endif //QWAK_KEYWORDS_H
