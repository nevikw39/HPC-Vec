#include <cstdio>
#include <random>
#include <limits>

using namespace std;

constexpr int N = 16777216;

char str_a[N], str_b[N];

int main()
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<char> uid(numeric_limits<char>::min(), numeric_limits<char>::max());

    for (char &i : str_a)
        i = uid(mt);

    for (char &i : str_b)
        i = uid(mt);

    FILE *f = fopen("data.txt", "w");
    fwrite_unlocked(str_a, sizeof(char), sizeof str_a / sizeof(char), f);
    fwrite_unlocked(str_b, sizeof(char), sizeof str_b / sizeof(char), f);
    fclose(f);
    return 0;
}
