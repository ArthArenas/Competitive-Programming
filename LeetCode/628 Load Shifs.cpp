class Solution {
public:
    int powersOfTwo[26];
    
    void setPowersOfTwo(){
        int cur = 1;
        for(int i = 0; i < 26; i++){
            powersOfTwo[i] = cur;
            cur <<= 1;
        }
    }
    
    int getRep(char c){
        return powersOfTwo[ (int)(c - 'a') ];
    }

    void createBitmasks(vector<int>& v, string& s){
        int i = (int)s.size() - 1;
        int curBM = 0;
        while(i >= 0){
            curBM = curBM | getRep(s[i]);
            v[i--] = curBM;
        }
    }

    bool belongs(char c, int incBitmask){
        return (getRep(c) & incBitmask);
    }
    
    string removeDuplicateLetters(string s) {
        if((int)s.size() == 0) return s;
        setPowersOfTwo();
        string result;
        int i = 0;
        int length = s.size();
        vector<int> right( length, 0 );
        createBitmasks(right, s);

        int validBitmask = right[0];
        int start = 0;
        char smallest = 'z';

        // find the smallest that appears in the string
        while(validBitmask){
            for(i = start; i < length; i++){
                if(validBitmask == (right[i] & validBitmask)){ // this character is valid
                    if(smallest > s[i] && belongs(s[i], validBitmask)){
                        smallest = s[i];
                        start = i;
                    }
                }
            }
            result += smallest;
            // now eliminate it from the valid bitmask super fast
            validBitmask = validBitmask ^ getRep(smallest);
            smallest = 'z';
        }
        return result;
    }
};