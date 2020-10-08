# hash_table_spell_check
To compile on terminal type
make create_and_test_hash or spell_check

To run:
./create_and_test_hash <file1> <file2> <flag>
./spell_check <document-file> <dictionary-file> 
**dictionary files are: words.txt and wordsEn.txt


Part 1: implementation of quadratic and linear probing
For this part, I made modifications to the quadratic_probing.h that was provided and created a linear_probing.h file.  I added functions that extract the required statistics and to track collisions and count probes, I modified the FindPos() function by adding counters.

Part 2: implementation of double hashing
For this part, I created a double_hashing.h file and made similar modifications as I did for part 1.  For collisions and probing, I added a second internal hash function and counters to extract the statistics required.

The challenging parts were implementing the proper double hashing procedure in FindPos() and making the r_value a command line argument.  I constantly ran into a "floating point exception: 8" error when trying to assign my private r_value variable to the one inserted, despite me converting it to an int from ch > string > int and using a public method to gain access to the private variable.  
The r_values I used were: 7, 13, 37.  The last two gave me closer results of collisions that resembled the ones on the expected output file.

Part 3: implementation of spell_check

For this part I modified the spell_check.cc file provided by creating a hash table then parsing and inserting all words in the dictionary file.  I then parsed the document file, changed every word to lower case and compared each of them to the words in the hash table.  To implement the cases, I assigned each incorrect word to a string for the alteration process.

Case A: go through every letter in incorrect word and add a letter from the alphabet to form a new word.  If the new word matched what is in the dictionary, then we have a fix.

Case B: go through every letter in incorrect word and remove a letter to form a new word.  If the new word matched what is in the dictionary, then we have a fix.

Case C: go through every letter in the incorrect word, except last one and swap letters adjacent to each other to form a new word.  If new word matches what is in dictionary, then we have a fix. 
