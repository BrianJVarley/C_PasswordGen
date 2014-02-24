// G00290342PasswordGen.cpp : main project file.

/*Brian Varley-G00290342// Procedural programming project
*Program to generate a password and also allow user to input a password that will be validated.

*Password rules:

1. Passwords must be at least 9 characters long and less than 15 characters.
2. Passwords must have at least 2 numbers in them.
3. Passwords must have at least 2 uppercase letters and 2 lowercase letters in them.
4. Passwords must have at least 1 symbol in them (eg ?, $, £, %). You may define a set of
acceptable symbols to use.
5. Passwords may not have small, common words in them eg hat, pow or ate. You should
create a dictionary file that can be used to check the passwords. This can be a plain text file.
6. You should maintain a history of checked passwords and generated passwords to ensure
that they are not used twice in the system. This can be done in a text file as well.

*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <string.h>
#include <time.h>

//Constants here:
#define MAX 30
#define gC_FOUND 99
#define gC_NOT_FOUND -99





using namespace std;



//declaring functions:
int showMenu();		
void generatePass();	
void validatePass();
int countLetters(char *,int *,int *,int *,int *,int *);
int checkWordInFile(char * fileName,char * theWord);




int main()
{

	int iChoice;
	
	// have menu appear, user makes decision, do work, reshow menu
	// do this until user enters 5

	do
	{

		iChoice = showMenu();


	}while(iChoice != 3);

	printf("\n\n\n");
	system("pause");


}//end of main

//Methods placed here:

//showMenu method calls program menu,either 1.generate password,2.enter password and validate. or 3.exit(close program)
int showMenu()
{
	int iChoice;

	system("cls");
	printf("\n\n\t\tWelcome to Password Generator and Validator\n\n");
	printf("\n\t\t1. Generate");
	printf("\n\t\t2. Validate");
	printf("\n\t\t3. Exit");
	
	printf("\n\n\t\tEnter your menu choice: ");
	fflush(stdin);
	scanf_s("%d", &iChoice);

	// user enters one of 3 values
	// generate,validate or exit program
	

	switch(iChoice)
	{
		case 1:		// generate
		{
			generatePass();
			
			break;
		}
		case 2:		// validate
		{
			validatePass();


			break;
		}
		case 3:		// exit
		{
			printf("\n\nProgram exiting!...");
			exit(0);//terminates program
			
			break;
		}
		default:
		{
			break;
		}
	}//end of switch


	return(iChoice);
} //end of showMenu


static bool verifyThat(bool condition, const char* error) {
    if(!condition) printf("%s", error);
    return !condition;
}




//method to generate a random password for user following password guidelines.  
void generatePass()

{
	FILE *fptr;//file pointer
	int iChar,iUpper,iLower,iSymbol,iNumber,iTotal;

	
	printf("\n\n\t\tGenerate Password selected ");

	get_user_password:
	printf("\n\n\t\tPassword creation in progress... ");

	int i,iResult,iCount;
	char password[10 + 1];
	char strLower[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRTUVWXYZ!£$%^&*0123456789";

	srand(time (0));

	for(i = 0; i < 10;i++)
	{
		password[i] = strLower[(rand() % (sizeof(strLower) / sizeof(char) - 1))];

	}
	password[i] = '\0';    

	iChar = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);

	//folowing statements used to validate password
	iChar = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
	iUpper = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iLower =countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iSymbol =countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iNumber = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iTotal = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
	

	
	if(verifyThat(iUpper >= 2, "Not enough uppercase letters!!!\n")
     || verifyThat(iLower >= 2, "Not enough lowercase letters!!!\n")
     || verifyThat(iSymbol >= 1, "Not enough symbols!!!\n")
     || verifyThat(iNumber >= 2, "Not enough numbers!!!\n")
     || verifyThat(iTotal >= 9, "Not enough characters!!!\n")
     || verifyThat(iTotal <= 15, "Too many characters!!!\n"))

	goto get_user_password;

    iResult = checkWordInFile("dictionary.txt", password);

    if(verifyThat(iResult != gC_FOUND, "Password contains small common 3 letter word/s."))
    goto get_user_password;
	
    iResult = checkWordInFile("passHistory.txt",password);

    if(verifyThat(iResult != gC_FOUND, "Password contains previously used password."))
    goto get_user_password;
	 
	
	printf("\n\n\n Your new password is verified ");
	printf(password);
	
	//writing password to passHistroy file.

	
	//fptr = fopen("passHistory.txt", "w");	// create or open the file
	fptr = fopen("passHistory.txt", "a");	// create or open the file
	//"w" deletes file if not empty. You should use "a" for append (http://www.cplusplus.com/reference/cstdio/fopen/)
	/*for( iCount = 0; iCount < 8; iCount++)
	{ 
		//%s stands for string (char array), but password[iCount] is a char (the iCount-th char of the char array. Use %c. But here, you write first 8 letters
		//fprintf(fptr, "%s\n", password[iCount]);
		fprintf(fptr, "%c", password[iCount]);
	}
	fprintf(fptr, "\n");	//add a carriage return after first 8 characters
	*/
	//You can also use this the whole 10 characters to your file.
	fprintf(fptr, "%s\n", password);

	fclose(fptr);


	printf("\n\n\n");
	system("pause");

	

}//end of generatePass method.




