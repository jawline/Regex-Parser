# Regexp
A regular expression string matcher

Regex is passed as infix with a $ to signal matching.

Some examples
./bin/regex "abc" "abc"
./bin/regex "(a|b)cc" "acc"
./bin/regex "b*" "bbbbbbbb"
./bin/regex "[a-zA-Z]*" "qQ"

Supported syntax
? - String may exist
* - Zero or more instances may exist
+ - One or more instances may exist
| - Left or right side match
() - Brackets can be used to group
[abc] - Any character inside square brackets will be matched (Equivilent to (a|b|c))
[a-z0-9] - Any character between a-z or 0-9 will be added. Can be done with any lower or uppercase letter or digits but not mixed ([a-z] and [A-Z] work but not [a-Z])

TODO:
NFA -> DFA
Escaped characters
I'm sure some other stuff
