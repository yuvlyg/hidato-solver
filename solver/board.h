
class Board {
public:
    Board();
    Board(const Board& b);
    Board(const char* filename);
    void putZeros();
    void printBoard() const;
    bool writeToFile(const char* filename) const;
    bool isLegalState() const;
    bool isFull() const;
    int m_board[9][9];
    
};


