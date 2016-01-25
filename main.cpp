#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Tree.h"
#include "Token.h"


using namespace std;

int main() {
    Qwak::Lexer l("scripts/method.qwak");

    auto queue = l.get_token_queue();

    while ( !queue.empty() ) {
        Qwak::TokenPointer& node = queue.front();
        queue.pop();
        if (node->getId() == Qwak::token_identifier::NEW_LINE)
            cout << endl;
        else if (node->getId() == Qwak::token_identifier::IDENTIFIER) {
            cout << "[IDENTIFIER: " << node->get_str() << "]";
        }
        else if (node->getId() == Qwak::token_identifier::STRING_LITERAL) {
            cout << "[STRING: " << node->get_str() << "]";
        }
        else if (node->getId() == Qwak::token_identifier::INTEGER) {
            cout << "[INTEGER: " << node->get_str() << "]";
        }
        else
        {
            cout << "[" << Qwak::get_token_as_string(node->getId()) << "]";
        }
    }
}