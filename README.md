# permute
A program to find the permutations of the characters contained in a string.
It allows non-mathematicians to use a classic computer algorithm
which is useful in probability and game theory simulations.

For usage instruction, see the man page.

To compile the program from the source, see the BUILD file. This file
also includes instructions for building a Debian package file (.deb).

I originally wrote this program as a tool to cheat at certain word
puzzles. An example of how this tool can be used to do this follows:

permute ABCD |sort|uniq>in.txt

comm -23 in.txt <(aspell list < in.txt)

where "ABCD" is the string to be permuted

in.txt is a temporary file used to save the raw permutations
before they are passed through the spell checker. The comm
command then compares the list of misspelled words to the
original (raw) list and removes the words that are in common
between the two lists. What remains should be a list of
correctly spelled words (displayed to stdout).

Note that the above sequence will generate a number of false positives
(particularly for words of one or two characters). These can be
easily identified by a quick (human) scan of the final list.
