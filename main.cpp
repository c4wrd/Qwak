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
        Qwak::TokenPointer node = queue.front();
        queue.pop();
        cout << "[" << Qwak::get_token_as_string(node->getId()) << "]";
        if (node->getId() == Qwak::token_identifier::NEW_LINE)
            cout << endl;
    }
}