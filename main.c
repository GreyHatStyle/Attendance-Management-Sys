//Final Code

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define mypath "Data/2024/"
#define check "sucessgooburrrr"
#define N 100000
char data[100000];

int size;
char *NameStorer[1000];

// Structure to send attendance
typedef struct data{
    char name[100];
    char atd[2];
}Atten;

int FileSize(){
    char str[N];
    int n=0;
    FILE *mainn = fopen("Data//main.txt","r");
    fscanf(mainn,"%[^\b]s",str);
    char *token = strtok(str,",");
    
    for(int i=0;token!=NULL;i++){
        n++;
        token = strtok(0,",");
    }
    size = n;
}

// Sorting function
static int myCompare(const void* a, const void* b)
{
 
    // setting up rules for comparison
    return strcmp(*(const char**)a, *(const char**)b);
}
 
// Function to sort the array
void sort(char* arr[], int n)
{
    // calling qsort function to sort the array
    // with the help of Comparator
    qsort(arr, n, sizeof(const char*), myCompare);
}

void MonthCoverter(int month, char *str){
    switch(month)
    {
        case 1: 
        strcpy(str,"Jan");
        break;
        case 2: 
        strcpy(str,"Feb");
        break;
        case 3: 
        strcpy(str,"Mar");
        break;
        case 4: 
        strcpy(str,"Apr");
        
        break;
        case 5: 
        strcpy(str,"May");

        break;
        case 6:
        strcpy(str,"June");
        
        break;
        case 7:
        strcpy(str,"July");
        
        break;
        case 8:
        strcpy(str,"Aug");
        
        break;
        case 9:
        strcpy(str,"Sept");
        
        break;
        case 10:
        strcpy(str,"Oct");
        
        break;
        case 11:
        strcpy(str,"Nov");
        
        break;
        case 12:
        strcpy(str,"Dec");
        
        break;
        default: 
        strcpy(str,"invalid");
        break;
    }
}

void PathConverter(char date[], char month[],char *path){
    strcat(path,month);
    strcat(path,"/");
    strcat(path,date);
    strcat(path,".txt");
}

void UniversalString(){
    FILE *mainn = fopen("Data//main.txt","r");
    fscanf(mainn,"%[^\b]s",data);
    char *token = strtok(data,",");
    
    for(int i=0;token!=NULL;i++){
        NameStorer[i] = token;
        token = strtok(0,",");
    }
    fclose(mainn);
}

#include <ctype.h>
// To send Attendance in date named file
// Status Done.
void Start_Attendance(){
    Atten list[size];
   
    // Loop to set names in Structure
    for(int i=0;i<size;i++){
        // getchar();
        strcpy(list[i].name,NameStorer[i]);
    }
    printf("Enter the attendance: \n");
    for(int i=0;i<size;i++){
        printf("%s :",list[i].name);
        scanf("%s",list[i].atd);
    }
    

    char mon[10];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int date = tm.tm_mday;
    int month = tm.tm_mon + 1;
    int year = tm.tm_year + 1900;
    char d[2];

    sprintf(d, "%d", date);// int date to string date
    MonthCoverter(month,mon);
    // Converting path
    char path[100] = "Data/2024/";
    PathConverter(d,mon,path);
    
    FILE *ftrr = fopen(path, "w");
    fclose(ftrr);
    // Creating a file for storing attendance
    FILE *ftr = fopen(path,"a+");
    for(int i=0;i<size;i++){
        fprintf(ftr,"%s - %s\n",list[i].name,list[i].atd);
    }
    fclose(ftr);
}

