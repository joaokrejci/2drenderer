#include <check.h>
#include "../src/dynamic_array.h"

START_TEST(test_create_dynamic_array)
{
    dynamic_array_t da = create_dynamic_array(sizeof(int));

    ck_assert(da.data == NULL);
    ck_assert(da.data_size == sizeof(int));
    ck_assert(da.length == 0);
    ck_assert(da.__alloc_size == 0);

    delete_dynamic_array(&da);
}
END_TEST

START_TEST(test_insert_element) 
{
    dynamic_array_t da = create_dynamic_array(sizeof(long long));
    long long elements[4] = {25, 26, 27, 28};

    dynamic_array_insert(&da, (unsigned char*) elements, 2);

    long long *inner_array = (long long *) da.data;
    ck_assert(inner_array[0] == 25 && inner_array[1] == 26);
    ck_assert(da.__alloc_size == 5);
    ck_assert(da.length == 2);

    delete_dynamic_array(&da);
}
END_TEST

START_TEST(test_remove_element)
{
    dynamic_array_t da = create_dynamic_array(sizeof(long long));
    long long elements[] = {0,1,2,3,4,5};

    dynamic_array_insert(&da, (unsigned char*) elements, 6);
    dynamic_array_remove(&da, 0);
    dynamic_array_remove(&da, 4);
    dynamic_array_remove(&da, 2);

    long long *inner_array = (long long *) da.data;
    ck_assert(inner_array[0] == 25 && inner_array[1] == 26);
    ck_assert(da.__alloc_size == 5);
    ck_assert(da.length == 1);


    delete_dynamic_array(&da);
}
END_TEST

Suite * dynamic_array_suite() {
    Suite * s;
    TCase *tc_core;

    s = suite_create("Dynamic Array");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create_dynamic_array);
    tcase_add_test(tc_core, test_insert_element);
    tcase_add_test(tc_core, test_remove_element);

    suite_add_tcase(s, tc_core);

    return s;
}

int main() {
    Suite * suite = dynamic_array_suite();
    SRunner * sr = srunner_create(suite);

    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    return number_failed;
}