#include <bits/stdc++.h>
using namespace std;

class SnakesAndLadders {
public:
    int n;
    vector<int> board;
    
    // Constructor: Initializes the board using the given snakes and ladders.
    SnakesAndLadders(int size, vector<pair<int, int>> snakes, vector<pair<int, int>> ladders) {
        n = size;
        board.resize(n * n + 1, -1);
        
        // For each snake, set the board position to its destination.
        for (auto [start, end] : snakes)
            board[start] = end;
        // For each ladder, set the board position to its destination.
        for (auto [start, end] : ladders)
            board[start] = end;
    }
    
    // Returns the minimum number of moves to win the game.
    int minMovesToWin() {
        queue<int> q;
        vector<bool> visited(n * n + 1, false);
        q.push(1);
        visited[1] = true;
        int moves = 0;
        
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int curr = q.front();
                q.pop();
                
                // If we've reached the final square, return the move count.
                if (curr == n * n)
                    return moves;
                
                // Try all possible dice outcomes (1 through 6).
                for (int next = curr + 1; next <= min(curr + 6, n * n); ++next) {
                    int destination = (board[next] == -1) ? next : board[next];
                    
                    if (!visited[destination]) {
                        visited[destination] = true;
                        q.push(destination);
                    }
                }
            }
            ++moves;
        }
        
        return -1; // Return -1 if it's impossible to reach the end.
    }
};

int main() {
    int boardSize;
    cout << "Enter board size (n for an n x n board): ";
    cin >> boardSize;
    
    int totalSquares = boardSize * boardSize;
    
    int numSnakes;
    cout << "Enter number of snakes: ";
    cin >> numSnakes;
    
    vector<pair<int, int>> snakes(numSnakes);
    cout << "Enter snake start and end positions (start > end):\n";
    for (int i = 0; i < numSnakes; i++) {
        int start, end;
        cin >> start >> end;
        snakes[i] = {start, end};
    }
    
    int numLadders;
    cout << "Enter number of ladders: ";
    cin >> numLadders;
    
    vector<pair<int, int>> ladders(numLadders);
    cout << "Enter ladder start and end positions (start < end):\n";
    for (int i = 0; i < numLadders; i++) {
        int start, end;
        cin >> start >> end;
        ladders[i] = {start, end};
    }
    
    SnakesAndLadders game(boardSize, snakes, ladders);
    int moves = game.minMovesToWin();
    if (moves != -1)
        cout << "Minimum moves to win: " << moves << endl;
    else
        cout << "It is not possible to win the game." << endl;
    
    return 0;
}
