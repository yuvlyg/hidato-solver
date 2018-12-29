
#define N_CELLS (61)

class Board {
public:
    Board();
    Board(const Board& b);
    Board(const char* filename);
    Board(const int vec[N_CELLS * 3]);
    void toVec(int vec[N_CELLS * 3]) const;
    void putZeros();
    void printBoard() const;
    bool writeToFile(const char* filename) const;
    bool isLegalState() const;
    bool isFull() const;
    int m_board[9][9];
    
};