static bool certifyThat(bool condition, const char* error) {
    if(!condition) printf("%s", error);
    return !condition;
}

//method to validate a user generated password following password guidelines.
void validatePass()
{
	FILE *fptr;
	char password[MAX+1];
	int iChar,iUpper,iLower,iSymbol,iNumber,iTotal,iResult,iCount;
	


	//shows user password guidelines
	printf("\n\n\t\tPassword rules: ");
	printf("\n\n\t\t 1. Passwords must be at least 9 characters long and less than 15 characters. ");
	printf("\n\n\t\t 2. Passwords must have at least 2 numbers in them.");
	printf("\n\n\t\t 3. Passwords must have at least 2 uppercase letters and 2 lowercase letters in them.");
	printf("\n\n\t\t 4. Passwords must have at least 1 symbol in them (eg ?, $, £, %).");
	printf("\n\n\t\t 5. Passwords may not have small, common words in them eg hat, pow or ate.");

	//gets user password input
	get_user_password:

	printf("\n\n\t\tEnter your password following password rules: ");
	scanf("%s", &password);


	iChar = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
	iUpper = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iLower =countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iSymbol =countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iNumber = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
    iTotal = countLetters(password,&iUpper,&iLower,&iSymbol,&iNumber,&iTotal);
	

	
	if(certifyThat(iUpper >= 2, "Not enough uppercase letters!!!\n")
     || certifyThat(iLower >= 2, "Not enough lowercase letters!!!\n")
     || certifyThat(iSymbol >= 1, "Not enough symbols!!!\n")
     || certifyThat(iNumber >= 2, "Not enough numbers!!!\n")
     || certifyThat(iTotal >= 9, "Not enough characters!!!\n")
     || certifyThat(iTotal <= 15, "Too many characters!!!\n"))

	goto get_user_password;

    iResult = checkWordInFile("dictionary.txt", password);

    if(certifyThat(iResult != gC_FOUND, "Password contains small common 3 letter word/s."))
    goto get_user_password;
	
    iResult = checkWordInFile("passHistory.txt",password);

    if(certifyThat(iResult != gC_FOUND, "Password contains previously used password."))
    goto get_user_password;
	 
	
	printf("\n\n\n Your new password is verified ");
	printf(password);
	
	//writing password to passHistroy file.

	
	//fptr = fopen("passHistory.txt", "w");	// create or open the file
	fptr = fopen("passHistory.txt", "a");	// create or open the file
	//"w" deletes file if not empty. You should use "a" for append (http://www.cplusplus.com/reference/cstdio/fopen/)
	/*for( iCount = 0; iCount < 8; iCount++)
	{ 
		//%s stands for string (char array), but password[iCount] is a char (the iCount-th char of the char array. Use %c. But here, you write first 8 letters
		//fprintf(fptr, "%s\n", password[iCount]);
		fprintf(fptr, "%c", password[iCount]);
	}
	fprintf(fptr, "\n");	//add a carriage return after first 8 characters
	*/
	//You can also use this the whole 10 characters to your file.
	fprintf(fptr, "%s\n", password);

	fclose(fptr);

	printf("\n\n\n");
	system("pause");


}//end validatePass method

int countLetters(char *	Password,int * Upper,int * Lower,int * Symbol,int * Number,int * Total)
{
	int iTotal = 0,iC = 0,tU = 0,tL = 0,tS = 0,tN = 0;
	

	//strlen- function that returns length
	for (int iC = 0;iC < strlen(Password);iC++)
	{

		printf("%d",Password[iC]);
		//uppercase letters are in the range 65 - 90
		//lowercase letters are in the range 97 - 122
		//symbols are in the range 32-48
		//numbers are in the range 47 - 58
		

		if((Password[iC] > 64) && (Password[iC] < 91))
		{
			tU++;
			iTotal++;
		
		}
		else if((Password[iC] > 96) && (Password[iC] < 123))
		{
			tL++;
			iTotal++;
		
		}
		else if((Password[iC] > 32) && (Password[iC] < 48))
		{
			tS++;
			iTotal++;
		
		}
		else if((Password[iC] > 47) && (Password[iC] < 58))
		{
			tN++;
			iTotal++;
		
		}
	
		*Upper = tU;/*set value at memory address = tU,passing by reference saves memory used.*/
		*Lower = tL;
		*Symbol = tS;
		*Number = tN;
		

	}//end for statement

	
	return (iTotal);
}//end of countLetters

int checkWordInFile(char * fileName,char * theWord){

    FILE * fptr;
    char fileString[MAX + 1];
    //int iFound = -99;
    int iFound=gC_NOT_FOUND;
    //open the file
    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("\nNo dictionary file\n");
        printf("\n\n\n");
        system("pause");
        return (0); // just exit the function
    }

    /* read the contents of the file */
    while( fgets(fileString, MAX, fptr) )
    {
		//remove ending carriage return
		fileString[strlen(fileString)-1]='\0';
        //if( 0 == strcmp(theWord, fileString) )	//here you match for the entire line, you want ti see if there is 'pow' in your password for example
		if( strstr(theWord, fileString) !=NULL )
        {
            //iFound = -99;
			iFound = gC_FOUND;
        }
    }

    fclose(fptr);

    //return(0);
    return(iFound); //return whether we found the file or not



}//end of checkwORDiNFile










