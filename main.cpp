//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();

    cout << "\nMaze:\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

// ----------------------------------------------------------
// STUDENTS IMPLEMENT DFS HERE
// Add arguments, return type, and logic
// ----------------------------------------------------------
bool dfs(int r, int c, //Shows row and column
        const vector<vector<int>>& maze, //maze
        vector<vector<bool>>& visited, //visited cells
        vector<vector<int>>& parent_r, //parent row for reconstruction
        vector<vector<int>>& parent_c, // parent col for reconstruction
        int exit_r, int exit_c) { //exit coords

    //# rows in maze
    int x = maze.size();

    //# col in maze
    int y = maze[0].size();

    //Base Cases
    //If (r,c) outside of maze then stop
    if (r < 0 || c < 0 || r >= x || c >= y) {
        return false;
    }

    //If cell is wall or 1 then stop
    if (maze[r][c] == 1) {
        return false;
    }

    //If already visited the cell then stop
    if (visited[r][c]) {
        return false;
    }

    //Make current cell as visited
    visited[r][c] = true;

    //If the cell is the exit
    if (r == exit_r && c == exit_c) {
        return true;
    }

    /* reference for dr and dc
    int dr[4] = { -1,  0,  1,  0 };

    ex:
    dr[0] == -1
    r-1 == new row // UP


    int dc[4] = {  0,  1,  0, -1 };
    ex:
    dc[1] == 1
    c + 1 == new col // Right

     */

    //Directions for DFS
    for (int direction=0; direction < 4; direction++) {
        //make next row
        int neighborR = r + dr[direction];
        //make next col
        int neighborC = c + dc[direction];

        //If wall then skip
        if (maze[neighborR][neighborC] == 1) {
            continue;
        }

        //If visited cell then skip
        if (visited[neighborR][neighborC]) {
            continue;
        }

        //Set new row and column of neighbor
        parent_c[neighborR][neighborC] = c;
        parent_r[neighborR][neighborC] = r;




        /*
         Reference dfs
        dfs(int r, int c, //Shows row and column
        const vector<vector<int>>& maze, //maze
        vector<vector<bool>>& visited, //visited cells
        vector<vector<int>>& parent_r, //parent row for reconstruction
        vector<vector<int>>& parent_c, // parent col for reconstruction
        int exit_r, int exit_c) { //exit coords
         */
        //Recursive Call
        if (dfs(neighborR, neighborC, maze, visited, parent_r, parent_c, exit_r, exit_c)) {
            return true;
        }

    }
//if all direction fail
return false;
}


// ----------------------------------------------------------
// MAIN PROGRAM (students add DFS calls and logic)
// ----------------------------------------------------------
int main() {
    int N, M;

    cout << "Enter maze dimensions N M: ";
    cin >> N >> M;

    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(maze, N, M);

    // Pick entrance and exit
    pair<int,int> entrance = chooseBoundaryCell(maze);
    pair<int,int> exitcell = chooseBoundaryCell(maze);

    while (exitcell == entrance) {
        exitcell = chooseBoundaryCell(maze);
    }

    int ent_r = entrance.first;
    int ent_c = entrance.second;
    int exit_r = exitcell.first;
    int exit_c = exitcell.second;

    // Display the maze
    printMaze(maze, ent_r, ent_c, exit_r, exit_c);

    // Students must use these
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> parent_r(N, vector<int>(M, -1));
    vector<vector<int>> parent_c(N, vector<int>(M, -1));

    // ------------------------------------------------------
    // STUDENT WORK:
    // Call your DFS, track visited, and fill parent_r and parent_c
    // ------------------------------------------------------
    // bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);

    // ------------------------------------------------------
    // STUDENT WORK:
    // If found, print the path
    // ------------------------------------------------------
    // if (found) {
    //     printPath(exitcell, parent_r, parent_c, ent_r, ent_c);
    // } else {
    //     cout << "\nNo path exists.\n";
    // }

    return 0;
}