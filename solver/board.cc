#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "board.h"

#define EMPTY (0)
#define abs(x) ((x) >= 0 ? (x) : -1*(x))

using namespace std;

bool isValidCoor(int x, int y){
    return (x >= 0) && (x <= 8) && (y >= 0) && (y <= 8) && (y + x >= 4) && (y + x <= 12);
}

bool areNeighbors(int x, int y, int a, int b){
    int d1 = x - a;
    int d2 = y - b;
    if ((abs(d1) > 1) || (abs(d2) > 1)){
        return false; // one of them is not -1,0,1
    }
    if ((d1 == 0) || (d2 == 0)){
        if (d1 == d2){
            return false;
        }
        return true;
    }
    if (d1 * d2 == -1){
        return true; // -1 and 1
    }
    return false;
}
    
Board::Board() {
    putZeros();
}

Board::Board(const Board& b) {
    for (size_t i = 0; i < 9; i++){
        for (size_t j = 0; j < 9; j++){
            if (isValidCoor(i, j)){
                m_board[i][j] = b.m_board[i][j];
            }
        }
    }
}

// construct from a file
Board::Board(const char* filename){
    int x, y, val;
    putZeros();
    FILE* input_file = fopen(filename, "r");
    if (input_file){
        while (fscanf(input_file, "%d %d %d", &x, &y, &val) != EOF){
            if (isValidCoor(x, y) && (val >= 1) && (val <= 61)){
                m_board[x][y] = val;
            }
        }
    }
}

bool Board::writeToFile(const char* filename) const{
    FILE* output = fopen(filename, "w");
    if (output){
        for (size_t i = 0; i < 9; i++){
            for (size_t j = 0; j < 9; j++){
                if (isValidCoor(i, j)){
                    fprintf(output, "%zu %zu %d\n", i, j, m_board[i][j]);
                }
            }
        }
        return true;
    }
    return false;
}
void Board::putZeros(){
    for (size_t i = 0; i < 9; i++){
        for (size_t j = 0; j < 9; j++){
            if (isValidCoor(i, j)){
                m_board[i][j] = EMPTY;
            }
        }
    }
}    
void Board::printBoard() const {
    for (int y = 8; y >= 0; y--){
        for (int i = 0; i < 8 - y ; i++){
                printf(" ");
        }

        for (int x = 8; x >= 0; x--){
            if (isValidCoor(x, y)){
                printf(" %2d", m_board[x][y]);
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}

bool Board::isLegalState() const {
    int seen[62];
    size_t a,b;
    int element, possible_neighbors;
    int neighbors_good, neighbors_empty;
    
    for (size_t i = 0; i < 62; i++){
        seen[i] = 0;
    }
    
    // initialize seen array
    for (size_t x = 0; x < 9; x++){
        for (size_t y = 0; y < 9; y++){
            if (isValidCoor(x, y) && (m_board[x][y] != EMPTY)){
                seen[m_board[x][y]]++;
            }
        }
    }
    
    // make sure none repeats
    for (size_t i = 1; i <= 61; i++){
        if (seen[i] > 1){
            //cout << "failed on repeats" << endl;
            return false;
        }
    }
    
    
    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if (isValidCoor(x, y) && (m_board[x][y] != EMPTY)){
                element = m_board[x][y];
                possible_neighbors = (element == 1) || (element == 61) ? 1 : 2;
                
                neighbors_good = 0;
                neighbors_empty = 0;
                for ( int a = x - 1; a <= x + 1; a++ ){
                    for ( int b = y - 1; b <= y + 1; b++ ){
                        if (isValidCoor(a, b) && areNeighbors(x, y, a, b)){
                            if (m_board[a][b] == EMPTY) {
                                neighbors_empty++;
                            } else if (abs(element - m_board[a][b]) == 1){
                                neighbors_good++;
                            }
                        }
                    }
                }
                
                // the number of consecutive elements on board != this number among neighbours 
                if (neighbors_good != ((element == 1) ? 0 : seen[element - 1]) + ((element == 61) ? 0 : seen[element + 1])){
                    //cout << "failed on far consecutive element" << endl;
                    return false;
                }
                // enough space to all consecutive elements
                if (neighbors_empty + neighbors_good < possible_neighbors){
                    //printf("failed on space.(%d,%d). empty: %d, good: %d, needed: %d\n",x,y, neighbors_empty , neighbors_good ,possible_neighbors);
                    return false;
                }
                
            }
        }
    }
    return true;
}

bool Board::isFull() const {
    for (size_t x = 0; x < 9; x++){
        for (size_t y = 0; y < 9; y++){
            if (isValidCoor(x, y) && (m_board[x][y] == EMPTY)){
                return false;
            }
        }
    }
    return true;
}

