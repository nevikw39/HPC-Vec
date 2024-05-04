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

_Alignas(16) float a[N], b[N];

float dot_naive(const float *const lhs, const float *const rhs)
{
    assert(sizeof(float) == 4);
    float y = 0;
    for (int i = 0; i < N; i += 4)
    {
        __m128 li = _mm_load_ps(lhs + i), ri = _mm_load_ps(rhs + i);
        __m128 tmp = _mm_mul_ps(li, ri);
        _Alignas(16) static float arr[4];
        _mm_store_ps(arr, tmp);
        y += *arr + 1[arr] + 2[arr] + 3[arr];
    }
    return y;
}

float vec_angle() { return dot_naive(a, b) / sqrt(dot_naive(a, a) * dot_naive(b, b)); }

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
