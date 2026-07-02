// Student Record Management System
// Developer: Obaidur Rahman
// College: Jamia Millia Islamia, New Delhi
// Language: C
// Version : 2.0 (Bug fixes + Missing features + SHA-256 password hashing)


#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct student {

    char name[50];
    int roll;
    int class;
    char section;
    float mark;
    }S;

    //hashing
    void hash_password(const char *input, char *output){
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char *)input, strlen(input), hash);

        for (int i=0; i<SHA256_DIGEST_LENGTH; i++) {
            sprintf(output + (i*2), "%02x", hash[i]);
        }
        output[64] = '\0';
    }

    void addstudent(){
        S s1;
        FILE *f = fopen("StudentData.txt","ab");
        if (f==NULL) {
            printf("Error: Could not open student data file.\n");
            return;
        }

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

        if (s1.mark < 0 || s1.mark > 100) {
            printf("Invalid marks. Enter a value between 0 and 100.\n");
            fclose(f);
            return;
        }

        //check duplicate 
        FILE *check = fopen("StudentData.txt","rb");
        if (check != NULL) {
            S temp;
            while (fread(&temp,sizeof(S),1,check)==1) {
                if (temp.roll == s1.roll) {
                    printf("Roll %d already exists.\n", s1.roll);
                    fclose(check);
                    fclose(f);
                    return;
                }
            }
            fclose(check);
        }
        
        fwrite(&s1,sizeof(S),1,f);
        fclose(f);
        printf("Student added successfully.\n");
    }

   void showall (){
        S sx;
        FILE *f = fopen("StudentData.txt","rb");
        int check=0;

        if (f==NULL) {
            printf("No records found. File does not exist yet.\n");
            return;
        }

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

        if (f==NULL) {
            printf("No records found. File does not exist yet.\n");
            return;
        }

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
                f = NULL;
                printf("\nEnter New Data");
                f = fopen("StudentData.txt", "rb+");
                if (f==NULL) {
                    printf("Error: Could not open student data file.\n");
                    return;
                }

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

                if (sx.mark < 0 || sx.mark > 100) {
                    printf("Invalid marks. Enter a value between 0 and 100.\n");
                    fclose(f);
                    f = NULL;
                    return;
                }
                
                fwrite(&sx,sizeof(S),1,f);
            }

            else if (ss == 2)
            {
                fclose(f);
                f = NULL;
                FILE *original = fopen("StudentData.txt", "rb");
                FILE *temp = fopen("temp.txt", "wb");
                if (original==NULL || temp==NULL) {
                    printf("Error: Could not open file for delete.\n");
                    if (original!=NULL) fclose(original);
                    if (temp!=NULL) fclose(temp);
                    return;
                }
                
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
        if (f != NULL) {
            fclose(f);
        }
    }
int main (){
    
    //login 
    printf("Sign in to your Account \n");
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
            if (pass==NULL) {
                printf("Error: Could not create password file.\n");
                return 1;
            }
            char defaultpass[30] = "admin123";
            char defaulthash[65];
            hash_password(defaultpass, defaulthash);
        fwrite(defaulthash, sizeof(defaulthash), 1, pass);
        fclose(pass);
        }char password[65];
        pass = fopen("password.dat", "rb");
        if (pass==NULL) {
            printf("Error: Could not open password file.\n");
            return 1;
        }
        fread(password, sizeof(password), 1, pass);
        fclose(pass);

        char checkpassword[30];
        fgets(checkpassword,sizeof(checkpassword), stdin);
        checkpassword[strcspn(checkpassword,"\n")]='\0';

        char checkhash[65];
        hash_password(checkpassword, checkhash);

        //check input
        if (strcmp(checkUserID, UserID) != 0 ||
            strcmp(checkhash, password) != 0) {
            printf("\nThe username or password you entered is incorrect \n \n");
            i=0;
        }

        else { printf("\nLogin successful \n");
            i=1;
            }}

    //main menu loop
    while(1){
        printf("\nPlease select an action from the menu below \n");
        printf("0 -> Information & Help \n");
        printf("1 -> Enter New Student \n");
        printf("2 -> Display All Records \n");
        printf("3 -> Find Student \n");
        printf("4 -> Manage password \n");
        printf("5 -> EXIT \n \n");

        printf("type number between 0 to 5 for action : ");
        int ac;
        scanf("%d",&ac);

        if (ac==1){
           addstudent();
        }
        else if (ac==2){
            showall();
        }
        else if (ac==3){
            printf("Enter the student roll number : ");
            int sr;
            scanf("%d",&sr);
            searchstudent(sr);
        }
        else if (ac==4){
            FILE *pass;
            getchar();
            printf("Enter the new password : ");
            char newpass[30];
            fgets(newpass,sizeof(newpass), stdin);
            newpass[strcspn(newpass, "\n")] = '\0';

            char newhash[65];
            hash_password(newpass, newhash);

            pass = fopen("password.dat","wb");
            if (pass==NULL) {
                printf("Error: Could not open password file.\n");
            }
            else {
                fwrite(newhash, sizeof(newhash), 1, pass);
                fclose(pass);
                printf("Password changed successfully.\n");
            }
        }

        else if (ac==0) {
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
                printf("\n--- TECHNICAL NOTES (v2) ---\n");
                printf("- Data stored in binary (.dat/.txt) files\n");
                printf("- Binary storage is faster and more structured\n");
                printf("- Password is hashed with SHA-256 (OpenSSL)\n");
                printf("  before being saved, plaintext is never stored\n");
                printf("- fseek used to jump directly to any\n");
                printf("  record for editing without rewriting file\n");
                printf("- Every fopen is NULL-checked to avoid\n");
                printf("  crashes when a file is missing\n");
                printf("- Menu now loops until EXIT is selected\n");
                printf("========================================\n");
        }

        else if (ac==5){
            printf("\nExiting... Goodbye!\n");
            break;
        }

        else {
            printf("Invalid input..!\n");
        }
    }

    return 0;
}
