#include <fenv.h>
#include <math.h>

int
fraiseexcept(int excepts)
{
        __builtin_k1_wfxl(_K1_SFR_CS, (long long)(excepts & _K1_FPU_ALL_EXCEPTS) << 32);
	return 0;
}
