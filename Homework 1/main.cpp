#include<iostream>
#include<vector>

using namespace std;

int solution(vector<int> &A, vector<int> &B, int N) {
    map<int, int> counter;
    for(int i=0;i<A.size();i++){
        if (counter.find(A[i]) == counter.end()){
            counrer[A[i]] = 1;
        } else {
            counter[A[i]]++;
        }
    }

    return counter.size();
}


int main(){
    vector<int> A{1, 2, 4, 5};
    vector<int> B{2, 3, 5, 6};
    int N = 6;

    cout << solution(A, B, N)<<endl;
    return 0;
}