#include <stdio.h>

char attackString[] = "You Gao\nYou Gao\n";

int main() {
	int i;
	char *p = attackString;
	for (i=0; i <sizeof(attackString); i++){
		putchar(*p);
		p++;
	}
	return 1;
}
