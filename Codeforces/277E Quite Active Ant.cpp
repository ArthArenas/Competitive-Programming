#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > vvi;
const long long int MOD = 1000000007L;
typedef long long int ll;

struct Matrix{
    Matrix() = default;
    Matrix(int length){
        vvi N(length, vector<int>(length));
        M = N;
        this -> length = length;
    }
    Matrix& operator=(Matrix b){
        int n = b.length;
        int i, j;
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                M[i][j] = b.M[i][j];
            }
        }
        return *this;
    }
    int length;
    vvi M;
};

Matrix multMat(Matrix a, Matrix b){
    int n = a.length;
    int i, j, k;
    long long int cell;
    Matrix res(n);
    for(i = 0; i < n; i++){
       for(j = 0; j < n; j++){
            cell = 0L;
            for(k = 0; k < n; k++){
                cell += ll(a.M[i][k]) * ll(b.M[k][j]);
                cell %= MOD;
            }
            res.M[i][j] = cell;
       }
    }
    return res;
}

Matrix matPow(Matrix base, int power){
    Matrix result(2);
    if(power == 1){
        result = base;
    }
    else if(power & 1){
        result = multMat(base, matPow(base, power - 1));
    }
    else{
        Matrix k = matPow(base, power / 2);
        result = multMat(k, k);
    }
    return result;
}

int main(){
    int n;
    cin >> n;
    Matrix m(2);
    m.M[0][0] = 0;
    m.M[0][1] = 1;
    m.M[1][0] = 3;
    m.M[1][1] = 2;
    m = matPow(m, n);
    cout << m.M[0][0] << endl;
    return 0;
}