#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>

using namespace std;

typedef vector<long long int> vll;
bitset<80000> bs;
vector<long long> vprimes;
int primes = 0;
const int MAX1 = 80000; // upper bound on the square root of 6 * 10^9
const int MAX2 = 300;   // upper bound on the square root of 8 * 10^4

void setSieve()
{
    bs.set();
    bs[0] = 0;
    bs[1] = 0;
    int i, j;
    for(i = 2; i < MAX2; i++){
        if(bs[i] == 1){
            vprimes.push_back(i);
            for(j = i * i; j < MAX1; j += i) { bs[j] = 0; }
        }
    }
    for(i = MAX2; i < MAX1; i++){
        if(bs[i] == 1) { vprimes.push_back(i); }
    }
    primes = vprimes.size();
}

bool isPrime(long long int n)
{
    if(n < MAX1) { return bool(bs[int(n)]); }
    int i = 0;
    bool exit = false;
    while(!exit && vprimes[i] * vprimes[i] <= n){
        if(n % vprimes[i] == 0) { exit = true; }
        i++;
    }
    return (!exit);
}

long long int findClosestPrime(long long int n)
{
    long long int k = n;
    while(!isPrime(k--)) {}
    return (k+1);
}

void setInput(int heaps[], int N, int K, bool& done, string& answer)
{
    int m;
    if(N == 1){
        long long int n;
        cin >> n;
        if(!isPrime(n)) { m = int(n - findClosestPrime(n)); }
        else { m = int(n - findClosestPrime(n - 1)); }
        if(m > K) { heaps[0] = m - K - 1; }
        else { answer = "YES"; done = true; }
    }
    else{
        long long int nums[N];
        for(int i = 0; i < N; i++) { cin >> nums[i]; }
        for(int i = 0; i < N && !done; i++){
            m = int(nums[i] - findClosestPrime(nums[i]));
            if(m > K) { heaps[i] = m - K - 1; }
            else { answer = "YES"; done = true; }
        }
    }
}

int main()
{
    setSieve();
    int T, N, i, j, resultXOR;
    long long int K;
    bool done;
    string answer;
    cin >> T;
    for(j = 0; j < T; j++){
        done = false;
        scanf("");
        cin >> N >> K;
        int heaps[N];

        setInput(heaps, N, K, done, answer);
        
        resultXOR = 0;
        for(i = 0; i < N && !done; i++) { resultXOR = resultXOR ^ (heaps[i] % (K + 1)); }

        if(!done) { (resultXOR > 0) ? answer = "YES" : answer = "NO"; }

        cout << answer << endl;
    }
    return 0;
}