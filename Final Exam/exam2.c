#include <stdio.h>

int main() {

	int numRows, spaceCounter, asteriskCounter, rowCounter, numSpaces;

	printf("How many rows do you want in your diamond?");
	scanf("%d", &numRows);

	// Print first half of the triangle.
	numSpaces = numRows - 1;
	for ( rowCounter = 1 ; rowCounter <= numRows ; rowCounter++ ) {
		for ( spaceCounter = 1 ; spaceCounter <= numSpaces ; spaceCounter++ )
			printf(" "); //Only this line is inside the inner for loop.
		numSpaces--;        //Next row will have one less space
		for ( asteriskCounter = 1 ; asteriskCounter <= 2*rowCounter-1 ; asteriskCounter++)
			printf("*");
		printf("\n");
	}
  numSpaces = 1;
  for ( rowCounter = 1 ; rowCounter <= numRows-1 ; rowCounter++ ) {
    for ( spaceCounter = 1 ; spaceCounter <= numSpaces ; spaceCounter++ )
      printf(" "); //Only this line is inside the inner for loop.
    numSpaces++;        //Next row will have one less space
    for ( asteriskCounter = 1 ; asteriskCounter <= 2*(numRows -rowCounter)-1 ; asteriskCounter++)
      printf("*");
    printf("\n");
  }

	// Print second half of the triangle.

}
