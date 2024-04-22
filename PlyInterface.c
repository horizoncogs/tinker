#include "PlyInterface.h"

void ply_interface_start() {
    printf("---\n");
    printf("Welcome to the Ply Software v1.\n");
    printf("Created by Dmitry Chernov, B23-504 circa April 2024.\n");
    int choice = 0;
    PlyPolynomialMemory memory = {NULL, 0};
    while (1) {
        printf("---\n");
        printf("Please choose one of the following options to proceed:\n");
        printf("(1) Save polynomial to memory.\n");
        printf("(2) Delete polynomial from memory.\n");
        printf("(3) Add two stored polynomials and save the result.\n");
        printf("(4) Multiply stored polynomial with scalar and save the result.\n");
        printf("(5) Multiply two stored polynomials and save the result.\n");
        printf("(6) Compose two stored polynomials and save the result.\n");
        printf("(7) Display all currently stored polynomials.\n");
        printf("(8) Exit program.\n");
        printf("<Your choice> ");
        scanf("%d", &choice);
        if (choice == 1) {
            ply_interface_save(&memory);
        } else if (choice == 2) {
            ply_interface_delete(&memory);
        } else if (choice == 3) {
            ply_interface_sum(&memory);
        } else if (choice == 4) {
            ply_interface_multiply_scalar(&memory);
        } else if (choice == 5) {
            ply_interface_multiply_vector(&memory);
        } else if (choice == 6) {
            ply_interface_compose(&memory);
        } else if (choice == 7) {
            ply_interface_display(&memory);
        } else if (choice == 8) {
            break;
        } else {
            printf("---\n");
            printf("Invalid input, please try again.\n");
        }
    }
};

void ply_interface_save(PlyPolynomialMemory *memory) {
    int polt = 0, power = 0;
    void *data;
    printf("---\n");
    printf("Enter the type of polynomial to add:\n");
    printf("(1) Integer polynomial.\n");
    printf("(2) Floating-point polynomial.\n");
    printf("<Your choice> ");
    scanf("%d", &polt);
    if (polt != 1 && polt != 2) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the degree of polynomial (0 - 100 inclusive):\n");
    printf("<Your input> ");
    scanf("%d", &power);
    if (power < 0 || power > 100) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the coefficients:\n");
    printf("<Your input> ");
    if (polt == 1) {
        int pot = 0;
        data = malloc(sizeof(int) * (power + 1));
        for (int pos = 0; pos <= power; pos++) {
            scanf("%d", &pot);
            ((int *)data)[pos] = pot;
        }
        PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_save_int(memory, data, power);
        if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
            printf("---\n");
            printf("Memory interface error, operation interrupted.\n");
            return;
        }
    } else if (polt == 2) {
        data = malloc(sizeof(float) * (power + 1));
        float pot = 0;
        for (int pos = 0; pos <= power; pos++) {
            scanf("%f", &pot);
            ((float *)data)[pos] = pot;
        }
        PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_save_float(memory, data, power);
        if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
            printf("---\n");
            printf("Memory interface error, operation interrupted.\n");
            return;
        }
    }
    return;
};

void ply_interface_delete(PlyPolynomialMemory *memory) {
    if (memory->length == 0) {
        printf("---\n");
        printf("Not enough polynomials in memory, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the index of polynomial to delete:\n");
    int a = 0;
    printf("<Your input> ");
    scanf("%d", &a);
    if (!(a > 0 && a <= memory->length)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_delete(memory, a - 1);
    if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
        printf("---\n");
        printf("Memory interface error, operation interrupted.\n");
        return;
    }
    return;
};

void ply_interface_sum(PlyPolynomialMemory *memory) {
    if (memory->length == 0) {
        printf("---\n");
        printf("Not enough polynomials in memory, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the indices of polynomials to add:\n");
    int a = 0, b = 0;
    printf("<Your input> ");
    scanf("%d %d", &a, &b);
    if (!(a > 0 && a <= memory->length && b > 0 && b <= memory->length)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_sum(memory, a - 1, b - 1);
    if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
        printf("---\n");
        printf("Memory interface error, operation interrupted.\n");
        return;
    }
    return;
};

void ply_interface_multiply_scalar(PlyPolynomialMemory *memory) {
    if (memory->length == 0) {
        printf("---\n");
        printf("Not enough polynomials in memory, operation interrupted.\n");
        return;
    }
    int polt = 0, a = 0;
    printf("---\n");
    printf("Enter the type of polynomial to multiply:\n");
    printf("(1) Integer polynomial.\n");
    printf("(2) Floating-point polynomial.\n");
    printf("<Your choice> ");
    scanf("%d", &polt);
    if (polt != 1 && polt != 2) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the index of polynomial to multiply AND a scalar:\n");
    printf("<Your input> ");
    if (polt == 1) {
        int pot = 0;
        scanf("%d %d", &a, &pot);
        if (!(a > 0 && a <= memory->length)) {
            printf("---\n");
            printf("Invalid input, operation interrupted.\n");
            return;
        }
        PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_multiply_scalar(memory, a - 1, (void *)&pot);
        if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
            printf("---\n");
            printf("Memory interface error, operation interrupted.\n");
            return;
        }
    } else if (polt == 2) {
        float pot = 0;
        scanf("%d %f", &a, &pot);
        if (!(a > 0 && a <= memory->length)) {
            printf("---\n");
            printf("Invalid input, operation interrupted.\n");
            return;
        }
        PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_multiply_scalar(memory, a - 1, (void *)&pot);
        if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
            printf("---\n");
            printf("Memory interface error, operation interrupted.\n");
            return;
        }
    }
    return;
};

void ply_interface_multiply_vector(PlyPolynomialMemory *memory) {
    if (memory->length == 0) {
        printf("---\n");
        printf("Not enough polynomials in memory, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the indices of polynomials to multiply:\n");
    int a = 0, b = 0;
    printf("<Your input> ");
    scanf("%d %d", &a, &b);
    if (!(a > 0 && a <= memory->length && b > 0 && b <= memory->length)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_multiply_vector(memory, a - 1, b - 1);
    if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
        printf("---\n");
        printf("Memory interface error, operation interrupted.\n");
        return;
    }
    return;
};

void ply_interface_compose(PlyPolynomialMemory *memory) {
    if (memory->length == 0) {
        printf("---\n");
        printf("Not enough polynomials in memory, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the indices of polynomials to compose:\n");
    int a = 0, b = 0;
    printf("<Your input> ");
    scanf("%d %d", &a, &b);
    if (!(a > 0 && a <= memory->length && b > 0 && b <= memory->length)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    PlyPolynomialMemoryInterfaceStatus stat = PlyPolynomialMemoryHandle.ply_polynomial_memory_compose(memory, a - 1, b - 1);
    if (stat != PlyPolynomialMemoryInterfaceStatusOk) {
        printf("---\n");
        printf("Memory interface error, operation interrupted.\n");
        return;
    }
    return;
};

void ply_interface_display(PlyPolynomialMemory *memory) {
    printf("---\n");
    printf("The polynomials currently stored are listed below.\n");
    for (int pos = 0; pos < memory->length; pos++) {
        printf("(%d) Polynomial of degree %d.\n", pos + 1, memory->poly[pos].power);
        printf("    Coefficients: ");
        for (int power = 0; power <= memory->poly[pos].power; power++) {
            memory->poly[pos].base->log(memory->poly[pos].data + memory->poly[pos].base->len * power);
            printf(" ");
        }
        printf("\n");
    };
    return;
};
