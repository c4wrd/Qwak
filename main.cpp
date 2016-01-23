#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Tree.h"


using namespace std;

int main() {
    Qwak::Lexer l("method.qwak");



    //l.build_tokens();

   /* Qwak::Parser p(l);

    Qwak::Tree root = p.buildParseTree();*/
    return 0;
}