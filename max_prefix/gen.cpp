#include <cstdio>
#include <random>
#include <limits>

using namespace std;

constexpr int N = 16777216;

int arr[N];

int main()
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> uid(numeric_limits<int>::min() / N, numeric_limits<int>::max() / N);

    for (int &i : arr)
        i = uid(mt);

    FILE *f = fopen("data.dat", "wb");
    fwrite_unlocked(arr, sizeof(int), sizeof arr / sizeof(int), f);
    fclose(f);
    return 0;
}
