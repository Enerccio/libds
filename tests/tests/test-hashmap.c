#include <stdio.h>
#include <CuTest.h>
#include <hmap.h>
#include <funcops.h>

#define TEST_LEN (1024)
typedef void* (*data_provider)();

void shuffle(int* array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void* random_int() {
  int msb = (rand() % 2) << 15;
  return (void*)(uintptr_t)((msb | rand())+1);
}

void* random_str() {
  int rlen = (rand() % 1024) + 10;
  char* s = malloc(sizeof(char) * rlen);
  s[rlen-1] = '\0';
  for (int i=0; i<rlen-1; i++) {
    s[i] = (rand() % 64) + 32;
  }
  return s;
}

void TestCreateHashMap(CuTest* tc) {
    hash_table_t* htable1 = create_uint32_table();
    hash_table_t* htable2 = create_uint64_table();
    hash_table_t* htable3 = create_string_table();

    CuAssertPtrNotNull(tc, htable1);
    CuAssertPtrNotNull(tc, htable2);
    CuAssertPtrNotNull(tc, htable3);

    destroy_table(htable1);
    destroy_table(htable2);
    destroy_table(htable3);
}

void TestInsertHashMapTyped(CuTest* tc, hash_table_t* table, data_provider dp) {
  CuAssertPtrNotNull(tc, table);
  CuAssertPtrNotNull(tc, dp);

  for (int i=0; i<TEST_LEN; i++) {
    CuAssertTrue(tc, !table_set(table, dp(), dp()));
  }
  CuAssertTrue(tc, table_size(table) == TEST_LEN);

  destroy_table(table);
}

void TestContainsHashMapTyped(CuTest* tc, hash_table_t* table, data_provider dp, eq_function_t eq) {
  CuAssertPtrNotNull(tc, table);
  CuAssertPtrNotNull(tc, dp);
  CuAssertPtrNotNull(tc, eq);

  void** tk = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tk);
  void** tv = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tv);

  for (int i=0; i<TEST_LEN; i++) {
    void* data1 = dp();
    void* data2 = dp();
    tk[i] = data1;
    tv[i] = data2;
    CuAssertTrue(tc, !table_set(table, data1, data2));
  }
  CuAssertTrue(tc, table_size(table) == TEST_LEN);

  for (int i=0; i<TEST_LEN; i++) {
    void* data = table_get(table, tk[i]);
    CuAssertPtrNotNull(tc, data);
    CuAssertTrue(tc, eq(tv[i], data) == true);
  }

  destroy_table(table);
}

void TestDeleteHashMapTyped(CuTest* tc, hash_table_t* table, data_provider dp, eq_function_t eq) {
  CuAssertPtrNotNull(tc, table);
  CuAssertPtrNotNull(tc, dp);
  CuAssertPtrNotNull(tc, eq);

  void** tk = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tk);
  void** tv = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tv);

  for (int i=0; i<TEST_LEN; i++) {
    void* data1 = dp();
    void* data2 = dp();
    tk[i] = data1;
    tv[i] = data2;
    CuAssertTrue(tc, !table_set(table, data1, data2));
  }
  CuAssertTrue(tc, table_size(table) == TEST_LEN);

  for (int i=0; i<TEST_LEN; i++) {
    CuAssertPtrNotNull(tc, tk[i]);
    void* data = table_get(table, tk[i]);
    CuAssertPtrNotNull(tc, data);
    CuAssertTrue(tc, eq(tv[i], data) == true);
  }

  for (int i=0; i<TEST_LEN; i++) {
    CuAssertPtrNotNull(tc, tk[i]);
    CuAssertTrue(tc, table_remove(table, tk[i]) == true);
  }

  CuAssertTrue(tc, table_size(table) == 0);

  destroy_table(table);
}

void TestRContainsHashMapTyped(CuTest* tc, hash_table_t* table, data_provider dp, eq_function_t eq) {
  CuAssertPtrNotNull(tc, table);
  CuAssertPtrNotNull(tc, dp);
  CuAssertPtrNotNull(tc, eq);

  void** tk = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tk);
  void** tv = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tv);
  int* ri = malloc(sizeof(int) * TEST_LEN);
  CuAssertPtrNotNull(tc, ri);

  for (int i=0; i<TEST_LEN; i++) {
    void* data1 = dp();
    void* data2 = dp();
    tk[i] = data1;
    tv[i] = data2;
    ri[i] = i;
    CuAssertTrue(tc, !table_set(table, data1, data2));
  }
  CuAssertTrue(tc, table_size(table) == TEST_LEN);

  shuffle(ri, TEST_LEN);

  for (int i=0; i<TEST_LEN; i++) {
    void* data = table_get(table, tk[ri[i]]);
    CuAssertPtrNotNull(tc, data);
    CuAssertTrue(tc, eq(tv[ri[i]], data) == true);
  }

  destroy_table(table);
}

