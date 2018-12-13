/* question 1: Is it a palindrome?*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 100
#define DELIMITERS " .,;:?!/"
int main (void)
{
  char inputString[MAXLENGTH];
  char text[MAXLENGTH];
  char reverseString[MAXLENGTH];
  int i, j, k;
  int len;
  int palindrome;


  printf("Please enter a word or phrase without punctuation:");
  gets(inputString);
  len = strlen(inputString);
  strcpy(text, inputString); // copy input string
  for (i=0, j=0; i<len; i++){ //loop to remove spaces
    if (text[i] == ' '){ //if there is a space
      for(j=i; j<len; j++){ //move forward
        text[j] = text[j+1];
      }
      len--; //take one off of the string length
    }
  }
  for (i=0, j=0; i<len; i++){ //loop to remove punctuation
    if ((text[i] == ',') || (text[i] == '.') || (text[i] == '!') || (text[i] == '?')){
      for(j=i; j<len; j++){ //if one of those chars, move ahead
        text[j] = text[j+1];
      }
      len--; //take one off strlen
    }
  }
  //printf("No spaces: %s", text);
  for(i=0;(text[i] = (char)tolower(text[i]))!=0; ++i); //change text to all lowercase
  for(i=0; i<strlen(text); i++) //reverseString
  {
    reverseString[strlen(text)-i-1]=text[i];
  }
  reverseString[strlen(text)]='\0';

  printf("Original String: %s\n\n",inputString);
  printf("Filtered String: %s\n", text);
  printf("Reversed String: %s\n",reverseString);

  palindrome=strcmp(text, reverseString);
  if(palindrome==0)
  {
    printf("That is a palindrome!\n");
  }
  else
  {
    printf("That is not a palindrome.\n");
  }

  return 0;
}
