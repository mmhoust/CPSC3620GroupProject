/* Matthew Houst
   serial Brute force sudoku solver
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// these functions check for valid row,column, and box respectively
int checkRow(int **grid,int row);
int checkColumn(int **grid,int col);
int checkBox(int **grid,int box);
int checkGrid(int **grid);
void printGrid(int **grid);

#define rowSize 9
#define colSize 9
#define numBoxes 9

int main(int argc, char**argv){
	// input grid from file, arg 1
	// allocate memory for grid using double pointer 
	int **grid = (int **)malloc(rowSize*sizeof(int *));
	int **origGrid = (int **)malloc(rowSize*sizeof(int *));
	for(int i=0; i<rowSize; i++){
		grid[i] = (int *)malloc(colSize*sizeof(int));
		origGrid[i] = (int *)malloc(colSize*sizeof(int));
	}
	FILE *fp;
	char buf[81];
	fp = fopen(argv[1],"r");
	int row = 0;
	while(fgets(buf,sizeof(buf),fp)){
		int i = 0;
		printf("%s\n",buf);
		while(buf[i] != '\0'){
			grid[row][i] = buf[i] - '0';
			origGrid[row][i] = buf[i] - '0';
			i++;
		}
		row++;
	}
	fclose(fp);
	// brute force algorithm
	int rowPos = 0;
	int colPos =0;
	while(colPos < 9 && rowPos < 9){
		if(origGrid[rowPos][colPos] == 0){
			grid[rowPos][colPos]++;
			if(checkGrid(grid) != 0){
				if(grid[rowPos][colPos] > 9){
					grid[rowPos][colPos] = 0;
					colPos--;
					if(colPos < 0){
						colPos = 8;
						rowPos--;
					}	
				}
				continue;
			}
		}
		colPos++;
		if(colPos >= 9){
			colPos = 0;
			rowPos++;
		}
	}

	printGrid(grid);

	// free grid
	for(int i = 0; i<rowSize; i++){
		free(grid[i]);
		free(origGrid[i]);
	}
	free(grid);
	free(origGrid);

}

void printGrid(int **grid){
	for(int i = 0; i < rowSize; i++){
		for(int j =0; j < colSize; j++){
			printf("%d",grid[i][j]);
		}
		printf("\n");
	}
}

int checkRow(int **grid,int row){
	int countArray[rowSize] = {0};
	for(int i =0; i<rowSize; i++){
		countArray[grid[row][i]]++;
	}
	for(int i =0; i<rowSize; i++){
		if(countArray[i] > 1){
			return 1;
		}
	}
	return 0;
}
int checkColumn(int **grid,int col){
	int countArray[colSize] = {0};
	memset(countArray,0,9*sizeof(int));
	for(int i =0; i<colSize; i++){
		countArray[grid[i][col]]++;
	}
	for(int i =0; i<colSize; i++){
		if(countArray[i] > 1){
			return 1;
		}
	}
	return 0;
}
int checkBox(int **grid,int box){
	int countArray[numBoxes] = {0};
	int rowOffset = (box/3) * 3;
	int colOffset = (box%3) * 3;
	for(int i =0; i< 3; i++){
		for(int j = 0; j <3; j++){
			countArray[grid[rowOffset+i][colOffset+j]]++;
		}
	}
	for(int i = 0; i < 3; i++){
		if(countArray[i] > 1){
			return 1;
		}
	}
	return 0;
}

int checkGrid(int **grid){
	for(int i = 0; i < 9; i++){
		if(checkRow(grid,i) != 0 || checkColumn(grid,i) != 0 || checkBox(grid,i) != 0){
			return 1;
		}
	}
	return 0;
}

