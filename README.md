# CPP-LexicalAnalysis
C++ program that does lexical analysis on inputs.

This program does lexical analysis on an input file. It will identify the spaces in between words and put them into one of 4 categories. 

[1]Keywords (if,then,etc.)
[2]Identifiers (first characters are either underscore or letter followed by either letters or digits)
[3]Signed integers (+123,-456,789, etc)
[4]Signed floating-point numbers (12.345, +12.45, .0123)

After identifying all words(tokens) the program will put the words in a table defining he token and class type for each word, with 1234 identidying to the above definitions.
