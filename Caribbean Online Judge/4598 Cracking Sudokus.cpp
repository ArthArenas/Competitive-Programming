#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>

using namespace std;

typedef pair<int, int> ii;

int solved = 0; // Amount of solved cells
bool change = false; // Signals when a cell was changed
int pows[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
int rows[] = {511, 511, 511, 511, 511, 511, 511, 511, 511};
int cols[] = {511, 511, 511, 511, 511, 511, 511, 511, 511};
int squs[] = {511, 511, 511, 511, 511, 511, 511, 511, 511};
int winners[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int sudoku[9][9];

/* The remaining 1s are available in this particular cell */
int f(int i, int j) {
    int m, n;
    int result = rows[i];
    result = result & cols[j];
    m = i / 3;
    n = j / 3;
    result = result & squs[m * 3 + n];
    return result;
}

/* Retrieves the winners and signals that there are changes when returning 0, and returns -1 otherwise
s = 0 (row), s = 1 (column), s = 2 (square) */
void getWinners(int s, int j) {
    int c = 0; // how many are available
    int i, k;
    int J = j;
    int m, n, p, q;
    int resultXOR; // Candidates to be defined
    int resultAND; // Numbers that are not defined and could be candidates
    int avail[9];
    int ands[7];

    // Fill-in the array of available numbers
    switch(s) {
    case 0:
        for(i = 0; i < 9; i++){
            if(sudoku[j][i] == 0){
                avail[c] = f(j, i);
                c++;
            }
        }
        break;
    case 1:
        for(i = 0; i < 9; i++){
            if(sudoku[i][j] == 0){
                avail[c] = f(i, j);
                c++;
            }
        }
        break;
    case 2:
        m = j / 3; // ROW
        n = j % 3; // COLUMN
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(sudoku[m*3 + i][n*3 + j] == 0){
                    avail[c] = f(m*3 + i, n*3 + j);
                    c++;
                }
            }
        }
        break;
    }

    if(!(c == 9 || c == 0)){
        for(i = c; i < 9; i++) { avail[i] = 0; } // Fill it with 0s
        ands[0] = avail[0] & avail[1];
        ands[1] = avail[2] & avail[3];
        ands[2] = avail[4] & avail[5];
        ands[3] = avail[6] & avail[7];
        m = avail[0] ^ avail[1];
        n = avail[2] ^ avail[3];
        p = avail[4] ^ avail[5];
        q = avail[6] ^ avail[7];
        ands[4] = m & n;
        ands[5] = p & q;
        m = m ^ n;
        n = p ^ q;
        ands[6] = m & n;
        resultXOR = m ^ n;
        resultAND = ands[0];
        for(i = 1; i < 7; i++) { resultAND = resultAND | ands[i]; }

        // cout << "case " << s << " resultAND = " << resultAND << " resultXOR = " << resultXOR << " j = " << J << endl;
        k = 0;
        for(i = 0; i < 9; i++) {
            if(resultAND % 2 == 0 && resultXOR % 2 == 1) { winners[k] = i; k++; } /// HERE ARE THE WINNERS
            resultAND /= 2;
            resultXOR /= 2;
        }
        winners[k] = -1;
    }
    else { winners[0] = -1; } // signaling that the row is empty or full
}

/* changes the given cell to the given value and kills the possibility for its lines and square to have this value
btindex is... */
void setbox(int i, int j, int num) {
    // Global signals
    solved++;
    change = true;
    int m, n;
    sudoku[i][j] = (num + 1);
    rows[i] -= pows[num];
    cols[j] -= pows[num];
    m = i / 3; // ROW
    n = j / 3; // COLUMN
    squs[m*3 + n] -= pows[num];
    // cout << "setting " << i << ", " << j << " with " << num + 1 << endl;
}

void unsetbox(int i, int j) {
    // Global signals
    //cout << "unsetting " << i << ", " << j << " from " << sudoku[i][j] << endl;
    solved--;
    int num = sudoku[i][j] - 1;
    int m, n;
    sudoku[i][j] = 0;
    rows[i] += pows[num];
    cols[j] += pows[num];
    m = i / 3; // ROW
    n = j / 3; // COLUMN
    squs[m*3 + n] += pows[num];
    // cout << "unsetting " << i << ", " << j << " from " << num + 1 << endl;
}

/* Fill the whole indexed (by j) area (s) in the winners array, and record every change in v. Winners is stopped by -1
s = 0 (row), s = 1 (column), s = 2 (square) */
void fillWinners(int s, int j, vector<ii>& v) {
    int k = 0;
    int i, m, n;
    int J = j;
    while(winners[k] != -1){
        switch(s)
        {
        case 0:
            for(i = 0; i < 9; i++){
                if(sudoku[j][i] == 0 && f(j, i) / pows[winners[k]] % 2 == 1){
                    setbox(j, i, winners[k]);
                    ii temp(j, i);
                    v.push_back(temp);
                    i = 9; // break
                }
            }
            break;
        case 1:
            for(i = 0; i < 9; i++){
                if(sudoku[i][j] == 0 && f(i, j) / pows[winners[k]] % 2 == 1){
                    setbox(i, j, winners[k]);
                    ii temp(i, j);
                    v.push_back(temp);
                    i = 9;
                }
            }
            break;
        case 2:
            m = J / 3; // ROW
            n = J % 3; // COLUMN
            for(i = 0; i < 3; i++){
                for(j = 0; j < 3; j++){
                    if(sudoku[m*3 + i][n*3 + j] == 0 && f(m*3 + i, n*3 + j) / pows[winners[k]] % 2 == 1){
                        // cout << "call made from case 2\n";
                        setbox(m*3 + i, n*3 + j, winners[k]);
                        ii temp(m*3 + i, n*3 + j);
                        v.push_back(temp);
                        i = 3; j = 3;
                    }
                }
            }
            break;
        }
        k++;
    }
}

