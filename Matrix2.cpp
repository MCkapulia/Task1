#include <iostream>
#include <vector>
#include <time.h>
#include <thread>
using namespace std;

void multiMatrix(int n, vector <vector <int>>& a, vector <vector <int>>& b)
{
    int multi, sum;
    vector <vector <int>> c(n, vector<int>(n));

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            sum = 0;
            for (int j = 0; j < c[i].size(); j++)
            {
                multi = a[k][j] * b[j][i];
                c[k][i] += multi;
            }
        }
    }
    cout << "Matrix C = A * B:" << endl;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < c[i].size(); j++)
        {

            cout << c[i][j] << " ";
        }
        cout << endl;
    }

}

void multiMatrixByLines(vector <int>& a, vector <vector <int>>& b, int row, int n, vector <vector <int>>& c)
{
    int multi;
    vector <int > res(n);
   
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n; j++)
        {
            multi = a[j] * b[j][i];
            res[i] += multi;
        }
    }
    c[row] = res;
}
int main()
{
    int n; // размер матриц
    cout << "Enter size of matrix: ";
    cin >> n;
    int ub = 100;
    int lb = 1;
    vector <vector <int>> a(n, vector<int>(n));
    vector <vector<int>> b(n, vector<int>(n));
    vector <vector<int>> c(n, vector<int>(n));
    cout << "Matrix A:" << endl;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < a[i].size(); j++)
        {
            a[i][j] = (rand() % (ub - lb + 1)) + lb;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Matrix B:" << endl;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < b[i].size(); j++)
        {
            b[i][j] = (rand() % (ub - lb + 1)) + lb;
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    clock_t start_time = clock();
    vector < thread > threads1;
    cout << "Matrix C = A * B:" << endl;
    for (int i = 0; i < n; i++) {
        thread thr(multiMatrixByLines, ref(a[i]), ref(b), i, n, ref(c));
        threads1.emplace_back(move(thr));
    }
    for (auto& thr : threads1) {
        thr.join();
    }
    clock_t end_time = clock();
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < c[i].size(); j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    double search_time = (double)(end_time - start_time)/CLOCKS_PER_SEC;
    cout << "Time with threads: "<< search_time << endl;
    clock_t start_time1 = clock();
    multiMatrix(n, a, b);
    clock_t end_time1 = clock();
    
    double search_time1 = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time without threads: " << search_time1 << endl;
   
}

