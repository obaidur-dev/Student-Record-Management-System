// Student Record Management System
// Developer: Obaidur Rahman
// College: Jamia Millia Islamia, New Delhi
// Language: C


#include <stdio.h>
#include <string.h>

typedef struct student {

    char name[50];
    int roll;
    int class;
    char section;
    float mark;
    }S;

    void addstudent(){
        S s1;
        FILE *f = fopen("StudentData.txt","ab");

        getchar();
        printf("Name    : ");
        fgets(s1.name, sizeof(s1.name),stdin);
        printf("\nRoll    : ");
        scanf("%d",&s1.roll);
        printf("\nClass   : ");
        scanf("%d",&s1.class);
        getchar();
        printf("\nSection : ");
        s1.section = getchar();
        printf("\nMarks   : ");
        scanf("%f",&s1.mark);
        
        fwrite(&s1,sizeof(S),1,f);
        fclose(f);
    }

   void showall (){
        S sx;
        FILE *f = fopen("StudentData.txt","rb");
        int check=0;

        while (fread(&sx,sizeof(S),1,f)==1 ) {
            check=1;

            printf("\nName    : %s", sx.name);
            printf("Roll    : %d\n", sx.roll);
            printf("Class   : %d\n", sx.class);
            printf("Section : %c\n", sx.section);
            printf("Marks   : %.2f\n", sx.mark);
            printf("--------------------\n");
        }
        if (check==0) {
            printf("-NO DATA FOUND-");
            }
        fclose(f);
    }

    void searchstudent(int r){
        S sx;
        FILE *f = fopen("StudentData.txt","rb+");
        int check=0;
        int loc=0;
        while (fread(&sx,sizeof(S),1,f)==1 ) {
            if (sx.roll == r)
            {
                check =1;
                printf("\nName    : %s", sx.name);
                printf("Roll    : %d\n", sx.roll);
                printf("Class   : %d\n", sx.class);
                printf("Section : %c\n", sx.section);
                printf("Marks   : %.2f\n", sx.mark);
                break;
            }loc++;
            
        }
        if (check==0) {
            printf("Roll not matched with any student ");
            }
        if (check!=0) 
        {
        
            printf("\nWhat do you want to do? \n1-Edit \n2-Delete \n3-Nothing \n");

            int ss;
            for (int i=0; i<1;) {
            printf("\nSelect only one 1/2/3 : ");
            scanf("%d",&ss);

            if (ss==1 || ss ==2 || ss == 3) {
                break;
                                 }

            else {
            printf("Wrong pick , Please select between 1 to 3");
                 }
            }

            if (ss ==1)
            {
                fclose(f);
                printf("\nEnter New Data");
                f = fopen("StudentData.txt", "rb+");

                fseek(f,loc*sizeof(S),SEEK_SET);
                getchar();
                printf("Name    : ");
                fgets(sx.name, sizeof(sx.name),stdin);
                printf("\nRoll    : ");
                scanf("%d",&sx.roll);
                printf("\nClass   : ");
                scanf("%d",&sx.class);
                getchar();
                printf("\nSection : ");
                sx.section = getchar();
                printf("\nMarks   : ");
                scanf("%f",&sx.mark);
                
                fwrite(&sx,sizeof(S),1,f);
            }

            else if (ss == 2)
            {
                fclose(f);
                FILE *original = fopen("StudentData.txt", "rb");
                FILE *temp = fopen("temp.txt", "wb");
                
                S copy;
                while (fread(&copy, sizeof(S), 1, original) == 1)
                {
                    if (copy.roll != r)
                    {
                        fwrite(&copy,sizeof(S),1,temp);
                    }
                    else {
                    continue;
                    }
                }
                
                fclose(original);
                fclose(temp);
                
                remove("StudentData.txt");
                rename("temp.txt", "StudentData.txt");
                
                printf("Student deleted.");
            }

            else {
            printf("program exited");
            }
        }
        fclose(f);
    }
int main (){
    
    FILE *f;
    //login interface
    printf("Sign in to your Account \n");
    int ac;
    for (int i=0; i<1;) {
    
        //UserID

        char UserID[20]="admin";
        char checkUserID[20];
        printf("User ID :");
        fgets(checkUserID,sizeof(checkUserID), stdin);
        checkUserID[strcspn(checkUserID,"\n")]='\0';

        //Password
        printf("Password :");
        FILE *pass;
        pass = fopen("password.dat", "rb");
        if(pass==NULL){

            pass = fopen("password.dat","wb");
            char defaultpass[30] = "admin123";
            fwrite(defaultpass, sizeof(defaultpass), 1, pass);
        fclose(pass);
        }char password[30];
        pass = fopen("password.dat", "rb");
        fread(password, sizeof(password), 1, pass);
        fclose(pass);

        char checkpassword[30];
        fgets(checkpassword,sizeof(checkpassword), stdin);
        checkpassword[strcspn(checkpassword,"\n")]='\0';

        //check input
        if (strcmp(checkUserID, UserID) != 0 ||
            strcmp(checkpassword, password) != 0) {
            printf("\nThe username or password you entered is incorrect \n \n");
            i=0;
        }

        else { printf("\nWelcome! Please select an action from the menu below \n");
            
            printf("0 -> Information & Help \n");
            printf("1 -> Enter New Student \n");
            printf("2 -> Display All Records \n");
            printf("3 -> Find Student \n");
            printf("4 -> Manage password \n");
            printf("5 -> EXIT \n \n");

            printf("type number between 1 to 5 for action : ");
            scanf("%d",&ac);
                if (ac==1 || ac==2 || ac==3 || ac==4 || ac==0) {i=1;}
                else if (ac==5) { i=0;}
                else {printf("Invalid input..!"); i=0;}
            }}

    if (ac==1){
       addstudent();
    }
    if (ac==2){
        showall();
    }
    if (ac==3){
        printf("Enter the student roll number : ");
        int sr;
        scanf("%d",&sr);
        searchstudent(sr);
    }
    if (ac==4){
        FILE *pass;
        getchar();
        printf("Enter the new password : ");
        pass = fopen("password.dat","wb");
        char newpass[30];
        fgets(newpass,sizeof(newpass), stdin);
        newpass[strcspn(newpass, "\n")] = '\0';
        fwrite(newpass, sizeof(newpass), 1, pass);
    fclose(pass);
    }
    
    if (ac==0) {
            printf("\n========================================\n");
            printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
            printf("========================================\n");
            printf("Developer : Obaidur Rahman\n");
            printf("College   : Jamia Millia Islamia, New Delhi\n");
            printf("Purpose   : Built as a 1st year project to\n");
            printf("            practice C file handling and structs\n");
            printf("\n--- HOW TO USE ---\n");
            printf("1 -> Add a new student record\n");
            printf("2 -> Display all stored records\n");
            printf("3 -> Find a student by roll number\n");
            printf("     (also lets you edit or delete)\n");
            printf("4 -> Change the login password\n");
            printf("5 -> Exit the program\n");
            printf("\n--- TECHNICAL NOTES ---\n");
            printf("- Data stored in binary (.dat/.txt) files\n");
            printf("- Binary storage is faster and more structured\n");
            printf("- Password saved in password.dat so it\n");
            printf("  persists even after program closes\n");
            printf("- fseek used to jump directly to any\n");
            printf("  record for editing without rewriting file\n");
            printf("========================================\n");
    }
    return 0;
}
