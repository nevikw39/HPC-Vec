#include <cstdio>
#include <random>
#include <limits>

using namespace std;

constexpr int N = 16777216;

float a[N], b[N];

int main()
{
    random_device rd;
    mt19937 mt(rd());
    normal_distribution<float> nd(0, 1);

    for (auto &i : a)
        i = nd(mt);
    for (auto &i : b)
        i = nd(mt);

    FILE *f = fopen("data.dat", "wb");
    fwrite_unlocked(a, sizeof(float), sizeof a / sizeof(float), f);
    fwrite_unlocked(b, sizeof(float), sizeof b / sizeof(float), f);
    fclose(f);
    return 0;
}
