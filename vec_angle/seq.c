#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef N
#define N 16777216
#endif // N
#ifndef T
#define T 64
#endif // T

float a[N], b[N];

float dot(const float *const lhs, const float *const rhs)
{
    float y = 0;
    for (int i = 0; i < N; i++)
        y += i[lhs] * i[rhs];
    return y;
}

float vec_angle() { return dot(a, b) / sqrt(dot(a, a) * dot(b, b)); }

int main()
{
    FILE *f = fopen("data.dat", "rb");
    fread_unlocked(a, sizeof(float), sizeof a / sizeof(float), f);
    fread_unlocked(b, sizeof(float), sizeof b / sizeof(float), f);
    fclose(f);
    volatile float ans;
    for (volatile int t = 0; t < T; t++)
        ans = vec_angle();
    assert(-1 <= ans && ans <= 1);
    f = fopen("data.dat", "ab");
    fwrite_unlocked(&ans, sizeof ans, 1, f);
    fclose(f);
    printf("%f\n", ans);
    return 0;
}
