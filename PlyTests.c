#include <assert.h>
#include "PlyTests.h"
#include "PlyInterface.c"

void ply_test_operations() {
    int a1 = 2, b1 = 3;
    float a2 = 1.5, b2 = 2.5;
    void *res1 = malloc(sizeof(int)), *res2 = malloc(sizeof(float));
    assert(PhosBaseInt.sum((void *)&a1, (void *)&b1, &res1) == PhosBasicStatusOk);
    assert(PhosBaseInt.mul((void *)&a1, (void *)&b1, &res1) == PhosBasicStatusOk);
    assert(PhosBaseInt.neg((void *)&a1, &res1) == PhosBasicStatusOk);
    assert(PhosBaseInt.inv((void *)&a1, &res1) == PhosBasicStatusUndefinedError);
    assert(PhosBaseInt.one(&res1) == PhosBasicStatusOk);
    assert(PhosBaseInt.nul(&res1) == PhosBasicStatusOk);

    assert(PhosBaseFloat.sum((void *)&a2, (void *)&b2, &res2) == PhosBasicStatusOk);
    assert(PhosBaseFloat.mul((void *)&a2, (void *)&b2, &res2) == PhosBasicStatusOk);
    assert(PhosBaseFloat.neg((void *)&a2, &res2) == PhosBasicStatusOk);
    assert(PhosBaseFloat.inv((void *)&a2, &res2) == PhosBasicStatusOk);
    assert(PhosBaseFloat.one(&res2) == PhosBasicStatusOk);
    assert(PhosBaseFloat.nul(&res2) == PhosBasicStatusOk);
};

void ply_test_polynomials() {
    int dat1[3] = {1, 2, 1};
    int dat2[2] = {3, 4};
    int val1 = 2, val2 = 1;
    PlyPolynomialMemory memory = {NULL, 0};
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_save_int(&memory, (void *)dat1, val1) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_save_int(&memory, (void *)dat2, val2) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_sum(&memory, 0, 1) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_multiply_scalar(&memory, 0, (void *)&val2) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_multiply_vector(&memory, 0, 1) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_compose(&memory, 0, 1) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(PlyPolynomialMemoryHandle.ply_polynomial_memory_delete(&memory, 2) == PlyPolynomialMemoryInterfaceStatusOk);
    assert(memory.length == 5);
};

void ply_test_everything() {
    printf("---\n");
    printf("Deploying unit tests...\n");
    printf("Now testing: operations...\n");
    ply_test_operations();
    printf("Done.\n");
    printf("Now testing: polynomials...\n");
    ply_test_polynomials();
    printf("Done.\n");
    printf("All tests passed.\n");
};
