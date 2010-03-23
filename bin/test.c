int i = 2;
int j = 128;

!!$

long z = -129;

float f = 2.3;

int func() {
	int r;
	struct dat {
		int something;
		long nothing = 6;
		!!$
	} data;
}
