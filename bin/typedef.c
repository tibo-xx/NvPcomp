typedef long type_t;
long t_long;
/* coment */
int function(void *p1, void *p2, int p3) {
  type_t ok1;           /* type_t is type! */
  static type_t ok2;    /* type_t is type! */
  /*int type_t = 0; */      /* type_t is identifier _not_ type! */
  t_long = 0;
  return 0;
}

