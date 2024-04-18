#include <string.h>
#include "PlyPolynomial.h"

/*
PhosPolyStatus com(PhosPoly *pol, PhosPoly *pom, PhosPoly *res) {
    if (pol->bas != pom->bas)
        return PhosPolyStatusError;
    res->pow = (pol->pow * pom->pow);
    res->dat = malloc((pol->pow * pom->pow + 1) * pol->bas->len);
    res->bas = pol->bas;
    void *ress = malloc(pol->bas->len);
    for (int pos = 0; pos <= pol->pow; pos++) {
        if (pos == 0) {
            pol->bas->set(pol->dat, 0, &res->dat);
        } else {
            PhosPoly *pod = pom;
            PhosPoly *podm = malloc (sizeof(PhosPoly));
            PhosPoly *pods = malloc (sizeof(PhosPoly));
            for (int pot = pos; pot > 1; pot--) {
                PhosPolyActions.mul(pod, pom, podm);
                pod = podm;
                podm = malloc (sizeof(PhosPoly));
            }
            pol->bas->get(pol->dat, pos, &ress);
            PhosPolyActions.scl(pod, ress, pods);
            pod = pods;
            PhosPolyActions.sum(res, pod, podm);
            *res = *podm;
        }
    }
    return PhosPolyStatusOk;
};
*/

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_save_int(PlyPolynomialMemory *memory, void *data, int power) {
    memory->poly = (PlyPolynomial *)realloc(memory->poly, sizeof(PlyPolynomial) * (memory->length + 1));
    PlyPolynomial poly_new = {power, data, &PhosBaseInt};
    memory->poly[memory->length++] = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_save_float(PlyPolynomialMemory *memory, void *data, int power) {
    memory->poly = (PlyPolynomial *)realloc(memory->poly, sizeof(PlyPolynomial) * (memory->length + 1));
    PlyPolynomial poly_new = {power, data, &PhosBaseFloat};
    memory->poly[memory->length++] = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_delete(PlyPolynomialMemory *memory, int poly) {
    PlyPolynomial* poly_new = (PlyPolynomial *)malloc(sizeof(PlyPolynomial) * (--memory->length));
    if (poly != 0)
        memcpy(poly_new, memory->poly, poly * sizeof(PlyPolynomial));
    if (poly != memory->length)
        memcpy(
            poly_new + (poly * sizeof(PlyPolynomial)),
            memory->poly + ((poly + 1) * sizeof(PlyPolynomial)),
            (memory->length - poly) * sizeof(PlyPolynomial)
        );
    memory->poly = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_calculate(PlyPolynomialMemory *memory, int poly, void *value, void **result) {
    const PhosBase *base = memory->poly[poly].base;
    void *running_sum = malloc(base->len);
    base->nul(&running_sum);
    for (int pos = 0; pos <= memory->poly[poly].power; pos++) {
        void *coefficient = malloc(base->len);
        base->get(memory->poly[poly].data, pos, &coefficient);
        for (int i = 0; i < pos; i++)
            base->mul(coefficient, value, &coefficient);
        base->sum(coefficient, running_sum, &running_sum);
    }
    *result = running_sum;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_sum(PlyPolynomialMemory *memory, int poly1, int poly2) {
    if (memory->poly[poly1].base != memory->poly[poly2].base)
        return PlyPolynomialMemoryInterfaceStatusError;
    const PhosBase *base = memory->poly[poly1].base;
    int power = memory->poly[poly2].power;
    if (memory->poly[poly1].power > memory->poly[poly2].power)
        power = memory->poly[poly1].power;
    void *new_data = malloc(base->len * (power + 1));
    for (int pos = 0; pos <= power; pos++) {
        void *coef1 = malloc(base->len), *coef2 = malloc(base->len);
        if (pos <= memory->poly[poly1].power && pos <= memory->poly[poly2].power) {
            base->get(memory->poly[poly1].data, pos, &coef1);
            base->get(memory->poly[poly2].data, pos, &coef2);
        } else if (pos <= memory->poly[poly1].power) {
            base->get(memory->poly[poly1].data, pos, &coef1);
            base->nul(&coef2);
        } else {
            base->nul(&coef1);
            base->get(memory->poly[poly2].data, pos, &coef2);
        }
        base->sum(coef1, coef2, &coef1);
        base->set(coef1, pos, &new_data);
    }
    memory->poly = (PlyPolynomial *)realloc(memory->poly, sizeof(PlyPolynomial) * (memory->length + 1));
    PlyPolynomial poly_new = {power, new_data, base};
    memory->poly[memory->length++] = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_multiply_scalar(PlyPolynomialMemory *memory, int poly, void *value) {
    const PhosBase *base = memory->poly[poly].base;
    int power = memory->poly[poly].power;
    void *new_data = malloc((power + 1) * base->len);
    for (int pos = 0; pos <= power; pos++) {
        void *coefficient = malloc(base->len);
        base->get(memory->poly[poly].data, pos, &coefficient);
        base->mul(coefficient, value, &coefficient);
        base->set(coefficient, pos, &new_data);
    }
    memory->poly = (PlyPolynomial *)realloc(memory->poly, sizeof(PlyPolynomial) * (memory->length + 1));
    PlyPolynomial poly_new = {power, new_data, base};
    memory->poly[memory->length++] = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_multiply_vector(PlyPolynomialMemory *memory, int poly1, int poly2) {
    if (memory->poly[poly1].base != memory->poly[poly2].base)
        return PlyPolynomialMemoryInterfaceStatusError;
    const PhosBase *base = memory->poly[poly1].base;
    int power = memory->poly[poly1].power + memory->poly[poly2].power;
    void *new_data = malloc((power + 1) * base->len);
    void *coefficient1 = malloc(base->len), *coefficient2 = malloc(base->len);
    for (int pos1 = 0; pos1 <= memory->poly[poly1].power; pos1++)
        for (int pos2 = 0; pos2 <= memory->poly[poly2].power; pos2++) {
            base->get(memory->poly[poly1].data, pos1, &coefficient1);
            base->get(memory->poly[poly2].data, pos2, &coefficient2);
            base->mul(coefficient1, coefficient2, &coefficient1);
            base->get(new_data, pos1 + pos2, &coefficient2);
            base->sum(coefficient1, coefficient2, &coefficient1);
            base->set(coefficient1, pos1 + pos2, &new_data);
        }
    memory->poly = (PlyPolynomial *)realloc(memory->poly, sizeof(PlyPolynomial) * (memory->length + 1));
    PlyPolynomial poly_new = {power, new_data, base};
    memory->poly[memory->length++] = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

PlyPolynomialMemoryInterfaceStatus ply_polynomial_memory_compose(PlyPolynomialMemory *memory, int poly1, int poly2) {
    if (memory->poly[poly1].base != memory->poly[poly2].base)
        return PlyPolynomialMemoryInterfaceStatusError;
    const PhosBase *base = memory->poly[poly1].base;
    int power = memory->poly[poly1].power * memory->poly[poly2].power;
    void *very_new_data = malloc((power + 1) * base->len);
    void *data2 = memory->poly[poly2].data;
    for (int pos1 = 0; pos1 <= memory->poly[poly1].power; pos1++) {
        void *new_data = malloc((power + 1) * base->len);
        if (pos1 == 0) {
            base->set(memory->poly[poly1].data, 0, &very_new_data);
        } else {
            int current_power = memory->poly[poly2].power;
            void *running_product = malloc((power + 1) * base->len);
            for (int pot = pos1; pot > 1; pot--) {
                int power_mult = current_power + memory->poly[poly2].power;
                void *coefficient1 = malloc(base->len), *coefficient2 = malloc(base->len);
                for (int pos2 = 0; pos2 <= current_power; pos2++)
                    for (int pos3 = 0; pos3 <= memory->poly[poly2].power; pos3++) {
                        base->get(running_product, pos2, &coefficient1);
                        base->get(memory->poly[poly2].data, pos3, &coefficient2);
                        base->mul(coefficient1, coefficient2, &coefficient1);
                        base->get(running_product, pos2 + pos3, &coefficient2);
                        base->sum(coefficient1, coefficient2, &coefficient1);
                        base->set(coefficient1, pos2 + pos3, &running_product);
                    }
                current_power += memory->poly[poly2].power;
            }
            void *coefficient = malloc(base->len);
            base->get(memory->poly[poly1].data, pos1, &coefficient);
            for (int pos = 0; pos <= current_power; pos++) {
                void *coefficient_scale = malloc(base->len);
                base->get(new_data, pos, &coefficient_scale);
                base->mul(coefficient_scale, coefficient, &coefficient_scale);
                base->set(coefficient_scale, pos, &new_data);
            }
            for (int pos = 0; pos <= power; pos++) {
                void *coef1 = malloc(base->len), *coef2 = malloc(base->len);
                base->get(new_data, pos, &coef1);
                base->get(very_new_data, pos, &coef2);
                base->sum(coef1, coef2, &coef1);
                base->set(coef1, pos, &very_new_data);
            }
        }
    }
    memory->poly = (PlyPolynomial *)realloc(memory->poly, sizeof(PlyPolynomial) * (memory->length + 1));
    PlyPolynomial poly_new = {power, very_new_data, base};
    memory->poly[memory->length++] = poly_new;
    return PlyPolynomialMemoryInterfaceStatusOk;
};

const PlyPolynomialMemoryInterface PlyPolynomialMemoryHandle = {
    .ply_polynomial_memory_save_int = ply_polynomial_memory_save_int,
    .ply_polynomial_memory_save_float = ply_polynomial_memory_save_float,
    .ply_polynomial_memory_delete = ply_polynomial_memory_delete,
    .ply_polynomial_memory_calculate = ply_polynomial_memory_calculate,
    .ply_polynomial_memory_sum = ply_polynomial_memory_sum,
    .ply_polynomial_memory_multiply_scalar = ply_polynomial_memory_multiply_scalar,
    .ply_polynomial_memory_multiply_vector = ply_polynomial_memory_multiply_vector,
    .ply_polynomial_memory_compose = ply_polynomial_memory_compose
};
