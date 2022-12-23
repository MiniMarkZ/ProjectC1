#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
  char id[10];
  char name[50];
  char tpye[50];
  int price;
  int count;
} product;

/*Function prototype */
char *now();
void login();
int main();
void menu();
void edit();
int id_check();
void add();
void deletep();
void printdata();
void check();
void history();
void printhis();
/*in program */

/*time*/
char *now(char *dt){
  time_t current= time(NULL);
  struct tm *info = localtime(&current);
  strftime(dt,40, "%yY%mM%dD%HH%MM",info);
  return dt ;
}

/*login id password */
void login(){
  char id[50] ,pass[50];
  char id_user[]="admin",pass_user[]="1234";
  printf("Please enter ID :");
  scanf("%s",id);
  getchar();
  printf("Please enter password :");
  scanf("%s",pass);
  getchar();
  if(strcmp(id,id_user)==0&&strcmp(pass,pass_user)==0){
    system("cls");
    menu();
  }
  else{
    printf("password is Wrong");
    system("cls");
    main();
  }
}
/*print data*/
void printdata(){
  product printdata;
  FILE *f=fopen("datafile","r");
  char *token,str[100];
  while((fgets(str,100,f))!=NULL){
    token=strtok(str,",");
    int col=0;
    while(token!=NULL){
      switch(col){
        case 0:
          strcpy(printdata.id, token);
          break;
        case 1 :
          strcpy(printdata.name, token);
          break;
        case 2 :
          strcpy(printdata.tpye, token);
          break;
        case 3 :
          printdata.price=atoi(token);
          break;
      }
      col++;
      token=strtok(NULL,",");
    }
  printf("%s | %s | %s | %d \n",printdata.id,printdata.name,printdata.tpye,printdata.price);
  }
  printf("[0]Exit\n");
  fclose(f);
}
/*check id*/
int id_check(char *id){
  product check;
  char str[100],*token;
  FILE *odata=fopen("datafile","r");
  while((fgets(str,100,odata))!=NULL){
    token=strtok(str,",");
    int col=0;
    while(token!=NULL){
      switch(col){
        case 0:
          strcpy(check.id, token);
          break;
        case 1 :
          strcpy(check.name, token);
          break;
        case 2 :
          strcpy(check.tpye, token);
          break;
        case 3 :
          check.price=atoi(token);
          break;
      }
      col++;
      token=strtok(NULL,",");
    }
    if(strcmp(id,check.id)==0){
      fclose(odata);
      return 1;
    }
  }
  fclose(odata);
  return 0;
}

int numberid(char *id){
  FILE *f= fopen("Historyfile","r");
  int n=0;
  char   str[100],idproduct[10]="";
  while((fgets(str,100,f))!=NULL){
    for(int i =0 ; i<3;i++){
      idproduct[i]=str[i];
    }
    if(strcmp(idproduct,id)==0){
      if(str[18]=='A'){
        n++;
      }
      if(str[18]=='D'){
        n--;
      }
    }
  }
  fclose(f);
  return n;
}

