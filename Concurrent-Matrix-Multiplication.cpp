#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std;
using namespace chrono;

class A{
    public:
    vector<vector<int>> mat;
    A(int n,int m){
        mat.resize(n,vector<int>(m));
    }
    void multiply(vector<int>& a,vector<vector<int>>& b,int r){
        int n = a.size(),m = b.size();
        for(int c=0;c<m;++c){
            int sum = 0;
            for(int i=0;i<n;++i){
                sum += (a[i] * b[i][c]);
            }
            mat[r][c] = sum;
        }
        return;
    }
};
void solve(){
    int n1,m1;
    cin >> n1 >> m1;
    vector<vector<int>> a(n1,vector<int>(m1));
    for(int i=0;i<n1;++i){
        for(int j=0;j<m1;++j){
            cin >> a[i][j];
        }
    }
    int n2,m2;
    cin >> n2 >> m2;
    vector<vector<int>> b(n2,vector<int>(m2));
     for(int i=0;i<n2;++i){
        for(int j=0;j<m2;++j){
            cin >> b[i][j];
        }
    }
    if(m1 != n2){
        cout << "Can't multiply" << endl;
        return;
    }
   int n = n1,m = m2;
   A c(n,m);
   //cout << thread::hardware_concurrency() << endl;
   vector<thread> t(n*m); // Beyond the thread limit if we create thread it's not going to useful but this is only for educational purpose
   int ind = 0;
   for(int i=0;i<n;++i){
       for(int j=0;j<m;++j){ 
           t[ind++] = thread(&A::multiply,&c,ref(a[i]),ref(b),i);
           //c.multiply(a[i],b,i);
       }
   }
   ind = 0;
   for(int i=0;i<n;++i){
       for(int j=0;j<m;++j){
           t[ind++].join();
       }
   }
   vector<vector<int>> res = c.mat;
    cout << "Result Matrix: " << endl;
   for(int i=0;i<n;++i){
       for(int j=0;j<m;++j){
           cout << res[i][j] << " ";
       }
       cout << endl;
   }
}
int main(){
    auto start = high_resolution_clock::now(); 
    solve();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end-start);
    cout << endl;
    cout << "Time Taken: " << duration.count() << " ms" << endl;
}
