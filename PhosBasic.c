#include <limits.h>
#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include "PhosBasic.h"


PhosBasicStatus sum_int(void *opa, void *opb, void **res) {
    int *resd = *(int **)res;
    int opad = *(int *)opa;
    int opbd = *(int *)opb;
    if (opad > 0 && opbd > 0)
        if (opad > INT_MAX - opbd) 
            return PhosBasicStatusOverflowError;
    if (opad < 0 && opbd < 0)
        if (opad < INT_MIN - opbd) 
            return PhosBasicStatusUndefrlowError;
    *resd = opad + opbd;
    return PhosBasicStatusOk;
};

PhosBasicStatus mul_int(void *opa, void *opb, void **res) {
    int *resd = *(int **)res;
    int opad = *(int *)opa;
    int opbd = *(int *)opb;
    if ((opad > 0 && opbd > 0) || (opad < 0 && opbd < 0))
        if (abs(opad) > INT_MAX / abs(opbd)) 
            return PhosBasicStatusOverflowError;
    if ((opad < 0 && opbd > 0) || (opad > 0 && opbd < 0))
        if (-abs(opad) > INT_MIN / abs(opbd))
            return PhosBasicStatusUndefrlowError;
    *resd = opad * opbd;
    return PhosBasicStatusOk;
};

PhosBasicStatus neg_int(void *opa, void **res) {
    int *resd = *(int **)res;
    int opad = *(int *)opa;
    if (opad == INT_MIN)
        return PhosBasicStatusOverflowError;
    *resd = -opad;
    return PhosBasicStatusOk;
};

PhosBasicStatus inv_int(void *opa, void **res) {
    return PhosBasicStatusUndefinedError;
};

PhosBasicStatus one_int(void **res) {
    int *resd = *(int **)res;
    *resd = (int) 1;
    return PhosBasicStatusOk;
};

PhosBasicStatus nul_int(void **res) {
    int *resd = *(int **)res;
    *resd = (int) 0;
    return PhosBasicStatusOk;
};

PhosBasicStatus set_int(void *opa, int opb, void **res) {
    int *resd = *(int **)res;
    int opad = *(int *)opa;
    resd[opb] = opad;
    return PhosBasicStatusOk;
};

PhosBasicStatus get_int(void *opa, int opb, void **res) {
    int *resd = *(int **)res;
    int *opad = (int *)opa;
    *resd = opad[opb];
    return PhosBasicStatusOk;
};

PhosBasicStatus log_int(void *opa) {
    int *opad = (int *)opa;
    printf("%d", *opad);
    return PhosBasicStatusOk;
};

PhosBasicStatus sum_flt(void *opa, void *opb, void **res) {
    // TODO: Add overflow checks.
    float *resd = *(float **)res;
    float opad = *(float *)opa;
    float opbd = *(float *)opb;
    *resd = opad + opbd;
    return PhosBasicStatusOk;
};
    
PhosBasicStatus mul_flt(void *opa, void *opb, void **res) {
    // TODO: Add overflow checks.
    float *resd = *(float **)res;
    float opad = *(float *)opa;
    float opbd = *(float *)opb;
    *resd = opad * opbd;
    return PhosBasicStatusOk;
};

PhosBasicStatus neg_flt(void *opa, void **res) {
    // TODO: Add overflow checks.
    float *resd = *(float **)res;
    float opad = *(float *)opa;
    *resd = -opad;
    return PhosBasicStatusOk;
};

PhosBasicStatus inv_flt(void *opa, void **res) {
    // TODO: Add overflow checks.
    float *resd = *(float **)res;
    float opad = *(float *)opa;
    *resd = 1 / opad;
    return PhosBasicStatusOk;
};

PhosBasicStatus one_flt(void **res) {
    float *resd = *(float **)res;
    *resd = (float) 1;
    return PhosBasicStatusOk;
};

PhosBasicStatus nul_flt(void **res) {
    float *resd = *(float **)res;
    *resd = (float) 0;
    return PhosBasicStatusOk;
};

PhosBasicStatus set_flt(void *opa, int opb, void **res) {
    float *resd = *(float **)res;
    float opad = *(float *)opa;
    resd[opb] = opad;
    return PhosBasicStatusOk;
};

PhosBasicStatus get_flt(void *opa, int opb, void **res) {
    float *resd = *(float **)res;
    float *opad = (float *)opa;
    *resd = opad[opb];
    return PhosBasicStatusOk;
};

PhosBasicStatus log_flt(void *opa) {
    float *opad = (float *)opa;
    printf("%f", *opad);
    return PhosBasicStatusOk;
};

const PhosBase PhosBaseInt = {
    .len = sizeof(int),
    .sum = sum_int,
    .mul = mul_int,
    .neg = neg_int,
    .inv = inv_int,
    .one = one_int,
    .nul = nul_int,
    .set = set_int,
    .get = get_int,
    .log = log_int
};

const PhosBase PhosBaseFloat = {
    .len = sizeof(float),
    .sum = sum_flt,
    .mul = mul_flt,
    .neg = neg_flt,
    .inv = inv_flt,
    .one = one_flt,
    .nul = nul_flt,
    .set = set_flt,
    .get = get_int,
    .log = log_flt
};
