@echo on

rmdir "%1/bison"
mkdir "%1/bison"
rmdir "%1/flex"
mkdir "%1/flex"

bison -d -o %1/bison/ps1.0_parser.cpp -p ps10_ bison/ps1.0_grammar.y

bison -d -o %1/bison/rc1.0_parser.cpp -p rc10_ bison/rc1.0_grammar.y

bison -d -o %1/bison/ts1.0_parser.cpp -p ts10_ bison/ts1.0_grammar.y

bison -d -o %1/bison/vs1.0_parser.cpp -p vs10_ bison/vs1.0_grammar.y

flex -Prc10_ -o %1/flex/rc1.0_lexer.cpp flex/rc1.0_tokens.l
flex -Pps10_ -o %1/flex/ps1.0_lexer.cpp flex/ps1.0_tokens.l
flex -Pts10_ -o %1/flex/ts1.0_lexer.cpp flex/ts1.0_tokens.l
flex -Pvs10_ -o %1/flex/vs1.0_lexer.cpp flex/vs1.0_tokens.l