/* Reads the matrix */
void readmatrix() {
    int i, j;
    char c[9], d;
    string trash;
    for(i = 0; i < 3; i++){
        cin >> c[0] >> c[1] >> c[2] >> d >> c[3] >> c[4] >> c[5] >> d >> c[6] >> c[7] >> c[8];
        for(j = 0; j < 9; j++) {
            if(c[j] != '*') { setbox(i, j, (c[j] - '0' - 1)); }
        }
    }
    cin >> trash;
    for(i = 0; i < 3; i++){
        cin >> c[0] >> c[1] >> c[2] >> d >> c[3] >> c[4] >> c[5] >> d >> c[6] >> c[7] >> c[8];
        for(j = 0; j < 9; j++) {
            if(c[j] != '*') { setbox(i + 3, j, (c[j] - '0' - 1)); }
        }
    }
    cin >> trash;
    for(i = 0; i < 3; i++){
        cin >> c[0] >> c[1] >> c[2] >> d >> c[3] >> c[4] >> c[5] >> d >> c[6] >> c[7] >> c[8];
        for(j = 0; j < 9; j++) {
            if(c[j] != '*') { setbox(i + 6, j, (c[j] - '0' - 1)); }
        }
    }
}

/* Prints the matrix */
void printmatrix() {
    int o = 0;
    int i;
    for(i = 0; i < 3; i++){
        printf("%d %d %d | %d %d %d | %d %d %d\n", sudoku[o + i][0], sudoku[o + i][1], sudoku[o + i][2], sudoku[o + i][3], sudoku[o + i][4], sudoku[o + i][5], sudoku[o + i][6], sudoku[o + i][7], sudoku[o + i][8]);
    }
    printf("------+-------+------\n");
    o = 3;
    for(i = 0; i < 3; i++){
        printf("%d %d %d | %d %d %d | %d %d %d\n", sudoku[o + i][0], sudoku[o + i][1], sudoku[o + i][2], sudoku[o + i][3], sudoku[o + i][4], sudoku[o + i][5], sudoku[o + i][6], sudoku[o + i][7], sudoku[o + i][8]);
    }
    printf("------+-------+------\n");
    o = 6;
    for(i = 0; i < 3; i++){
        printf("%d %d %d | %d %d %d | %d %d %d\n", sudoku[o + i][0], sudoku[o + i][1], sudoku[o + i][2], sudoku[o + i][3], sudoku[o + i][4], sudoku[o + i][5], sudoku[o + i][6], sudoku[o + i][7], sudoku[o + i][8]);
    }
}

/* Returns the next cell that is empty */
ii getnextempty() {
    int i, j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(sudoku[i][j] == 0){
                ii p(i, j);
                return p;
            }
        }
    }
    ii r(-1, -1);
    return r; // This should never happen though
}

/* We need to undo every consequence of the current decision and backtrack or take the next decision */
bool checkforerrors() {
    bool error = false;
    int i, j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(sudoku[i][j] == 0 && f(i, j) == 0) {
                    error = true;
                    // cout << "found error at " << i << ", " << j << endl;
                    int m = i/3;
                    int n = j/3;
                    // cout << rows[i] << " " << cols[j] << " " << squs[m*3 + n] << endl;
            }
        }
    }
    return error;
}

/* Attempts to solve each area */
vector<ii> quickSolution() {
    vector <ii> v;
    int i, s;
    while(change && solved != 81){
        change = false;
        for(i = 0; i < 9 && solved != 81; i++){
            for(s = 0; s < 3; s++){
                getWinners(s, i);
                //cout << "out of getWinners(" << s << ", " << i << ")\n";
                fillWinners(s, i, v);
                //cout << "out of fillWinners(" << s << ", " << i << ")\n";
            }
        }
    }
    return v;
}

bool backtrack(int i, int j) {
    //if(solved > 20) { printmatrix(); }
    // Create the stack of options
    // cout << "here with " << i << ", " << j << endl;
    stack <int> s;
    int n = f(i, j);
    int k = 0;
    int a, b;
    bool success;
    // cout << "options are: ";
    while(n != 0){
        if(n%2 == 1) { s.push(k); }
        n /= 2;
        k++;
    }
    // cout << endl;
    while(!s.empty() && solved != 81){
        // cout << "trying with " << s.top() + 1 << " in " << i << ", " << j << endl;
        // printmatrix();
        setbox(i, j, s.top());
        //printmatrix();
        if(solved == 81) { return true; }
        vector<ii> v = quickSolution();
        if(solved == 81) { return true; }
        if(checkforerrors()){
            // printmatrix();
            // undo vector
            b = v.size();
            for(a = 0; a < b; a++){ unsetbox(v[a].first, v[a].second); }
            // undo current decision
            unsetbox(i, j);
            // discard this option from the stack
            s.pop();
        }
        else{
            // Everything seems fine with this option so we go on
            ii nextnum = getnextempty();
            // Just in case we are done
            success = backtrack(nextnum.first, nextnum.second);
            // If there's success then we're done, else we have to pop and undo
            if(!success){
                b = v.size();
                for(a = 0; a < b; a++) { unsetbox(v[a].first, v[a].second); }
                unsetbox(i, j);
                s.pop();
            }
            else{
                return true;
            }
        }
    }
    // cout << "ran out of options with " << i << ", " << j << endl;
    return false; // We just ran out of options so whoever called me, must receive this result
}

int main() {
    readmatrix();

    vector<ii> trash = quickSolution();

    if(solved != 81){
        ii initial = getnextempty();
        bool alwaysTrue = backtrack(initial.first, initial.second);
    }

    printmatrix();

    return 0;
}