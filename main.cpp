#include <iostream>

using namespace std;

int main() {
    Lexer l("scripts\\method.qwak");
    l.buildTokens();

    Parser p(l);

    Tree root = p.buildParseTree();

    return 0;
}