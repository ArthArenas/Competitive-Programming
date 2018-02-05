#include <iostream>

using namespace std;

void preKMP(string P, int b[])
{
    int s = P.size();
    int i = 0;
    int j = -1;
    b[0] = -1;
    while(i < s){
        while(j >= 0 && P[i] != P[j]) { j = b[j]; }
        i++;
        j++;
        b[i] = j;
    }
}

int KMPvar(string s, string z, int b[])
{
    int result = 0;
    int cut_lim = -1;
    int cur_lim = -1;

    s = " " + s;
    int n = s.size();
    int m = z.size();
    int a, c;
    int i = 0;
    int j = -1;
    while(i < n){
        while(j >= 0 && s[i] != z[j]) { j = b[j]; }
        i++;
        j++;
        if(j == m){ // Gets in here only after a match
            a = (i - j);
            j = b[j];
            c = a + m - 1;
            if(a <= cur_lim){ // Overlap
                cut_lim = c;
            }
            else{ // Brand new
                if(a > cut_lim){
                    cur_lim = c;
                    cut_lim = c;
                    result++;
                }
            }
        }
    }
    return result;
}

int main()
{
    string s, z;
    cin >> s;
    cin >> z;
    int b[int(z.size()) + 1];
    preKMP(z, b);
    cout << KMPvar(s, z, b) << endl;
}