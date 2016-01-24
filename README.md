# Qwak
Quite Worthless Awkward Kompiler (not actually a compiler)

Qwak is just a small front-end for a quite useless scripting language I have written up. This is purely for learning purposes, I am sure there are many mistakes or poor design choices on my part. I have no experience in building lexical/semantic/syntactic analysis tools from scratch, and have only recently began to learned about them.


How it works
------------
Currently Qwak is a recursive descent parser, i.e. it goes from top to bottom. It'll read the stream character by character, seeing if we match any of our preset rules in our grammar (you can read about those in the grammar.txt file in the repo). If the lexer matches a rule, an instance of a Token is created and a safe pointer is pushed to a queue for syntactic and semantic processing. A tree is then built from these tokens, should it be verified as syntactically correct, which can either be walked manually (for debugging), or interpreted.

Roadmap
-------
 * Qwak Lexer --IN PROGRESS-- *Complete*
 * Implement our grammar in code
 * Implement analysis to verify input matches grammar
 * Create the program Tree and associated classes
 * Implement scopes (each function theoretically should have it's own scope, there will be an entry point scope, and we can explicitly create a scope with brackets '{' new scope here '}')
 * Implement class to parse our token queue into a walkable Tree for interpretation
 * Create our interpreter
 * Never use this again!

Lexer status
------------
The lexer is fully implemented and is tokenizing input streams correctly. 


Here is an example output from the /scripts/method.qwak script:


	["<first-token-marker>"]["func"]["IDENTIFIER"]["("][")"]["new_line"]
	["IDENTIFIER"]["("]["string_literal"][")"]["new_line"]
	["end"]["new_line"]
	["new_line"]
	["var"]["IDENTIFIER"]["="]["IDENTIFIER"]["new_line"]
	["var"]["IDENTIFIER"]["="]["string_literal"]["new_line"]
	["new_line"]
	["if"]["IDENTIFIER"]["=="]["IDENTIFIER"]["then"]["new_line"]
	["IDENTIFIER"]["("]["string_literal"][")"]["new_line"]
	["end"]["<eof>"]["<last-token-marker"]

Currently researching whether to maintain the new line split expressions, or
to implement semi-colons (the original intended use).

Potential Explorations
----------------------
At the moment a script needs to be parsed into a tree and is then interpreted. Needing to parse the source each time (should it not change), is unnecessary and should be replaced. This will eventually be replaced by storing the tree in a file, which can be read much faster than parsing.

License
-------
This project is released under the MIT License, feel free to do anything with it as you wish. It was built for demonstration and learning purposes, and could potentially help those looking to create something similar. 
