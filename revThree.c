#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/* THINGS TO ADD


*/

//begin definitions
//var definitions
#define SIZE 9 //size of numbers/rows/cols
#define RESET 0 //reset to zero
#define FILENAME "puzzle.txt"

//function definitions
int solvePuzzle();
int findEmpty();
int isSafe();
void printPuzzle();

//global vars
int row, col = 0;
long int totalNum = 0;
int puzzle[SIZE][SIZE];

//end definitions

/* This function asks users if they wish to change the file before solving.
   It then asks if the user wishes to solve the current puzzle after review.
   Then, it runs the functions below it to solve the puzzle
*/
int main(){

  //begin vars
  int r, c; //rows / columns
  FILE *fr; //file read
  int solution = 0; //var used to solve
  int change; //var to change puzzle
  int solve; //variable to ask users if they wish to solve
  double spentTime = 0.0; //var for time spent, used for debug
  //end vars

  //open file
  fr = fopen(FILENAME, "r");
  if (fr == NULL){
    printf("Error, can not open %s.\n", FILENAME);
    exit(EXIT_FAILURE);
  }
  for (r=0; r<SIZE; r++){
    for(c=0; c<SIZE; c++){
      fscanf(fr, "%d", &puzzle[r][c]);
    }
  }
  fclose(fr);
  //close file

  printf("The current puzzle is: \n\n");
  printPuzzle(); //print current puzzle out
  printf("Would you like to make changes to the puzzle (1 for YES, 2 for NO)? ");
  scanf("%d", &change); //store input
  if(change==1){ //do users wish to change?
    system("open puzzle.txt"); //opens the puzzle document
    printf("Please save and close the puzzle window!\n");
    printf("Please restart the program to update me!\n");
    exit(0); //exits program
  }
  else if(change == 2){ //
    printf("No changes made! \n");
  }
  else{
    printf("Please enter a valid choice. ");
  }
  printf("Would you like me to solve (1 for YES, 2 for NO)? ");
  scanf("%d", &solve); //scans if users wish to solve
  clock_t begin = clock(); //begin clock, used to time completion
  if(solve == 1){ //if yes
    solution = solvePuzzle(); //solve puzzle using function solvePuzzle
    if(solution){ // if solution exists
      printf("The solution to this puzzle is: \n\n");
      printPuzzle(); //print the solved puzzle
    }
    else{ //if the solution does not exist
      printf("There is no solution to this puzzle. Sorry!\n"); //print DNE
    }
  }
  else if (solve == 2){ //if users do not wish to sove
    printf("No problem, you may change the puzzle in");
    printf("the \"PUZZLE\" section of the code\n");
  }
  else{ //error cases
    printf("Please enter a valid option.\n"); //please enter a valid value
  }
  clock_t end = clock();
  spentTime += (double) (end - begin) / CLOCKS_PER_SEC;
  if (solve == 1){
  printf("It took me %.5f milliseconds to complete the puzzle.\n",spentTime*1000);
}
  printf("Thank you, goodbye!\n"); //thanks users
  return 0;
}

/*
This function prints the sudoku puzzle out
*/
void printPuzzle(){
  int i, j;
  printf("\t-------------------------\n"); //print top line of box
  for (i=0; i<SIZE; i++){ //for each row
    printf("\t"); // tab the box in
    for (j=0; j<SIZE; j++){ //for each col
        if(j==0){ //at first entry print a | to make box
          printf("| ");
        }
        if(puzzle[i][j] == 0){ //if the value is blank (0), print a "."
          printf(". ");
        }
        else{ //otherwise, print the value
          printf("%d ", puzzle[i][j]);
        }
        if((j+1) % 3 == 0){ //to break the square up into 3x3
          printf("| ");
        }
      }
        if((i+1) % 3 ==0){ //to break the square up into 3x3
          printf("\n\t-------------------------");
        }
        printf("\n");
    }
  }
//end printPuzzle

/*
This function checks if all cells are assigned
If there are unassigned cells, it changes the values
of row and col accordingly.
*/
int findEmpty(){
  int i, j;
  for (i=row; i<SIZE;i++){ //loop through rows
    for(j=0; j<SIZE; j++){ //loop through cols
      if (puzzle[i][j] == 0){ //is the value equal to zero (blank)
        row = i; //mark blank
        col = j; //mark blank
        return 1;
      }
    }
  }
  return 0;
}
//end findEmpty

/*
This function checks if the value is safe to add into the PUZZLE
if it is the same, it will reset and send check another digit
*/
int isSafe(int r, int c, int n){
  int i, j, beginRow, beginCol;
  //break into 3x3
  beginRow = (r/3)*3;
  beginCol = (c/3)*3;
  //printf("BeginRow: %d, BeginCol: %d\n", beginRow, beginCol);

  for (j=0; j<SIZE; j++){ //check the row
    if(puzzle[r][j] == n){ //if the cell has the same value as another
      return 0; //return a 0, send reset
    }
    if(puzzle[j][c] == n){ //if the cell has the same value as another
      return 0; //return a 0, send reset
    }
  }
  //for the 3x3
  for(i=beginRow; i<=beginRow+2; i++){  //check row
    for(j=beginCol; j<=beginCol+2;j++){ //check col
      /*printf("Row: %d, Col: %d   ", i, j);
      printf("%d = ",puzzle[i][j]);
      printf("%d\n",n);*/
      if(puzzle[i][j] == n){ //if the cell has the same value as another
        return 0; //return a 0, send reset
      }
    }
  }
  return 1; //otherwise return 1
}
//end isSafe

/*
This function uses backtracking
to solve the Sudoku puzzle
*/
int solvePuzzle() {
  int digit, prevRow, prevCol; //vars
  totalNum++; //for debug
  if(!findEmpty()){ //if sudoku is full, end
    return 1;
  }
  for(digit = 1; digit<=SIZE; digit++){ //enters digits 1-9
    if (isSafe(row, col, digit)){ //if we can assign the digit
      puzzle[row][col] = digit; //assign it
      prevRow = row; //setup backtrack
      prevCol = col; //setup backtrack
      if(solvePuzzle()){ //complete?
        return 1;} //yes, end
      //if not:
      puzzle[row][col] = 0; //set back to zero
      row = prevRow; //backtrack
      col = prevCol; //backtrack
      puzzle[row][col] = RESET; //reset and try again
    }
  }
  return 0;
}
//end solvePuzzle
