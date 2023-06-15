#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>

int checking(char *str){
    int a = 0;
    while(str[a] != '\0'){
        a++;
    }
    if(a != 4){
        return 0;
    }
    for (int i = 0; i < 4;i++){
        if(str[i] < '0' || str[i] > '9'){
            return 0;
        }
    }
    for(int i = 0; i < 3;i++){
        for(int a = i + 1;a < 4;a++){
            if(str[i] == str[a])
            {
                return 0;
            }
        }
    }
    return 1;
}
char* readl(){
    char* buffer = malloc(4);
    char c;
    int fd = 0;
    int i,j = 0;
    while((i = read(fd,&c,1))){
        if(c == '\n'){
            return buffer;
        }
        buffer[j] = c;
        j++;
    }
    return NULL;
}
int have(char *z,char r){
    for(int i = 0; z[i] != '\0';i++){
        if(z[i] == r){
            return 0;
        }
    }
    return 1;
}
char* secredcode(){
    char* a = malloc(4);
    char b;
    srand(time(NULL));
    int i = 0;
    while(i < 4){
        b = rand()%8 + '0';
        if(have(a,b) != 0){
            a[i] = b;
            i++;
        }
    }
    return a;
}
int cmp(char* a,char* b){
    if(strlen(a) != strlen(b)){
        return 0;
    }
    if(a[1] == b[1]){
        return 1;
    }
    return 0;
}
void mastermind(int ac,char** av){
    char* code = malloc(4);
    code = NULL;
    int loops = 10;
    
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
 
    for(int i = 1; i < ac; i++){
        if(cmp(av[i], "-c") == 1){
            i++;
            code = av[i];
        }else if(cmp(av[i], "-t") == 1){
            i++;
            loops = atoi(av[i]);
        }
    }
    if(code == 0){
        code = secredcode();
    }
    for(int i = 0; i < loops; i++)
    {
        
        printf("---\n");
        printf("Round %d\n",i);
        write(1,">",1);
        char *input = readl();
        if(checking(input) == 0)
        {
            printf("Wrong input!\n");
            i--;
        }
        else if(checking(input) == 1)
        {
            int wellp = 0;
            int missp = 0;
            for(int i = 0; code[i] != '\0';i++)
            {
                if(code[i] == input[i]){
                    wellp++;
                }
            }
            for(int i = 0; code[i] != '\0';i++){
                for(int j = 0; input[j] != '\0'; j++){
                    if(code[i] == input[j] && i != j){
                        missp++;
                    }
                }
            }
            if(wellp == 4)
            {
                printf("Congratz! You did it!\n");return;
            }else{
                printf("\nWell placed pieces: %d\n", wellp);
                printf("Misplaced pieces: %d\n", missp);
            }
        }
    }
}
int main(int argc, char** argv) {
    mastermind(argc, argv);

    return 0;
}