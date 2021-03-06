#ifdef _WIN32
#include "../../src/common/stdint.h"
#define inline __forceinline
#else
#include <stdint.h>
#endif

#include "../../src/common/binomial.h"
#include "../../src/common/entropy.h"
#include "../../src/xorshift128/xorshift128.h"

typedef struct s_aug_state {
    xorshift128_state *rng;
    binomial_t *binomial;

    int has_gauss, shift_zig_random_int, has_uint32;
    double gauss;
    uint32_t uinteger;
    uint64_t zig_random_int;

} aug_state;

inline uint32_t random_uint32(aug_state* state)
{
    uint64_t temp;
    if (state->has_uint32)
    {
        state->has_uint32 = 0;
        return state->uinteger;
    }
    state->has_uint32 = 1;
    temp = xorshift128_next(state->rng);
    state->uinteger = (uint32_t)(temp >> 32);
    return (uint32_t)(temp & 0xFFFFFFFFLL);
}

inline uint64_t random_uint64(aug_state* state)
{
    return xorshift128_next(state->rng);
}

inline uint64_t random_raw_values(aug_state* state)
{
    return random_uint64(state);
}

inline double random_double(aug_state* state)
{
    uint64_t rn;
    int32_t a, b;
    rn = random_uint64(state);
    a = rn >> 37;
    b = (rn & 0xFFFFFFFFLL) >> 6;
    return (a * 67108864.0 + b) / 9007199254740992.0;
}

extern void set_seed(aug_state* state, uint64_t seed);

extern void set_seed_by_array(aug_state* state, uint64_t *vals, int count);

extern void jump_state(aug_state* state);

extern void entropy_init(aug_state* state);
