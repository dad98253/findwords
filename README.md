# findwords
A program to help find perturbations of characters in a string.
The primary purpose of this program is to help cheat when playing
online word games.
Note that the program will generate a number of false positives
(particularly for words of one or two characters). These can be
easily identified by a quick (human) scan of the final list.

Usage:
./findwords ABCD |sort|uniq>in.txt

comm -23 in.txt <(aspell list < in.txt)

where "ABCD" is the string to be permuted

in.txt is a temporary file used to save the raw permutations
before they are passed through the spell checker. The com
command then compares the list of misspelled words to the
original (raw) list and removes the words that are in common
between the two lists. What remains should be a list of
correctly spelled words (displayed to stdout).
