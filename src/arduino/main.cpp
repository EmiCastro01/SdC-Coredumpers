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
    for (volatile j = 0; j < value; j++) {
      for
        volatile k = 0;
      k < value; k++)
      {
        foo++;
      }
    }
  }
  foo = 0;
}
