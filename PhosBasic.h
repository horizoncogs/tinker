typedef enum PhosBasicStatus {
    PhosBasicStatusOk,
    PhosBasicStatusOverflowError,
    PhosBasicStatusUndefrlowError,
    PhosBasicStatusUndefinedError
} PhosBasicStatus;

typedef struct PhosBase {
    int len;
    PhosBasicStatus (*sum) (void *opa, void *opb, void **res);
    PhosBasicStatus (*mul) (void *opa, void *opb, void **res);
    PhosBasicStatus (*neg) (void *opa, void **res);
    PhosBasicStatus (*inv) (void *opa, void **res);
    PhosBasicStatus (*one) (void **res);
    PhosBasicStatus (*nul) (void **res);
    PhosBasicStatus (*set) (void *opa, int opb, void **res);
    PhosBasicStatus (*get) (void *opa, int opb, void **res);
    PhosBasicStatus (*log) (void *opa);
} PhosBase;

extern const PhosBase PhosBaseInt;
extern const PhosBase PhosBaseFloat;
