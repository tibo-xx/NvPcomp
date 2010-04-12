void swapnum(int *i, int *j) {
  int temp = i;
  i = j;
  j = temp;
}

int main(void) {
  int a = 10;
  int b = 20;

  swapnum(&a, &b);
  /*printf("A is %d and B is %d\n", a, b);*/
  return 0;
}