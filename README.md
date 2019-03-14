# Secure_Regex_Project_C
Authors: Jameson Price, Cameron Osborn, Jordan Caraway
Intended environment for compilation includes a minimum gcc --version 4.9.4 or greater
To compile:
gcc -pedantic -Wall -Wextra -Werror main.c myUtils.c -lcrypt

To run:
./a.out

User input guide is as follows:

Name:
Leading spaces, trailing spaces after input, no input, numbers, and symbols are not allowed as input for a name.

Int:
Leading spaces, trailing spaces, no input, non-numerical characters, numbers larger than 2147483647 or smaller than -2147483647 are not allowed as input for a number.

Files:
Leading spaces, trailing spaces, no input are not valid input for file names.
Additionally, the following is enforced for files:
  All file names must be a .c, .txt, or .java file.
  File names cannot be either main.c, myUtils.c, or passwords.txt for either input or output file names
  The input and output file names must be unique
  Input files must exist in the current working directory

Password:
Leading spaces, trailing spaces, no input.
Must be within 8 and 32 characters long
May only contain letters, numbers, or the following symbols; !@#$%
