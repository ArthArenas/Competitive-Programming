#include <cstdio>
#include <iostream>

using namespace std;

int pows[13];

void setpows()
{
    int i;
    int result = 1;
    for(i = 0; i < 13; i++){
        pows[i] = result;
        result *= 2;
    }
}

int toint(string s)
{
    int result = 0;
    int i = 0;
    while(s[i]){
        result += pows[int(s[i] - 'A')];
        i++;
    }
    return result;
}

int findmatch(int result, int resultA)
{
    int i = 0;
    // result - 0 and resultA - 1
    while(true){
        if(result % 2 == 0 && resultA % 2 == 1) { return i; }
        else { result /= 2; resultA /= 2; }
        i++;
    }
}

int main()
{
    setpows();
    int T, j, i, iA, iB;
    string A, B, C, D, weight;
    bool done;
    int AB[6];
    int resultA, resultB, result, temp;
    scanf("%d", &T);
    for(j = 0; j < T; j++){
        done = false;
        resultA = 4095;
        resultB = 4095;
        result = 0;
        for(i = 0; i < 3; i++){
            cin >> A >> B >> C;
            iA = toint(A);
            iB = toint(B);
            if(C == "even"){
                result = result | iA;
                result = result | iB;
            }
            else if(C == "up"){
                // Swap
                D = A; A = B; B = D;
                temp = iA; iA = iB; iB = temp;
                resultA = resultA & iA;
                resultB = resultB & iB;
            }
            else{
                resultA = resultA & iA;
                resultB = resultB & iB;
            }
            AB[i*2] = iA;
            AB[i*2 + 1] = iB;
        }
        resultA = resultA | resultB;
        // result's 0s are candidates, as well as resultA's 1s are, so we find the match and we're done spotting the letter
        temp = findmatch(result, resultA);
        for(i = 0; i < 3 && !done; i++){
            if( (AB[i*2] / pows[temp]) % 2 == 1 ) { done = true; weight = "light"; }
        }
        for(i = 0; i < 3 && !done; i++){
            if( (AB[i*2 + 1] / pows[temp]) % 2 == 1 ) { done = true; weight = "heavy"; }
        }
        cout << char(temp + int('A')) << " is the counterfeit coin and it is " << weight << "." << endl;
    }
}