/*check Product*/
void check(int a){
  product printdata;
  printf("\t\t\tCheck product\n");
  printf("========================================================================\n");
  printf("ID  |  Name   | Type  | Price   |  Count   \n");
  FILE *f=fopen("datafile","r");
  char *token,str[100];
  int n;
  while((fgets(str,100,f))!=NULL){
    n=0;
    token=strtok(str,",");
    int col=0;
    while(token!=NULL){
      switch(col){
        case 0:
          strcpy(printdata.id, token);
          break;
        case 1 :
          strcpy(printdata.name, token);
          break;
        case 2 :
          strcpy(printdata.tpye, token);
          break;
        case 3 :
          printdata.price=atoi(token);
          break;
      }
      col++;
      token=strtok(NULL,",");
    }
  printdata.count=numberid(printdata.id);
  printf("%s | %s | %s | %d | %d\n",printdata.id,printdata.name,printdata.tpye,printdata.price,printdata.count);
  }
  system("pause");
  system("cls");
  fclose(f);
  if(a==2){
    main();
  }
  else{
    menu();
  }
}
/*add Product*/
void add(){
  char eid[50],*id[50],dt[40];
  *id = eid;
  int checknum,number;
  printf("\t\t\tAdd product\n");
  printf("========================================================================\n");
  printf("ID  |  Name   | Type  | Price   |\n");
  printdata();
  printf("Enter ID :");
  scanf("%s",eid);
  if(strcmp(eid,"0")==0){
    system("cls");
    menu();
  }
  checknum=id_check(*id);
  if(checknum==1){
    FILE *f=fopen("Historyfile","a");
    printf("Enter number :");
    scanf("%d",&number);
    for(int i =0; i<number;i++){
      fprintf(f,"%s%sA\n",eid,now(dt));
    }
    fclose(f);
    system("cls");
    add();
  }
  else{
    printf("error please type again\n");
    system("pause");
    system("cls");
    add();
  }
}
/*Delete Product*/
void deletep(){
  char eid[50],*id[50],dt[40];
  *id = eid;
  int checknum,number;
  printf("\t\t\tDelete product\n");
  printf("========================================================================\n");
  printf("ID  |  Name   | Type  | Price   |\n");
  printdata();
  printf("Enter ID :");
  scanf("%s",eid);
  if(strcmp(eid,"0")==0){
    system("cls");
    menu();
  }
  checknum=id_check(*id);
  if(checknum==1){
      FILE *f=fopen("Historyfile","a");
    printf("Enter number :");
    scanf("%d",&number);
    for(int i =0; i<number;i++){
      fprintf(f,"%s%sD\n",eid,now(dt));
    }
    fclose(f);
    system("cls");
    deletep();
  }
  else{
    printf("error please type again\n");
    system("pause");
    system("cls");
    deletep();
  }
}
void printhis(){
  product printdata;
  FILE *f=fopen("datafile","r");
  char *token,str[100];
  while((fgets(str,100,f))!=NULL){
    token=strtok(str,",");
    int col=0;
    while(token!=NULL){
      switch(col){
        case 0:
          strcpy(printdata.id, token);
          break;
        case 1 :
          strcpy(printdata.name, token);
          break;
        case 2 :
          strcpy(printdata.tpye, token);
          break;
        case 3 :
          printdata.price=atoi(token);
          break;
      }
      col++;
      token=strtok(NULL,",");
    }
  printf("%s | %s | %s | %d |\n",printdata.id,printdata.name,printdata.tpye,printdata.price);
  }
  fclose(f);
}
/*History*/
void history(){
  int number;
  product printdata ;
  FILE *f=fopen("Historyfile", "r");
  printf("\t\t\tHistory\n");
  printf("========================================================================\n");
  printf("[1]All\n");
  printf("[2]one product\n");
  printf("[3]Exit\n");
  printf("Enter number :");
  scanf("%d",&number);
  if(number==3){
    fclose(f);
    system("cls");
    menu();
  }
  if(number==1){
    system("cls");
    char str[100],name[10]="",*token;
    printf("ID  |  Name   | Type  | date  |  time  | status \n");
    while((fgets(str,100,f))!=NULL){
      for(int a =0 ;a<3;a++){
        printf("%c",str[a]);
        name[a]=str[a];
      }
      printf(" | ");
      FILE *dataf=fopen("datafile","r");
      char strdata[100]="";
      while((fgets(strdata,100,dataf))!=NULL){
        token=strtok(strdata,",");
        int col=0;
        while(token!=NULL){
          switch(col){
            case 0:
              strcpy(printdata.id, token);
              break;
            case 1 :
              strcpy(printdata.name, token);
              break;
            case 2 :
              strcpy(printdata.tpye, token);
              break;
            case 3 :
              printdata.price=atoi(token);
              break;
          }
          col++;
          token=strtok(NULL,",");
        }
        if(strcmp(name,printdata.id)==0){
          printf("%s | %s",printdata.name,printdata.tpye);
          fclose(dataf);
          break;
        }
      }
      printf(" | ");
      for(int b=9;b<11;b++){
        printf("%c",str[b]);
      }
      printf("/");
      for(int j =6;j<8;j++){
        printf("%c",str[j]);
      }
      printf("/");
      for(int i =3;i<5;i++){
        printf("%c",str[i]);
      }
      printf(" | ");
      for(int c =12 ; c<14;c++){
        printf("%c",str[c]);
      }
      printf(":");
      for(int d =15;d<17;d++){
        printf("%c",str[d]);
      }
      if(str[18]=='A'){
        printf(" |   + ");
      }
      if(str[18]=='D'){
        printf(" |   - ");
      }
    printf("\n");
    }
    system("pause");
    fclose(f);
    system("cls");
    history();
  }
  else if(number==2){
    system("cls");
    char str[100],name[10]="",*token,id[10];
    printf("ID  |  Name   | Type  | Price   |\n");
    printhis();
    printf("Enter ID :");
    scanf("%s",id);
    system("cls");
    printf("ID  |  Name   | Type  | date  |  time  | status \n");
    while((fgets(str,100,f))!=NULL){
      for(int a =0 ;a<3;a++){
        name[a]=str[a];
      }
      if(strcmp(id,name)==0){
        printf("%s",name);
      printf(" | ");
      FILE *dataf=fopen("datafile","r");
      char strdata[100]="";
      while((fgets(strdata,100,dataf))!=NULL){
        token=strtok(strdata,",");
        int col=0;
        while(token!=NULL){
          switch(col){
            case 0:
              strcpy(printdata.id, token);
              break;
            case 1 :
              strcpy(printdata.name, token);
              break;
            case 2 :
              strcpy(printdata.tpye, token);
              break;
            case 3 :
              printdata.price=atoi(token);
              break;
          }
          col++;
          token=strtok(NULL,",");
        }
        if(strcmp(name,printdata.id)==0){
          printf("%s | %s",printdata.name,printdata.tpye);
          fclose(dataf);
          break;
        }
      }
      printf(" | ");
      for(int b=9;b<11;b++){
        printf("%c",str[b]);
      }
      printf("/");
      for(int j =6;j<8;j++){
        printf("%c",str[j]);
      }
      printf("/");
      for(int i =3;i<5;i++){
        printf("%c",str[i]);
      }
      printf(" | ");

      for(int c =12 ; c<14;c++){
        printf("%c",str[c]);
      }
      printf(":");
      for(int d =15;d<17;d++){
        printf("%c",str[d]);
      }
      if(str[18]=='A'){
        printf(" |   + ");
      }
      if(str[18]=='D'){
        printf(" |   - ");
      }
    printf("\n");
      }
    }
    system("pause");
    fclose(f);
    system("cls");
    history();
  }
  else{
    printf("error plase type again");
    system("pause");
    system("cls");
    fclose(f);
    history();
  }


}
/*Edit*/
void edit(){
  printf("\t\t\tNew product\n");
  printf("========================================================================\n");
  FILE *dataf = fopen("datafile","a");
  product editproduct;
  printf("ID product:");
  scanf("%s",editproduct.id);
  printf("name Product:");
  scanf("%s",editproduct.name);
  printf("Tpye Product:");
  scanf("%s",editproduct.tpye);
  printf("price :");
  scanf("%d",&editproduct.price);
  fprintf(dataf,"%s,",editproduct.id);
  fprintf(dataf,"%s,",editproduct.name);
  fprintf(dataf,"%s,",editproduct.tpye);
  fprintf(dataf,"%d\n",editproduct.price);
  fclose(dataf);
  printf("add newproduct completed \n");
  system("pause");
  system("cls");
  menu();
}
/* menu program*/
void menu(){
  int nummenu;
  printf("\t\t\tMenu\n");
  printf("========================================================================\n");
  printf("[1]Check products \n");
  printf("[2]Add products \n");
  printf("[3]Delete products \n");
  printf("[4]History \n");
  printf("[5]new product\n");
  printf("[6]Exit\n");
  printf("Please enter number :");
  scanf("%d",&nummenu);
  printf("========================================================================\n");
  if(nummenu==1){
    system("cls");
    check(1);
  }
  else if(nummenu==2){
    system("cls");
    add();
  }
  else if(nummenu==3){
    system("cls");
    deletep();
  }
  else if(nummenu==4){
    system("cls");
    history();
  }
  else if(nummenu==5){
    system("cls");
    edit();
  }
  else if(nummenu==6){
    system("cls");
    main();
  }
  else{
    printf("error\n");
    system("pause");
    system("cls");
    menu();
  }
}


int main(void) {
  int a;
  printf("Welcom to program enter key 1 for public User and 2 for admin\n");
  scanf("%d",&a);
  if(a==1){
    system("cls");
    check(2);
  }
  else if(a==2){
    system("cls");
    login();
  }
  else{
    printf("error \n");
    main();
  }
  printf("error 007");
  return 0;
}
