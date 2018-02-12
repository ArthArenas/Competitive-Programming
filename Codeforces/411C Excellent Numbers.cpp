#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<pair<int, int> > vii;
typedef long long int ll;

const long long int MOD = 1000000007;

vector<long long int> memoInv(1, 1L);

ll fastPow(ll x, ll n){
    ll result = 1L;
    while(n){
        if(n&1) result = result * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return result;
}

ll binCoeff(ll n, ll k){
    if(n - k > k) { k = n - k; } /// k is as big as possible
    ll i;
    ll result = 1L;
    for(i = k + 1L; i <= n; i++){
        result *= i;
        result %= MOD;
    }
    /// Inverse part, this is the part that takes longer
    ll largestInverse = memoInv.size();
    largestInverse--;
    if(largestInverse < (n - k)){
        ll inverses = memoInv[largestInverse];
        for(i = int(largestInverse) + 1; i <= (n - k); i++){
            inverses *= fastPow(i, MOD - 2);
            inverses %= MOD;
            memoInv.push_back(inverses);
        }
    }
    result *= memoInv[n - k];
    result %= MOD;
    return result;
}

vector<long long int> getNums(ll a, ll b, ll n){
    vector<ll> v;
    for(int i = 2; i <= 256; i++){
        int j = i;
        ll TEN = 1L;
        ll result = 0L;
        while(j != 1){
            result += (j&1) ? int(a) * TEN : int(b) * TEN;
            TEN *= 10L;
            j >>= 1;
        }
        if(a*n <= result && result <= b*n){
            v.push_back(result);
        }
    }
    return v;
}

int main(){
    int a, b, i;
    ll n;
    scanf("%d %d %I64d", &a, &b, &n);
    /// now we get all the candidates for excellent numbers
    /// between a*n to b*n, inclusively
    vector<ll> nums = getNums(a, b, n);
    int m = nums.size();
    ll result = 0L;
    for(i = m - 1; i >= 0; i--){ /// Works best for my memoization
        ll B = (nums[i] - a * n) / (b - a);
        ll A = n - B;
        if(B >= 0 && A >= 0 && A * a + B * b == nums[i]){
            result += binCoeff(n, A);
            result %= MOD;
        }
    }
    printf("%I64d\n", result);
    return 0;
}