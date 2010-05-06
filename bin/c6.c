/*! Compile test file 6
 *  \file c6.c
 *  \brief Demonstrates the ability of NvPcomp to handle declarations and
 *  \brief generate code for procedures with single nesting levels and
 *  \brief value parameters.  
 *  \author CMT, DRJ & BFB
 */

int func(int in) {
	int t;
	t = in;
	return in + 10;
}

int main() {
	int j;
	j = func(2);
	j = j*2;
	j = j/4;
}
