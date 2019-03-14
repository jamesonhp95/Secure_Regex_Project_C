#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "./myUtils.h"

/*
 * Authors: Cameron Osborn, Jameson Price, Jordan Caraway
 *         
 *         The attempt of this project was to create a user interface to enter
 *         common input, and sanitize it as necessary to ensure that it follows
 *         the set guidelines for each input type. The most important task with this project
 *         was to create an environment that was 'full proof' against any user input.
 *         
 *         Secure C Application
 *         
 *         1. Prompts for and reads user first name, then last name (max 50
 *         chars)
 *
 *         2. Prompt for and read name of input file from user
 *
 *         3. Prompt for and read name of output file
 *
 *         4. Prompt for and read two int values
 *
 *         5. Prompt user to enter password, store, then ask user to re-enter,
 *         and verify correctness
 *
 *         6. Open output file and write name along with result of adding two
 *         int values and result of multiplying two integer values followed by
 *         input file contents
 *
 *
 *         Program must accept valid input from the user and write to the output
 *         file without error. Any error that does arise should be reported to
 *         either output file, or error log
 */
int main()
{
   char firstName[51];
   char lastName[51];
   long num1;
   long num2;
   char finName[51];
   char foutName[51];
   FILE * fout = NULL;
   getFname(firstName, (sizeof(firstName)-1));

   getLname(lastName, (sizeof(lastName)-1));
   
   num1 = getNum();

   num2 = getNum();

   getFin(finName, (sizeof(finName)-1));

   getFout(foutName, finName, (sizeof(foutName)-1));

   verifyHashes();
   fout = fopen(foutName, "w");
   fprintf(fout, "First Name: %s\nLast Name: %s\nnum1+num2: %li\nnum1*num2: %li\n", firstName, lastName, (num1+num2), (num1*num2));
   fclose(fout);
   writeToFile(finName, foutName);
   
   return 0;
}
