#include "board.cc"

/**
 * return values is whether the board was solved
 * if true, the board was solved inplace and everything is good
 * else, the board isn't solvable and wasn't changed!
 */
bool solveInplace(Board& b, int hint=-1){
    if (!b.isLegalState()){
        return false;
    }
    if (b.isFull()) {
        return true;
    }
    int seen[62];
    int element, element2;
    int best_interval = 60;
    int best_element = 1;
    int tmp;
    int pre_x, pre_y;

    for (size_t i = 0; i < 62; i++){
        seen[i] = 0;
    }
    
    // initialize seen array
    for (size_t x = 0; x < 9; x++){
        for (size_t y = 0; y < 9; y++){
            if (isValidCoor(x, y) && (b.m_board[x][y] != EMPTY)){
                seen[b.m_board[x][y]]++;
            }
        }
    }
    
    if (hint == -1){ // no hint...
        // find shortest unknown interval
        for (element = 1; element <= 61;){
            if (seen[element] != 0) {
                element ++;
                continue;
            }
            for (element2 = element + 1; element2 <= 61 && seen[element2] == 0; element2++);
            if ((element2 - element) < best_interval){
                best_interval = element2 - element;
                best_element = element;
                // printf("new best element: %d (len %d)"
            }
            element = element2;
        }
        element = best_element;
    } else {
        element = hint;
    }
    // printf("searching a place for %d\n", element);
    //return 0;
    if (element > 61 || seen[element] != 0){
        printf("bug!!!!!");
        return false;
    }

    // find predecessor's location
    for (size_t x = 0; x < 9; x++){
        for (size_t y = 0; y < 9; y++){
            if (isValidCoor(x, y) && (b.m_board[x][y] == element - 1)){
                pre_x = x;
                pre_y = y;
                break;
             }
         }
    }
    // try to put it in everywhere free
    for (size_t x = (pre_x > 0 ? pre_x - 1 : 0); x <= pre_x + 1; x++){
        for (size_t y = (pre_y > 0 ? pre_y - 1: 0); y <= pre_y + 1; y++){
            if (isValidCoor(x, y) && (b.m_board[x][y] == EMPTY)){
                b.m_board[x][y] = element;
                if ((element + 1 <= 61) && (seen[element+1] == 0)){
                    tmp = solveInplace(b, element + 1); // good element for next round
                } else {
                    tmp = solveInplace(b);
                }
                if (tmp){
                    return true;
                } else {
                    b.m_board[x][y] = EMPTY;
                }
            }
        }
    }
    // printf("couldn't locate %d", element);
    // couldn't find a place... such a shame
    return false;
}

bool solveFromVec(int vec[N_CELLS * 3]){
    bool res;
    Board b(vec);
    b.printBoard();
    res = solveInplace(b);
    if (res){
        b.toVec(vec);
    }
    return res;
}

int main(int argc, char** argv){
    bool res;
    if (argc == 1){
        printf("Usage: %s input_filename [output_filename]\n", argv[0]);
        return 0;
    }
    
    Board b(argv[1]);

    b.printBoard();
    res = solveInplace(b);
    if (res){
        printf("success!\n");
        if (argc == 3){
            b.writeToFile(argv[2]);
        } else {
            b.printBoard();
        }
        return 0;
    } else {
        printf("fail\n");
        return 1;
    }
    //cout << "solved?! " << solveInplace(b) << endl;
    //b.printBoard();
    
    return 0;
}
