#include "myUtils.h"

/**
 * This is a small method to strip carriage returns for user input.
 */
void strip(char *array)
{
   int len;
   int x;
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}
	len = strlen(array);
    x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';
	  x++;

   }
}

/**
 * This method uses a regex to verify that the user gave a valid integer as input
 * and is within the size of a max integer.
 * @return 0 for success, -1 for failure.
 */
int isValidInt(char * num)
{
   regex_t regex;
   int result = 0;
   long theNum = 0;
   long max;
   long min;
   result = regcomp(&regex, "^[\\-]?([0-9]{1,10})$", REG_EXTENDED);
   if(result)
   {
      regfree(&regex);
      printf("Regex failed to compile\n");
      return -1;
   }
   result = regexec(&regex, num, 0, NULL, 0);
   if(result == 0)
   {
      theNum = atol(num);
      max = 2147483648;
      min = -2147483648;
      if(theNum > min && theNum < max)
      {
         regfree(&regex);
         return 0;
      }
      else
      {
         regfree(&regex);
         printf("Invalid input\n");
         return -1;
      }
   }
   else if(result == REG_NOMATCH)
   {
      regfree(&regex);
      printf("Invalid input\n");
      return -1;
   }
   else
   {
      regfree(&regex);
      printf("Regex execution returned invalid result\n");
      return -1;
   }
}

/**
 * This method prompts the user for an integer, strips the input, then validates
 * the input with isValidInt().
 * @return the number input by the user
 */
long getNum()
{
   int valid;
   long num;
   char buf[15];
   valid = -1;
   while(valid != 0)
   {
      printf("Enter an int (between -2147483647 and 2147483647)\n");
      fgets(buf, (sizeof(buf)-1), stdin);
      strip(buf);
      stdin = freopen(NULL, "r", stdin);
      valid = isValidInt(buf);
      if(valid == 0)
         num = atol(buf);
   }
   return num;
}

/**
 * This method prompts the user for a first name (up to 50 characters), strips the input,
 * and validates that the user entered a valid name with isValidName()
 * After validation, the name is copied into the passed in char pointer for the first name
 * back in main memory.
 */
void getFname(char * fname, size_t len)
{
   int valid;
   char buf[55];
   char fName[51];
   valid = -1;
   while(valid !=0)
   {
      printf("Enter first name (Up to 50 characters.\nCannot contain numbers or symbols other than: - or ')\n");
      fgets(buf, (sizeof(buf)-1), stdin);
      strip(buf);
      stdin = freopen(NULL, "r", stdin);
      valid = isValidName(buf);
      if(valid == 0)
         strncpy(fName, buf, (sizeof(fName)-1));
   }
   strncpy(fname, fName, len);
}

/**
 * This method prompts the user for a last name (up to 50 characters), strips the input,
 * and validates that the user entered a valid name with isValidName()
 * After validation, the name is copied into the passed in char pointer for the last name
 * back in main memory.
 */
void getLname(char * lname, size_t len)
{
   int valid;
   char buf[55];
   char lName[51];
   valid = -1;
   while(valid != 0)
   {
      printf("Enter last name (Up to 50 characters.\nCannot contain numbers or symbols other than: - or ')\n");
      fgets(buf, (sizeof(buf)-1), stdin);
      strip(buf);
      stdin = freopen(NULL, "r", stdin);
      valid = isValidName(buf);
      if(valid == 0)
         strncpy(lName, buf, (sizeof(lName)-1));
   }
   strncpy(lname, lName, len);
}

/**
 * This method uses a regex to verify that the user gave a valid name as input
 * @return 0 for success, -1 for failure.
 */
int isValidName(char * name)
{
   regex_t regex;
   int result;
   result = regcomp(&regex, "^([a-z]|[A-Z]|[\\-]){1,50}$", REG_EXTENDED);
   if(result)
   {
      regfree(&regex);
      printf("Regex failed to compile\n");
      return -1;
   }
   result = regexec(&regex, name, 0, NULL, 0);
   if(result == 0)
   {
      regfree(&regex);
      return 0;
   }
   else if(result == REG_NOMATCH)
   {
      regfree(&regex);
      printf("Invalid input\n");
      return -1;
   }
   else
   {
      regfree(&regex);
      printf("Regex execution returned invalid result\n");
      return -1;
   }
}