void TestRDeleteHashMapTyped(CuTest* tc, hash_table_t* table, data_provider dp, eq_function_t eq) {
  CuAssertPtrNotNull(tc, table);
  CuAssertPtrNotNull(tc, dp);
  CuAssertPtrNotNull(tc, eq);

  void** tk = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tk);
  void** tv = malloc(sizeof(void*) * TEST_LEN);
  CuAssertPtrNotNull(tc, tv);
  int* ri = malloc(sizeof(int) * TEST_LEN);
  CuAssertPtrNotNull(tc, ri);

  for (int i=0; i<TEST_LEN; i++) {
    void* data1 = dp();
    void* data2 = dp();
    tk[i] = data1;
    tv[i] = data2;
    ri[i] = i;
    CuAssertTrue(tc, !table_set(table, data1, data2));
  }
  CuAssertTrue(tc, table_size(table) == TEST_LEN);

  shuffle(ri, TEST_LEN);

  for (int i=0; i<TEST_LEN; i++) {
    CuAssertPtrNotNull(tc, tk[ri[i]]);
    void* data = table_get(table, tk[ri[i]]);
    CuAssertPtrNotNull(tc, data);
    CuAssertTrue(tc, eq(tv[ri[i]], data) == true);
  }

  for (int i=0; i<TEST_LEN; i++) {
    CuAssertPtrNotNull(tc, tk[ri[i]]);
    CuAssertTrue(tc, table_remove(table, tk[ri[i]]) == true);
  }

  CuAssertTrue(tc, table_size(table) == 0);

  destroy_table(table);
}

void TestInsertHashMap(CuTest* tc) {
  TestInsertHashMapTyped(tc, create_uint32_table(), random_int);
  TestInsertHashMapTyped(tc, create_uint64_table(), random_int);
  TestInsertHashMapTyped(tc, create_string_table(), random_str);
}

void TestContainsHashMap(CuTest* tc) {
  TestContainsHashMapTyped(tc, create_uint32_table(), random_int, uint32_eq_function);
  TestContainsHashMapTyped(tc, create_uint64_table(), random_int, uint64_eq_function);
  TestContainsHashMapTyped(tc, create_string_table(), random_str, string_eq_function);
}

void TestDeleteHashMap(CuTest* tc) {
  TestDeleteHashMapTyped(tc, create_uint32_table(), random_int, uint32_eq_function);
  TestDeleteHashMapTyped(tc, create_uint64_table(), random_int, uint64_eq_function);
  TestDeleteHashMapTyped(tc, create_string_table(), random_str, string_eq_function);
}

void TestRContainsHashMap(CuTest* tc) {
  TestRContainsHashMapTyped(tc, create_uint32_table(), random_int, uint32_eq_function);
  TestContainsHashMapTyped(tc, create_uint64_table(), random_int, uint64_eq_function);
  TestContainsHashMapTyped(tc, create_string_table(), random_str, string_eq_function);
}

void TestRDeleteHashMap(CuTest* tc) {
  TestRDeleteHashMapTyped(tc, create_uint32_table(), random_int, uint32_eq_function);
  TestRDeleteHashMapTyped(tc, create_uint64_table(), random_int, uint64_eq_function);
  TestRDeleteHashMapTyped(tc, create_string_table(), random_str, string_eq_function);
}

CuSuite* test_suite() {
  CuSuite* suite = CuSuiteNew();

  CuSuiteAdd(suite, CuTestNew("Creating hash maps", TestCreateHashMap));
  CuSuiteAdd(suite, CuTestNew("Testing insert", TestInsertHashMap));
  CuSuiteAdd(suite, CuTestNew("Testing contains", TestContainsHashMap));
  CuSuiteAdd(suite, CuTestNew("Testing remove", TestDeleteHashMap));
  CuSuiteAdd(suite, CuTestNew("Testing contains - random", TestRContainsHashMap));
  CuSuiteAdd(suite, CuTestNew("Testing remove - random", TestRDeleteHashMap));

  return suite;
}

int main(void) {
  printf("\n===================\nHashmap test\n===================\n");

  CuString* output = CuStringNew();
  CuSuite* suite = test_suite();
  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  return suite->failCount > 0;
}
