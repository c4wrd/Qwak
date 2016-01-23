qwak v0.1

- Method Calling
    func main()
        write(“hi");
    end

main()

- Variable declaration
    var x = "hi";
    var y = 1;
    x = "different";              # comments are not processed


*****

statement = method_decl*
          | if_statement*
          | (
                  var_decl*
                | method_call*
                | assignment_statement*

            ) ";"

primary = string
          | integer
          | "(" expression ")"
          | expression

expression = primary
            | expression binop expression
            | unop expression

binop =   "&" | "||"       % lowest priority
        | "<" | "<=" | ">" | ">=" | "!="
        | "+" | "-"
        | "*" | "/"                     % highest priority

parameters = "(" primary | primary "," parameters ")" | "()"

var_decl = "var" identifier "=" expression

method_decl = "func" identifier parameters
                     statement*
              "end"

method_call = identifier parameters

assignment_statement = identifier "=" expression

if_statement = "if" expression "then" statement* "endf"