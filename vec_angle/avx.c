#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <immintrin.h>

#ifndef N
#define N 16777216
#endif // N
#ifndef T
#define T 64
#endif // T
#ifndef EPS
#define EPS 1e-6f
#endif // EPS

_Alignas(32) float a[N], b[N];

float dot(const float *const lhs, const float *const rhs)
{
    assert(sizeof(float) == 4);
    __m256 y = _mm256_setzero_ps();
    for (int i = 0; i < N; i += 8)
    {
        __m256 li = _mm256_load_ps(lhs + i), ri = _mm256_load_ps(rhs + i);
        __m256 tmp = _mm256_mul_ps(li, ri);
        y = _mm256_add_ps(y, tmp);
    }
    return y[0] + y[1] + y[2] + y[3] + y[4] + y[5] + y[6] + y[7];
}

float vec_angle() { return dot(a, b) / sqrt(dot(a, a) * dot(b, b)); }

int main()
{
    FILE *f = fopen("data.dat", "rb");
    fread_unlocked(a, sizeof(float), sizeof a / sizeof(float), f);
    fread_unlocked(b, sizeof(float), sizeof b / sizeof(float), f);
    float ans;
    fread_unlocked(&ans, sizeof ans, 1, f);
    fclose(f);
    for (volatile int t = 0; t < T; t++)
    {
        volatile float res = vec_angle();
        assert(fabsf(res - ans) >= (fabsf(res) < fabsf(ans) ? fabsf(res) : fabsf(ans)) * EPS);
    }
    printf("%f\n", ans);
    return 0;
}
