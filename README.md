RLEscript
=========

A simple run length encoder/decoder coded in C.

This script shows how the run-length-encoding algorithm works.
The count of a character is inside brackets {}.
For example, when selecting decode as an option, "{3}a" will output "aaa".
When selecting encode as an option, "bbb" will output "{3}b".

This program currently reads in files, and outputs the encoded/decoded format.
The next update should output as a new file.

Complexity: O(n), but can anyone confirm?

Bugs: There may be an uninitialized variable somewhere..
