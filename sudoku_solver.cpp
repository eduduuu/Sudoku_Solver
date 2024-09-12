#include <iostream>
#include <bits/stdc++.h>
#include<cmath>
#define NUMBER_CELLS 9*9
#define NUMBERS 9
#define SQRT 3

using namespace std;

// information relative to a cell
struct group {
    int line, column, square;
};

vector<int> sudoku[NUMBER_CELLS]; // adjacency list
vector<int> line[NUMBERS], column[NUMBERS], square[NUMBERS]; // each array have the index of elements in respective line, ...
struct group groups[NUMBER_CELLS]; // array with all the cells

// set the arrays above
void setThings() {
    for (int i = 0; i < NUMBERS; i++) {
        for (int j = 0; j < NUMBERS; j++) {
            line[i].push_back(i*NUMBERS + j);
            column[j].push_back(i*NUMBERS + j);
            square[SQRT*((int) floor(i/SQRT)) + (int) floor(j/SQRT)].push_back(i*NUMBERS + j);
            groups[(i*NUMBERS + j)] = {i, j, SQRT*((int) floor(i/SQRT)) + (int) floor(j/SQRT)};
        }
    }

    // first include the elements in the same square, then checks if the elements in the column and line
    // have not been include and include them or not
    for (int i = 0; i < NUMBER_CELLS; i++) {
        for (int j = 0; j < NUMBERS; j++) 
            if (square[groups[i].square][j] != i)
                sudoku[i].push_back(square[groups[i].square][j]);
        for (int j = 0; j < NUMBERS; j++) 
            if (line[groups[i].line][j] != i && groups[line[groups[i].line][j]].square != groups[i].square)
                sudoku[i].push_back(line[groups[i].line][j]);
        for (int j = 0; j < NUMBERS; j++) 
            if (column[groups[i].column][j] != i && groups[column[groups[i].column][j]].square != groups[i].square &&
                groups[column[groups[i].column][j]].line != groups[i].line)
                    sudoku[i].push_back(column[groups[i].column][j]);
    }
}

// prints the solution
void print(int numbers[]) {
    for (int i = 0; i < NUMBER_CELLS; i++) {
        if (i % NUMBERS == 0) cout << "\n";
        cout << numbers[i] << " ";
    }
    
}

// checks if a number is possible for a cell
bool isPossible(vector<int> graph[], int node, int numbers[], int n) {
    for (int i : graph[node]) 
        if (numbers[i] == n) 
            return false;
    return true;
}

// backtraking of the possibilities. It stops when the first is found
bool graphColoring(vector<int> graph[], int k, int numbers[], int node) {
    if (node == NUMBER_CELLS) return true; // return if all cells have a number

    // for all numbers, test if it is possible, if so, try it on the backtraking
    for (int i = 1; i <= k; i++) {
        if (numbers[node] == 0) {
            if(!isPossible(graph, node, numbers, i)) continue;
            
            numbers[node] = i;
            if (graphColoring(graph, k, numbers, node+1))
                return true;
            
            numbers[node] = 0;
        }
        else {
            // it will enter here, if the cell has a preset number
            if (graphColoring(graph, k, numbers, node+1))
                return true;
        }
    }

    return false;
}


int main () {
    // set all numbers as 0
    int numbers[NUMBER_CELLS];
    for (int i = 0; i < NUMBER_CELLS; i++) 
        numbers[i] = 0;
    
    setThings();

    // if you want to set some cells with a number before find the solution
    // write: "numbers[i] = n;" where i is the index of the cell
    // conting from left to right, up to bottom, starting with 0 and n is the number. 

    // print the numbers if a solution was find
    if (graphColoring(sudoku, NUMBERS, numbers, 0))
        print(numbers);

    return 0;
}