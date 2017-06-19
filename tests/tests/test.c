#include <stdio.h>
#include <CuTest.h>

CuSuite* test_suite() {
  CuSuite* suite = CuSuiteNew();
  return suite;
}

int main(void) {
  printf("\n===================\nTest of testing framework\n===================\n");

  CuString* output = CuStringNew();
  CuSuite* suite = test_suite();
  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  return suite->failCount > 0;
}
