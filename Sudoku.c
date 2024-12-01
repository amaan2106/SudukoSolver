/**
 * Exercise 11 - Simple Sudoku Solver
 *
 * Please read the comments below carefully, they describe your task in detail.
 * Any clarifications and corrections will be posted to Piazza so please keep
 * an eye on the forum!
 *
 * Starter code: Mustafa Quraish, 2020
 */

#include <stdio.h>

#ifndef __testing__
/**
 * Prints out the sudoku in an easy-to-view format. Feel free to change
 * this function if you need to help you debug.
 */
void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  printf("+-------+-------+-------+\n");
  for (int j = 0; j < 9; j++)
  {
    printf("| ");
    for (int i = 0; i < 9; i++)
    {
      printf("%d ", sudoku[j][i]);
      if (i % 3 == 2)
        printf("| ");
    }
    printf("\n");
    if (j % 3 == 2)
      printf("+-------+-------+-------+\n");
  }
}
#endif

/*****************************************************************************/

/**
 * This function checks if the current sudoku grid (not necessarily
 * complete) is valid. This means that (ignoring the 0s), each row, column
 * and 3x3 subgrid should not repeat any digits 1-9.
 *
 * Returns 1 if the sudoku is valid, or 0 if it's not.
 */

int is_valid_row(int sudoku[9][9]){
  int list[10] = {0};
  for(int j = 0; j < 9; j++){
    for (int i = 0; i  < 9; i++){
      list[sudoku[i][j]]++;
    }
    for(int k = 1; k < 10; k++){
      if(list[k] > 1){
        return 0;
        }
      list[k] = 0;
      }
    }
    return 1;
  }




int is_valid_column(int sudoku[9][9]){
  int list[10] = {0};
  for(int j = 0; j < 9; j++){
    for(int i = 0; i < 9; i++){
      list[sudoku[j][i]] = list[sudoku[j][i]] + 1;
    }
    for (int k = 1; k < 10; k++){
      if (list[k] > 1){
        return 0;
      }
      list[k] = 0;
    }
  }
  return 1;
}

int is_valid_3by3(int sudoku[9][9]){
  int c[10] = {0};
  for(int num = 0; num < 9; num = num + 3){  // this checks each box below
    for(int undernum = 0; undernum < 9; undernum = undernum + 3){ //this checks each box beside
      for(int i = num; i < num + 3; i++){
        for(int j = undernum; j < undernum + 3; j++){
          c[sudoku[i][j]] = c[sudoku[i][j]] + 1;
        }
      }
      for(int k = 1; k <= 9; k++){
        if(c[k] > 1){
          return 0;
        }
      c[k] = 0;
      }
    }
  }
  return 1;

}

int is_valid_sudoku(int sudoku[9][9])
{
  //base case probs multiple

  //recursive case
  if(is_valid_row(sudoku) == 0 || is_valid_3by3(sudoku) == 0 || is_valid_column(sudoku) == 0){
    return 0;
  }else{
    return 1;
  }
}



/**
 * Given a (possibly partially) completed sudoku grid, try and solve the
 * sudoku. The `sudoku` array should be changed to contain the solution if
 * one exists. None of digits in the input grid should be changed.
 * 
 * NOTE: The empty spots are denoted with 0s in them.
 *
 * Refer to the handout for more discussion on how to implement this.
 *
 * Return 1 if the sudoku was solved, and update the `sudoku` parameter.
 * Return 0 if it's not possible to solve the sudoku, and leave the input
 *    `sudoku` array unchanged in this case.
 */

int check(int sudoku[9][9], int num, int row, int column){
  for (int i = 0; i < 9; i++){
    if(num == sudoku[i][column]){
      return 0;
    }
  }
  for (int i = 0; i < 9; i++){
      if(num == sudoku[row][i]){
      return 0;
    }
  }
    int begofrow = row - row % 3;
    int begofcolumn = column - column % 3;
   
    for (int i = 0; i < 3; i++){
    
        for (int j = 0; j < 3; j++){
        
            if (sudoku[i + begofrow][j + begofcolumn] == num){

                return 0;
            }
        }
    }
    return 1;
}


int solveSudoku(int sudoku[9][9], int i, int j)
{
    if (i == 8 && j == 9){ //base case
        return 1;
    }
    if (j == 9){
        i = i + 1;
        j = 0;
    }
    if (sudoku[i][j] != 0){
        return solveSudoku(sudoku, i, j + 1);
    }
 
    for (int k = 1; k <= 9; k++){
        if (check(sudoku, k, i, j) == 1){
            sudoku[i][j] = k;
            if (solveSudoku(sudoku, i, j + 1) == 1){
                return 1;
            }
        }
      sudoku[i][j] = 0;
    }
    return 0;
}


int solve_sudoku(int sudoku[9][9])
{
  return solveSudoku(sudoku, 0, 0);
}


#ifndef __testing__

int main()
{
  /**
   * This example is the one from the Wiki, but your solution should be able
   * to handle any solvable sudoku. The time to solve different puzzles may
   * vary, but ideally it should not take more than a second for this one.
   */

  int sudoku_grid[9][9] = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0},
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};


  print_sudoku(sudoku_grid);

  int isvalid = is_valid_sudoku(sudoku_grid);

  int solved = solve_sudoku(sudoku_grid);


  printf("\nsolve_sudoku() return value: %d\n\n", solved);

  /* Look at the handout to see the solution for this! */
  print_sudoku(sudoku_grid);

  return 0;
}

#endif