/**
* This method utilizes a regex to determine whether the user input is in the format of a file
* name.
* @return 0 for success, -1 for failure.
*/
int isValidFile(char * file)
{
   regex_t regex;
   int result;
   result = regcomp(&regex, "^(([a-z]|[A-Z]|[0-9]){1,47}.txt|([a-z]|[A-Z]|[0-9]){1,49}.c|([a-z]|[A-Z]|[0-9]){1,46}.java)$", REG_EXTENDED);
   if(result)
   {
      regfree(&regex);
      printf("Regex failed to compile\n");
      return -1;
   }
   result = regexec(&regex, file, 0, NULL, 0);
   if(result == 0)
   {
      regfree(&regex);
      return 0;
   }
   else if(result == REG_NOMATCH)
   {
      regfree(&regex);
      printf("Invalid input\n");
      return -1;
   }
   else
   {
      regfree(&regex);
      printf("Regex execution returned invalid result\n");
      return -1;
   }
}

/**
 * This method prompts the user for a file name to open as an input file,
 * checks to ensure the user has not entered main.c, myUtils.c, or passwords.txt
 * After checking that one of these files has not been entered, we strip the input
 * and send it to isValidFile() to validate the input is in the correct format with a regex.
 * After validation we check that the input file can be opened. Afterwards we close the file,
 * and then we assign the final String input into the char * passed in back in main memory.
 */
void getFin(char * finFinal, size_t len)
{
   int valid;
   char buf[55];
   char finName[51];
   FILE * fin;
   valid = -1;
   while(valid != 0)
   {
      printf("Enter input file (Must exist in the current directory.\n Must be different than output file, and cannot main.c, myUtils.c, or password.txt. \nUp to 50 characters, must be a .java, .c, or .txt file)\n");
      fgets(buf, (sizeof(buf)-1), stdin);
      strip(buf);
      stdin = freopen(NULL, "r", stdin);
      valid = isValidFile(buf);
      if(valid == 0)
      {
         if(strcmp(buf, "main.c") == 0 || strcmp(buf, "myUtils.c") == 0 || strcmp(buf, "password.txt") == 0)
         {
            printf("Input file cannot be main.c, myUtils.c, or passwords.txt\n");
            valid = -1;
         }
      }
      if(valid == 0)
      {
         strncpy(finName, buf, (sizeof(finName)-1));
         fin = fopen(finName, "r");
         if(fin == NULL)
         {
            printf("Invalid input, file does not exist\n");
            valid = -1;
         }
         else
            fclose(fin);
      }
   }
   strncpy(finFinal, finName, len);
}

/**
 * This method prompts the user for a file name to open as an output file,
 * checks to ensure the user has not entered the input file name, main.c, myUtils.c, or passwords.txt
 * After checking that one of these files has not been entered, we strip the input
 * and send it to isValidFile() to validate the input is in the correct format with a regex.
 * After validation we assign the final String input into the char * passed in back in main memory.
 */
void getFout(char * fout, char * finName, size_t len)
{
   int valid;
   char buf[55];
   char foutName[51];
   valid = -1;
   while(valid != 0)
   {   
      printf("Enter output file (Must be in current directoy.\n Must be different than input file, and cannot main.c, myUtils.c, password.txt.\n Up to 50 characters, must be a .java, .c, or .txt file)\n");
      fgets(buf, sizeof(buf)-1, stdin);
      strip(buf);
      stdin = freopen(NULL, "r", stdin);
      valid = isValidFile(buf);
      if(valid == 0)
      {
         if(strcmp(buf, "main.c") == 0 || strcmp(buf, "myUtils.c") == 0 || strcmp(buf, "password.txt") == 0)
         {
            printf("Output file cannot be main.c, myUtils.c, or password.txt\n");
            valid = -1;
         }
      }
      if(valid == 0)
         strncpy(foutName, buf, (sizeof(foutName)-1));
      if(strcmp(finName, foutName) == 0)
      {
         printf("Invalid input. Output file cannot be the same as the input file.\n");
         valid = -1;
      }
      
   }
   strncpy(fout, foutName, len);
}

/**
* This method opens up the output file and we write the contents
* of the input file to the output file.
 */
void writeToFile(char * finName, char * foutName)
{
   char * argv[3];
   int myfd;
   FILE * fout = fopen(foutName, "a");
   if(fout != NULL)
   {
      myfd = fileno(fout);
      close(1);
      dup2(myfd, STDOUT_FILENO);
      fclose(fout);
      argv[0] = "cat";
      argv[1] = finName;
      argv[2] = NULL;
      execvp(argv[0], argv);
   }
   else
   {
      printf("Unable to write to file\n");
   }
}

