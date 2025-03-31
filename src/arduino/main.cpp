void test_func(int);
#define SAMPLE_TIME 2000
#define TEST_VALUE 1000
void setup() {
  cli();
  CLKPR = (1 << CLKPCE);
  CLKPR = (1 << CLKPS0);
  sei();

  Serial.begin(9600);
}

void loop() {
  Serial.println("START");
  test_func(TEST_VALUE);
  Serial.println("END");
  delay(SAMPLE_TIME);
}

void test_func(int value) {
  int foo;
  for (volatile int i = 0; i < value; i++) {
    foo++;
    for (int j = 0; j < 10; j++)
      ; // just waste some time
  }
}
