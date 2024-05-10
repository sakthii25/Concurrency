#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std;
using namespace chrono;

class A{
    atomic<int> flag;
    public:
    atomic<int> ok;
    A(){
        flag = 1;ok = 0;
    }
    void search(vector<int>& v,int val){
        int idx = 0,n = v.size();
        while(flag and idx < n){
            if(v[idx] == val){
                flag = 0;ok = 1;
                break;
            }
            ++idx;
        }
        return;
    }
    void print(){
        cout << this_thread::get_id() << endl;
    }
};
void solve(){
    //vector<vector<int>> g = {{1,2,3},{4,5,6},{7,8,9}};
    int N,M;
    cin >> N >> M;
    vector<vector<int>> g(N,vector<int>(M));
    for(int i=0;i<N;++i){
      for(int j=0;j<M;++j){
        cin >> g[i][j];
      }
    }
    int element;
    cin >> element;
    A b;
    vector<thread> t(N);
    //int limit = thread::hardware_concurrency();
    //Note here i just created N threads for that problem  Beyond limit if we create thread there is no use of it 
    for(int i=0;i<N;++i){
        t[i] = thread(&A::search,&b,ref(g[i]),element);
        //t[i] = thread(&A::print,&b);
    }
    for(int i=0;i<N;++i){
        t[i].join();
    }
    cout <<(b.ok ? "Found" : "Not Found") << endl;
}
int main(){
    auto start = high_resolution_clock::now(); 
    solve();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end-start);
    cout << endl;
    cout << "Time Taken: " << duration.count() << " ms" << endl;
}