/**
* This method prompts the user to enter a password, strips the input, uses hashedPass to 
* store the hash of the password. Then it writes that hash to passwords.txt
* Then we prompt the user to re-enter their password. We strip the input,
* read in the storedHash, and compare the re-entered password to the stored hash
* with verifyHash() which will return the original hash if the password is correct.
* Otherwise we continue to prompt until the user enters the same valid password twice.
 */
void verifyHashes()
{
   int valid;
   char buf[40];
   char pass1[33];
   char pass2[33];
   char * hash1;
   char storedHash[200];
   char * verifiedHash;
   FILE * passOut;
   FILE * passIn;
   valid = -1;
   while(valid != 0)
   {
      printf("Enter a password (Must be between 8 and 32 characters. May include numbers, uppercase, lowercase, and !,@,#,$,%%)\n");
      fgets(buf, (sizeof(buf)-1), stdin);
      strip(buf);
      stdin = freopen(NULL, "r", stdin);
      valid = isValidPassword(buf);
      if(valid == 0)
      {
         strncpy(pass1, buf, (sizeof(pass1)-1));
         hash1 = hashedPass(pass1);
         passOut = fopen("password.txt", "w");
         if(passOut != NULL)
         {
            fprintf(passOut, "%s", hash1);
   	        fclose(passOut);
         }
         printf("Please re-enter your password for verification:\n");
         fgets(buf, (sizeof(buf)-1), stdin);
         strip(buf);
         stdin = freopen(NULL, "r", stdin);
         valid = isValidPassword(buf);
         if(valid == 0)
         {
         	passIn = fopen("password.txt", "r");
         	if(passIn != NULL)
         	{
         	   fgets(storedHash, (sizeof(storedHash)-1), passIn);
         	}
            strncpy(pass2, buf, (sizeof(pass2)-1));
            verifiedHash = verifyHash(pass2, storedHash);
            if(strcmp(storedHash, verifiedHash) == 0)
            {
   	           valid = 0;
               printf("Correct password accepted\n");
            }
         	else
            {
        	   valid = -1;
               printf("Incorrect password, please try again\n");
         	}
         }
         else
         {
            valid = -1;
            printf("Second password not valid, please try again\n");
         }
      }
      else
      {
         valid = -1;
         printf("Password not valid, please try again.\n");
      }
   }
}

/**
 * This method uses a regex to verify that the user gave a valid password as input
 * and is called by VerifyHashes()
 * @return 0 for success, -1 for failure.
 */
int isValidPassword(char * password)
{
   regex_t regex;
   int result;
   result = regcomp(&regex, "^([0-9]|[a-z]|[A-Z]|[!]|[@]|[#]|[$]|[%%]){8,32}$", REG_EXTENDED);
   if(result)
   {
      regfree(&regex);
      printf("Regex failed to compile\n");
      return -1;
   }
   result = regexec(&regex, password, 0, NULL, 0);
   if(result == 0)
   {
      regfree(&regex);
      return 0;
   }
   else if(result == REG_NOMATCH)
   {
      regfree(&regex);
      printf("Invalid input\n");
      return -1;
   }
   else
   {
      regfree(&regex);
      printf("Regex execution returned invalid result\n");
      return -1;
   }
}

/**
* This method hashes the input password.
* @return the hashed password.
 */
char * hashedPass(char * password)
{
   char * coded;
   unsigned long seed[2];
   size_t myTime;
   int i;
   char salt[] = "$1$........";
   char * seedchars =
    "./0123456789ABCDEFGHIJKLMNOPQRST"
    "UVWXYZabcdefghijklmnopqrstuvwxyz";
   myTime = time(NULL);
   seed[0] = myTime;
   seed[1] = getpid() ^ (seed[0] >> 14 && 0x30000);
   for(i = 0; i < 8; i++)
      salt[3+i] = seedchars[(seed[i/5] >> (i%5)*6) & 0x3f];
   coded = crypt(password, salt);
   return coded;
}

/**
* This method takes the users input attempt for their previous password and compares it to.
* @return the same hash if the password is correct.
 */
char * verifyHash(char * password, char * hashOriginal)
{
   char * coded = crypt(password, hashOriginal);
   return coded;
}
