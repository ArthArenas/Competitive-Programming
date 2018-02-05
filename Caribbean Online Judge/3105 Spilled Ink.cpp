#include <iostream>
#include <queue>

using namespace std;

typedef pair<int,int> ii;

int main()
{
    // declare and get data
    int dr[] = {1, -1, 0, 0}; // S, N, E, W
    int dc[] = {0, 0, 1, -1}; // S, N, E, W
    int blots = 0;
    int biggest = 1;
    int R, C, i, j, k, c2, r2;
    cin >> R >> C;
    string paper[R];
    for(i = 0; i < R; i++){
        cin >> paper[i];
    }

    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++){
            if(paper[i][j] == '1'){
                int counter = 0;
                blots++;
                queue<ii> q;
                ii src(i, j);
                q.push(src);
                while(!q.empty()){
                    counter++;
                    // serve the next guy
                    ii a = q.front();
                    int r = a.first;
                    int c = a.second;
                    paper[r][c] = '0';
                    q.pop();

                    for(k = 0; k < 4; k++){
                        // See if we can add the neighbors to the wait list
                        r2 = r + dr[k];
                        c2 = c + dc[k];
                        if(!(r2 < 0 || r2 >= R || c2 < 0 || c2 >= C)){
                            if(paper[r2][c2] == '1'){
                                paper[r2][c2] = '0';
                                ii temp(r2, c2);
                                q.push(temp);
                            }
                        }
                    }
                }
                if(counter > biggest) { biggest = counter; }
            }
        }
    }
    cout << blots << " " << biggest << endl;
}