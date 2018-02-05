#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

struct Person
{
    Person() = default;
    Person(int weight, string name)
    {
        this -> weight = weight;
        this -> name = name;
        visited = false;
    }
    void add(Person*& p) { friends.push_back(p); }
    vector<Person*> friends;
    int weight;
    bool visited;
    string name;
};

int main()
{
    int M, N, i, weight;
    string name, name2;
    scanf("%d %d", &M, &N);
    while(!(M == 0 && N == 0)){
        map<string, Person> people;
        for(i = 0; i < M; i++){
            cin >> name >> weight;
            Person p(weight, name);
            pair<string, Person> guy(name, p);
            people.insert(guy);
        }
        for(i = 0; i < N; i++){
            cin >> name >> name2;
            Person* p = &(people.find(name2) -> second);
            Person* q = &(people.find(name) -> second);
            people[name].add(p);
            people[name2].add(q);
        }
        queue<Person*> waitlist;
        vector<string> ans;
        for(map <string, Person>::iterator it = people.begin(); it != people.end(); it++){
            if(!(it -> second.visited)){
                waitlist.push(&(it -> second));
                int biggest = it -> second.weight;
                string sbig = it -> first;
                while(!waitlist.empty()){
                    Person* t = waitlist.front();
                    waitlist.pop();
                    t -> visited = true;
                    if(t -> weight > biggest) { biggest = t -> weight; sbig = t -> name; }
                    for(Person* q: t -> friends){
                        if(!(q -> visited)) { waitlist.push(q); }
                    }
                }
                ans.push_back(sbig);
            }
        }
        int s = ans.size();
        sort(&ans[0], &ans[s]);
        for(i = 0; i < s; i++) { cout << ans[i] << endl; }
        scanf("%d %d", &M, &N);
    }
}