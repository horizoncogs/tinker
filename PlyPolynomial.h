#include "PhosBasic.c"

typedef enum PlyPolynomialMemoryInterfaceStatus {
    PlyPolynomialMemoryInterfaceStatusOk,
    PlyPolynomialMemoryInterfaceStatusError
} PlyPolynomialMemoryInterfaceStatus;

typedef struct PlyPolynomial {
    int power;
    void *data;
    const PhosBase *base;
} PlyPolynomial;

typedef struct PlyPolynomialMemory {
    PlyPolynomial *poly;
    int length;
} PlyPolynomialMemory;

typedef struct PlyPolynomialMemoryInterface {
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_save_int) (PlyPolynomialMemory *memory, void *data, int power);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_save_float) (PlyPolynomialMemory *memory, void *data, int power);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_delete) (PlyPolynomialMemory *memory, int poly);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_calculate) (PlyPolynomialMemory *memory, int poly, void *value, void **result);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_sum) (PlyPolynomialMemory *memory, int poly1, int poly2);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_multiply_scalar) (PlyPolynomialMemory *memory, int poly, void *value);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_multiply_vector) (PlyPolynomialMemory *memory, int poly1, int poly2);
    PlyPolynomialMemoryInterfaceStatus (*ply_polynomial_memory_compose) (PlyPolynomialMemory *memory, int poly1, int poly2);
} PlyPolynomialMemoryInterface;

extern const PlyPolynomialMemoryInterface PlyPolynomialMemoryHandle;
