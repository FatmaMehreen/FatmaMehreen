#include <stdio.h>
#include <string.h>

#define NUM_TEAM 10
#define SQUAD_SIZE 5


void display_menu();
void enrollclub();
void addplayer();
void searchupdate();
void displayclubstatistics();
void handlerror();



int main(){

    while(1){
        display_menu();
    }
}

struct playerattributes{
    char name;
    int kitnumber;
    char club;
    struct age{

    };
    char position;

};

struct teamattributes{
    char name;
    int activesize;

};

void display_menu(){

int integer;
printf("choose: 1- enroll, 2- add player, 3- search update, 4- display club statistics, 5- handle error");
scanf("%d", &integer);

if (integer == 1){

    enrollclub();
}
else if (integer == 2){
    addplayer();
}
else if (integer == 3){
    searchupdate();
}
else if (integer == 4){
    displayclubstatistics();
}
else if (integer == 5){
    handleerror();
}
else{
    printf("invalid. please input another another");
}
}

void enrollclub(){
    char clubname;
    printf("enter club name");
    scanf("%c", clubname);



}

void addplayer(){
    char clubsel;
    printf("select club");
    scanf("%c", clubsel);
    printf("enter club details");
    


}

void searchupdate(){

}

void displaystatistics(){

}

void handlerror(){

}