// To update attendance 
// Status Done.
void UpdateAttendance(){
    char date[10], name[50], month[10];
    int flag=0;
    printf("Please fill the following details: \n");
    printf("Date: ");
    getc(stdin);
    scanf("%s",date);
    printf("Month (Like Jan, Feb): ");
    getc(stdin);
    scanf("%s",month);
    

    // printf("===============\n%s-%s-%s\n===================",name,date,month);
    
    
    char path[100] = mypath;
    PathConverter(date,month,path);
    FILE *fptr = fopen(path,"r");
    if(fptr==NULL){
            printf("Not Attendance regestered for %s %s",date,month);
            return;
        }
    char str[100],par[10];
    char UpdName[100][100];
    int newS=0;
    // To find size of file
    while(!feof(fptr)){
        char ch = fgetc(fptr);
        if(ch=='\n'){newS++;}
    }

    // printf("size is:%d\n",newS);
    Atten lst[newS];
    rewind(fptr);
    
    for(int j=0;j<newS;j++){
        int i=0;
        while(!feof(fptr)){
            char ch = fgetc(fptr);
            str[i]=ch;
            i++;
            if(ch=='\n'){
                // printf("---\n%d\n--",ftell(fptr));
                fseek(fptr,-3,SEEK_CUR);
                // printf("===\n%d\n==",ftell(fptr));
                fscanf(fptr,"%s",par);
                // printf("Attendance: %s\n",par);
                fseek(fptr,2,SEEK_CUR);
                break;
            }
        }
        str[i]='\0';
        str[strlen(str)-5] = '\0'; // To access Name only
        // printf("----------\n%s\n--------------",str);
        // UpdName[j] = str;
        strcpy(UpdName[j],str);
        // printf("New Attd : %s is %s\n",str,par);
        strcpy(lst[j].name,str);
        strcpy(lst[j].atd,par);
    }

    printf("\nWhose attendance you want to change?\n");
    for(int k=0;k<newS;k++){
        printf("%d. %s is %s\n",k+1,lst[k].name,lst[k].atd);
    }
    printf("======================\nName: ");
    getc(stdin);
    gets(name);

    for(int i=0;i<newS;i++){
        // printf("Comaparing [%s] with [%s]",name,UpdName[i]);
        if(strcmp(name,UpdName[i])==0){
            printf("Found");
            flag=1;
            break;
        }
    }

    if(flag==1){
        printf("\nEntered.....");

        // Loop to update structure now
        for(int i=0;i<newS;i++){
            if(strcmp(lst[i].name,name)==0){
                char ap[2];
                printf("Found...\nMark A/P: ");
                scanf("%s",ap);
                puts(ap);
                strcpy(lst[i].atd,ap);
                break;
            }
        }
        fclose(fptr);
        FILE *ptr = fopen(path,"w");
        // Loop to send updated strucutre back and overwrite the file
        printf("New Attendance: \n");
        for(int i=0;i<newS;i++){
            fprintf(fptr,"%s - %s\n",lst[i].name,lst[i].atd);
            printf("%d. %s - %s\n",i+1,lst[i].name,lst[i].atd);
        }
        fclose(ptr);
    }
    else{
        printf("Error: Details are invalid.. Check for capital letters");
    }
}

// To send names to main.txt
// Success done
void AddNames(){
    char name[200], temp[20];
    printf("\nFirst word Capital of Name and Surname");
    printf("\nEnter New Name: ");
    getc(stdin);
    // gets(name);
    scanf("%[^\n]s",name);
    int z = size;
    NameStorer[z] = name;
    
    ++size;
    int n = size;
    // strcpy(NameStorer[z],name);
    int i,j;
    
    sort(NameStorer,n);
    // for(int i=0;i<size;i++){
    //     printf("==========\n%s\n==========",NameStorer[i]);
    // }
    FILE *ptr = fopen("Data/main.txt","w");
    for(int i=0;i<n;i++){
        fprintf(ptr,"%s,",NameStorer[i]);
    }
    fclose(ptr);
    printf("============\nEntered Name successfully!\n===========");
    printf("\nsize: %d",size);
    
}

// To display the attendance of any date
// Status done.
void Displayer(){
    char date[10], buff[N], month[10];
    printf("Please fill the following details: \n");
    printf("Date: ");
    scanf("%s",date);
    printf("Month (Like Jan, Feb): ");
    scanf("%s",month);
    char path[100] = mypath;
    PathConverter(date,month,path);
    
    FILE *ptr = fopen(path,"r");
    if(ptr==NULL){
        printf("Attendance of this date isn't registered...\n");
        return;
    }
    fscanf(ptr,"%[^\b]s",buff);
    printf("\n%sth of %s month Attendance is as follows\n",date,month);
    printf("%s",buff);
    fclose(ptr);
}

void DeleteName(){
    char name[100];
    printf("Which name do you want to remove?\n");
    for(int i=0;i<size;i++){
        printf("%s\n",NameStorer[i]);
    }
    printf("\nEnter the name now: ");
    getc(stdin);
    gets(name);
    int flag=0;
    for(int i=0;i<size;i++){
        if(strcmp(name,NameStorer[i])==0){
            NameStorer[i] = " ";
            flag=1;
            break;
        }
    }
    if(flag==0){
        printf("We couldn't find the name...\n");
        return;
    }
    FILE *fp = fopen("Data//main.txt","w");
    for(int i=0;i<size;i++){
        if(strcmp(NameStorer[i]," ")!=0){
            fprintf(fp,"%s,",NameStorer[i]);
        }
        
    }
    fclose(fp);
    printf("Name Deleted Successfully..");
    printf("\n======================\nPlease Exit the Program to save the changes\n");
    printf("==========================\n");

}

int main(){
    while(1){
        FileSize();
        
        UniversalString();
        
        int opt;

        // for(int i=0;i<size;i++){
        //     printf("%s\n",NameStorer[i]);
        // }
        printf("%d",size);
        printf("\nPlease Select Following options: \n");
        printf("1. Start Attendance\n2. Update\n3. Insert New Name\n4. Display Attendance");
        printf("\n5. Delete Name\n6. Exit");
        printf("\n\nOption: ");
        scanf("%d",&opt);
        if(opt==1){
            Start_Attendance();
        }
        else if(opt==2){
            UpdateAttendance();
        }
        else if(opt==3){
            AddNames();
        }
        else if(opt==4){
            Displayer();
        }
        else if(opt==5){
            DeleteName();
        }
        else if(opt==6){
            printf("\n Thanks for using our Project!");
            break;
        }
        else{
            printf("Invalid option\n");
        }
        
    
    
    }
}