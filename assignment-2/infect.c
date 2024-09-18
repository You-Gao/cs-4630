#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // char * 7328 bytes = 7328 characters = 7328 ASCII characters
    char * buffer = (char *)malloc(sizeof(char) * 7328);
    // read target to edit
    FILE * target = fopen("target.exe", "r+b");

    fread(buffer, sizeof(char), 7328, target);

    // close files
    fclose(target);
    
    // prepare the rsp
    buffer[1102] = 0x83; // sub rsp, 0x10
    buffer[1103] = 0xec;
    buffer[1104] = 0x18;

    // replace nop with movl of the address of the string to print
    buffer[1105] = 0x68;

    // Fill in little-endian representation of 0x0804845C starting from offset 1104
    buffer[1106] = 0x5c; // Least significant byte
    buffer[1107] = 0x84;
    buffer[1108] = 0x04;
    buffer[1109] = 0x08; // Most significant byte



    // Insert 'call puts' instruction (e8 94 fe ff ff) at the appropriate offset
    buffer[1110] = 0xe8; // call opcode
    buffer[1111] = 0x94; // offset byte 1
    buffer[1112] = 0xfe; // offset byte 2
    buffer[1113] = 0xff; // offset byte 3
    buffer[1114] = 0xff; // offset byte 4

    // Return to the original program
    buffer[1115] = 0xc3; // ret opcode

    // Fill buffer with "Wahoo virus activated!" starting from offset 0x45C (1116 in decimal)
    buffer[1116] = 0x57; // W
    buffer[1117] = 0x61; // a
    buffer[1118] = 0x68; // h
    buffer[1119] = 0x6f; // o
    buffer[1120] = 0x6f; // o
    buffer[1121] = 0x20; //  
    buffer[1122] = 0x76; // v
    buffer[1123] = 0x69; // i
    buffer[1124] = 0x72; // r
    buffer[1125] = 0x75; // u
    buffer[1126] = 0x73; // s
    buffer[1127] = 0x20; //  
    buffer[1128] = 0x61; // a
    buffer[1129] = 0x63; // c
    buffer[1130] = 0x74; // t
    buffer[1131] = 0x69; // i
    buffer[1132] = 0x76; // v
    buffer[1133] = 0x61; // a
    buffer[1134] = 0x74; // t
    buffer[1135] = 0x65; // e
    buffer[1136] = 0x64; // d
    buffer[1137] = 0x21; // !
    buffer[1138] = 0x00; // null terminator

    // replace char 493 with push 0x0804844e in little endian
    buffer[1171] = 0x68;
    buffer[1172] = 0x4e;
    buffer[1173] = 0x84;
    buffer[1174] = 0x04;
    buffer[1175] = 0x08;
    buffer[1176] = 0xc3;

    // read infect to edit
    FILE * infect = fopen("infected-target.exe", "wb");
    // write to infect
    fwrite(buffer, sizeof(char), 7328, infect);

    fclose(infect);

    // free buffer
    free(buffer);

    return 0;
    
}