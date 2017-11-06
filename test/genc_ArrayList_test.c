#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_ArrayList.h"

struct Integer {
    int value;
};

struct Integer_ArrayList {
    GENC_ARRAY_LIST(struct Integer);
};

static void genc_ArrayList_test(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList, 10);
    struct Integer element1;
    element1.value = 100;
    struct Integer element2;
    element2.value = 200;
    struct Integer element3;

    GENC_ARRAY_LIST_PUSH(&arrayList, element1);
    GENC_ARRAY_LIST_PUSH(&arrayList, element2);
    GENC_ARRAY_LIST_POP(&arrayList, &element3);

    GENC_ARRAY_LIST_FOR_EACH(&arrayList, index) {
        printf("%d\n", GENC_ARRAY_LIST_GET(&arrayList, index).value);
    }
    printf("%d", element3.value);
    printf("\n");
}

static void genc_ArrayList_test_insertion(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList, 10);
    struct Integer element1;
    element1.value = 100;
    struct Integer element2;
    element2.value = 200;
    struct Integer element3;
    element3.value = 300;
    GENC_ARRAY_LIST_INSERT(&arrayList, 0, element1);
    GENC_ARRAY_LIST_INSERT(&arrayList, 0, element2);
    GENC_ARRAY_LIST_INSERT(&arrayList, 0, element3);
    GENC_ARRAY_LIST_FOR_EACH(&arrayList, index) {
        assert_int_equal(GENC_ARRAY_LIST_GET(&arrayList, index).value, (GENC_ARRAY_LIST_SIZE(&arrayList) - index) * 100);
        printf("%d\n", GENC_ARRAY_LIST_GET(&arrayList, index).value);
    }
    printf("\n");
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_ArrayList_test),
        cmocka_unit_test(genc_ArrayList_test_insertion)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
