#include <stdio.h>
#include <string.h>
// #include <stdlib.h>


// sign_up and deletion --------------------------------
// 1. sign up ------------

int teacher_signup_gallery[6][2];
int student_signup_gallery[20][2];

int day_count[6];

char teachers[6][20];
char subjects[6][20];
char students[20][20];
char contacts[20][11];

int student_id, teacher_id;

struct signup
{
    char username[20];
    char subject[20];
    int pin;
    char mobile[11];
};



// 1.1 ---------
void teacher_signup()
{
    struct signup t;

    printf("Username: ");
    scanf("%s", t.username);

    printf("Subject: ");
    scanf("%s", t.subject);

    printf("Specify a PIN: ");
    scanf("%d", &t.pin);

    teacher_signup_gallery[teacher_id][0] = t.pin;
    teacher_signup_gallery[teacher_id][1] = teacher_id + 1;

    for (int a = 0; a < sizeof(t.username); a++)
    {
        teachers[teacher_id][a] = t.username[a];
    }

    for (int b = 0; b < sizeof(t.subject); b++)
    {
        subjects[teacher_id][b] = t.subject[b];
    }

    printf("\nRespected %s, signup successful... Your Teacher ID is: %d. Kindly remember this ID for further operations.", teachers[teacher_id], teacher_signup_gallery[teacher_id][1]);

    teacher_id++;
}

int change_teacher(int id){
    
    struct signup t;

    printf("Username: ");
    scanf("%s", t.username);

    // printf("Subject: ");
    // scanf("%s", t.subject);

    printf("Specify a PIN: ");
    scanf("%d", &t.pin);

    teacher_signup_gallery[id-1][0] = t.pin;
    teacher_signup_gallery[id-1][1] = id;

    for (int a = 0; a < sizeof(t.username); a++)
    {
        teachers[id-1][a] = t.username[a];
    }

    // for (int b = 0; b < sizeof(t.subject); b++)
    // {
    //     subjects[id-1][b] = t.subject[b];
    // }

    printf("\nRespected %s, signup successful... Your Teacher ID is: %d. Kindly remember this ID for further operations.", teachers[id-1], teacher_signup_gallery[id-1][1]);

}



// 1.2 ----------
void student_signup()
{
    struct signup s;

    printf("Student name: ");
    scanf("%s", s.username);

    printf("Mobile number: ");
    scanf("%s", s.mobile);

    printf("Specify a PIN: ");
    scanf("%d", &s.pin);

    student_signup_gallery[student_id][0] = s.pin;
    student_signup_gallery[student_id][1] = student_id + 1;

    for (int a = 0; a < sizeof(s.username); a++)
    {
        students[student_id][a] = s.username[a];
    }

    for (int b = 0; b < sizeof(s.mobile); b++)
    {
        contacts[student_id][b] = s.mobile[b];
    }

    printf("\nDear %s, signup successful... Your Student ID is: %d. Kindly remember this ID for further operations.", students[student_id], student_signup_gallery[student_id][1]);

    student_id++;
}




// 2. deletion of records ---------

// 2.1.1 -----------------
int add_teacher(int id){
    printf("\n\n\tThe attendance of subject %s is blocked!\nIt will be unblocked when a new teacher is assigned to this subject.\nIf you want to add a new teacher to the Teacher_ID %d, Press 1\nOR press 2 if not: ", subjects[id-1], id);

    int choice04;
    scanf("%d", &choice04);

    if (choice04==1){
        change_teacher(id);
    }
    else if(choice04==2){
        printf("\nThankYou!\n");
    } 
    else{
        printf("\nplease mind your input...");
    }

}

// 2.1 ----------
void delete_teacher()
{
    int id;
    printf("\nTeacher ID: ");
    scanf("%d", &id);

    if(teacher_signup_gallery[id-1][1]!=0){

    teacher_signup_gallery[id - 1][1] = 0;


    printf("\nrecord of teacher with Teacher_ID %d has been deleted sussceefully.", id);
    add_teacher(id);
    }

    else{
        printf("\nNo teacher with such ID exists...");
    }

}


// 2.2 ----------
void delete_student()
{
    int id;
    printf("\nEnter your Student ID: ");
    scanf("%d", &id);

    if(student_signup_gallery[id-1][1]!=0){

    student_signup_gallery[id - 1][1] = 0;


    printf("\nrecord of student with Student_ID %d has been deleted sussceefully.", id);
    }

    else{
        printf("\nNo student with such ID exists...");
    }
}




// 3. login -------------------------------------

struct login
{
    int id;
    int pin;
};

int attendance[6][20];


// 3.1.1 take attendance ------------
int take_attendance(int id)
{
    printf("\nFor taking attendance against every student,\npress 'p' for marking a student present\nor press 'a' for marking him/her absent\n\nAttendance of %s - Day : %d", subjects[id-1], day_count[id-1]+1);

    for (int a = 0; a < student_id; a++)
    {
        if(student_signup_gallery[a][1]!=0){
            char att;
            printf("\nAttendance of Student - %s: ", students[a]);
            scanf(" %c", &att);

        
            if (att == 'p')
            {
                attendance[id - 1][a] += 1;
            }

            else{
                attendance[id-1][a]+=0;
            }
        }

        else{
            printf("\nAttendane of Student %s (Blocked) : Student has left\n", students[a]);
        }
    // printf("%d", attendance[id-1][a]);
    }
    day_count[id-1]+=1;
}



// 3.1 ------------
void teacher_login()
{
    struct login t;
    printf("Teacher ID: ");
    scanf("%d", &t.id);
    printf("PIN: ");
    scanf("%d", &t.pin);

    if (t.pin == teacher_signup_gallery[t.id - 1][0] && teacher_signup_gallery[t.id-1][1]!=0)
    {
        printf("\nsuccessfully logged in as %s, teacher of %s...", teachers[t.id-1], subjects[t.id-1]);
        take_attendance(t.id);
    }
    else if (t.pin != teacher_signup_gallery[t.id - 1][0] && teacher_signup_gallery[t.id-1][1]!=0)
    {
        printf("\nInvalid credentials.");
    }
    else if (t.id>teacher_id){
        printf("\nno such Teacher_ID exists...");
    }
    else if (teacher_signup_gallery[t.id-1][1]==0){
        printf("\n[error] - Invalid user...\neither the user has been deleted or no user with such id exists.");
        add_teacher(t.id);
    }
    else{
        printf("\nno such Teacher_ID exists...");
    }
}



// 3.2.1 see attendance percentage ------------
int view_attendance(int id)
{
    if(teacher_id>0){
    printf("\nDear %s,", students[id-1]);
        for(int a=0; a<teacher_id; a++){
            float attendance_percentage;

            attendance_percentage = (attendance[a][id-1]/(float)day_count[a])*100;

            if (attendance_percentage>=0.00){

                printf("\nTotal classes of %s conducted till now are %d and your attendance in it is %.2f%%", subjects[a], day_count[a], attendance_percentage);
                printf("\nlectures attended in %s are: %d out of %d", subjects[a], attendance[a][id-1], day_count[a]);

                if (attendance_percentage>=75.00){
                    printf("\nYou are eligible to sit in %s exam!", subjects[a]);
                }
                else{
                    printf("\nYour attendance is less than 75%%, you may get a detention in this subject.\nPlease maintain your attendance...");
                }
            }

            else{

                printf("\nTotal classes of %s conducted till now are %d and your attendance in it is %d%%", subjects[a], day_count[a], 0);
                printf("\nlectures attended in %s are: %d out of %d", subjects[a], attendance[a][id-1], day_count[a]);

                if (attendance_percentage>=75.00){
                    printf("\nYou are eligible to sit in %s exam!", subjects[a]);
                }
                else{
                    printf("\nYour attendance is less than 75%%, you may get a detention in this subject.\nPlease maintain your attendance...");
                }
            }

            // printf("%d", attendance[a][id-1]);

        }
    }
    
    else{
        printf("\nNo classes have started yet!\n");
    }

}


// 3.2 ------------
void student_login()
{
    struct login s;
    printf("student ID: ");
    scanf("%d", &s.id);
    printf("PIN: ");
    scanf("%d", &s.pin);

    if (s.pin == student_signup_gallery[s.id - 1][0] && student_signup_gallery[s.id-1][1]!=0)
    {
        printf("\nsuccessfully logged in...");
        view_attendance(s.id);
    }
    else if (s.pin != student_signup_gallery[s.id - 1][0] && student_signup_gallery[s.id-1][1]!=0)
    {
        printf("\nInvalid credentials.");
    }
    else if (s.id>student_id){
        printf("\nno such Student_ID exists...");
    }
    else if (student_signup_gallery[s.id-1][1]==0){
        printf("\n[error] - Invalid user...\neither the user has been deleted or no user with such id exists.");
    }
    else{
        printf("\nno such Student_ID exists...");
    }
}




// display student details -------------

void display(){
    int id;
    printf("Enter Student_ID: ");
    scanf("%d", &id);

    if(student_signup_gallery[id-1][1]!=0){

    printf("\nDetails of student with Student_ID are as follows:\n");

    printf("Name: %s\n", students[id-1]);
    printf("Mobile number: %s\n\n", contacts[id-1]);

    view_attendance(id);
    }

    else{
        printf("Student does not exists. please enter a valid ID.");
    }
}


// search some student in the Record -------------
void search(){
    display();
}



// modify a student record --------------------------------------------------

void modify(){
    int id;
    char choice05;
    
    printf("\nEnter the ID of the Student whose record is to be modified: ");
    scanf("%d", &id);

    if(student_signup_gallery[id-1][1]!=0){

        printf("\nPress 'm' to change mobile number\nPress 'n' to change name of the student\nOR press 'p' to change pin: ");
        scanf(" %c", &choice05);

        if(choice05=='m'){
            char new_mobile[11];
            printf("\nNew mobile number: ");
            scanf("%s", new_mobile);

            for(int a=0; a<sizeof(new_mobile); a++){
                contacts[id-1][a]=new_mobile[a];
            }

            printf("\nMobiel number changed...\n");
        }

        else if(choice05=='n'){
            char new_name[20];
            printf("\nNew name: ");
            scanf("%s", new_name);

            for(int a=0; a<sizeof(new_name); a++){
                students[id-1][a]=new_name[a];
            }

            printf("\nName of the student has been changed...\n");
        }
        else if(choice05=='p'){
            int new_pin;
            printf("\nNew pin: ");
            scanf("%d", &new_pin);

            student_signup_gallery[id-1][0]=new_pin;
            
            printf("\nPIN changed...");
        }
        else{
            printf("\nplease mind your input...");
        }
    }

    else{
        printf("\nNo such student exists. Please enter a valid Student_ID.");
    }

}








// -----------------------------( handling permanency of data )-------------------------------


// 1.
void write_1(){
    FILE *fp1;

    fp1=fopen("AMS_teacher_signup_gallery_data.txt", "r+");

    // fprintf("PIN  ID\n");
    for(int a=0; a<teacher_id; a++){
        fprintf(fp1, "%d %d\n", teacher_signup_gallery[a][0], teacher_signup_gallery[a][1]);
    }

    fclose(fp1);
}

void assign_1(){
    FILE *fp1;

    fp1=fopen("AMS_teacher_signup_gallery_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        int x,y;
        fscanf(fp1, " %d", &x);
        fscanf(fp1, " %d", &y);

        teacher_signup_gallery[a][0]=x;
        teacher_signup_gallery[a][1]=y;
    }

    fclose(fp1);
}




// 2.
void write_2(){
    FILE *fp1;

    fp1=fopen("AMS_student_signup_gallery_data.txt", "r+");

    // fprintf("PIN  ID\n");
    for(int a=0; a<student_id; a++){
        fprintf(fp1, "%d %d\n", student_signup_gallery[a][0], student_signup_gallery[a][1]);
    }

    fclose(fp1);
}

void assign_2(){
    FILE *fp1;

    fp1=fopen("AMS_student_signup_gallery_data.txt", "r+");

    for(int a=0; a<student_id; a++){
        int x,y;
        fscanf(fp1, " %d", &x);
        fscanf(fp1, " %d", &y);

        student_signup_gallery[a][0]=x;
        student_signup_gallery[a][1]=y;
    }

    fclose(fp1);
}




// 3.
void write_3(){
    FILE *fp1;

    fp1=fopen("AMS_day_count_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        fprintf(fp1, "%d\n", day_count[a]);
    }

    fclose(fp1);
}

void assign_3(){
    FILE *fp1;

    fp1=fopen("AMS_day_count_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        int x;
        fscanf(fp1, " %d", &x);

        day_count[a]=x;
    }

    fclose(fp1);
}





// 4.
void write_4(){
    FILE *fp1;

    fp1=fopen("AMS_teachers_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        fprintf(fp1, "%s\n", teachers[a]);
    }

    fclose(fp1);
}

void assign_4(){
    FILE *fp1;

    fp1=fopen("AMS_teachers_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        char x[20];
        fscanf(fp1, " %s", x);

        for(int b=0; b<strlen(x); b++){
            teachers[a][b]=x[b];
        }
    }

    fclose(fp1);
}




// 5.
void write_5(){
    FILE *fp1;

    fp1=fopen("AMS_subjects_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        fprintf(fp1, "%s\n", subjects[a]);
    }

    fclose(fp1);
}

void assign_5(){
    FILE *fp1;

    fp1=fopen("AMS_subjects_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        char x[20];
        fscanf(fp1, " %s", x);

        for(int b=0; b<strlen(x); b++){
            subjects[a][b]=x[b];
        }
    }

    fclose(fp1);
}




// 6.
void write_6(){
    FILE *fp1;

    fp1=fopen("AMS_students_data.txt", "r+");

    for(int a=0; a<student_id; a++){
        fprintf(fp1, "%s\n", students[a]);
    }

    fclose(fp1);
}

void assign_6(){
    FILE *fp1;

    fp1=fopen("AMS_students_data.txt", "r+");

    for(int a=0; a<student_id; a++){
        char x[20];
        fscanf(fp1, " %s", x);

        for(int b=0; b<strlen(x); b++){
            students[a][b]=x[b];
        }
    }

    fclose(fp1);
}




// 7.
void write_7(){
    FILE *fp1;

    fp1=fopen("AMS_contacts_data.txt", "r+");

    for(int a=0; a<student_id; a++){
        fprintf(fp1, "%s\n", contacts[a]);
    }

    fclose(fp1);
}

void assign_7(){
    FILE *fp1;

    fp1=fopen("AMS_contacts_data.txt", "r+");

    for(int a=0; a<student_id; a++){
        char x[11];
        fscanf(fp1, " %s", x);

        for(int b=0; b<strlen(x); b++){
            contacts[a][b]=x[b];
        }
    }

    fclose(fp1);
}




// 8.
void write_8(){
    FILE *fp1;

    fp1=fopen("AMS_attendance_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        for(int b=0; b<student_id; b++){
            fprintf(fp1, "%d\n", attendance[a][b]);
        }
    }

    fclose(fp1);
}

void assign_8(){
    FILE *fp1;

    fp1=fopen("AMS_attendance_data.txt", "r+");

    for(int a=0; a<teacher_id; a++){
        for(int b=0; b<student_id; b++){
            fscanf(fp1, " %d\n", &attendance[a][b]);
        }
    }

    fclose(fp1);
}
// -------------------------------------------------------------------------------------







// Run functions -----------------------------------------------

void run1(){

    while (1)
    {
        FILE *fp9;

        // --------------------------------------------------------------
            fp9=fopen("AMS_primary_key.txt", "r+");

            fscanf(fp9, "%d", &teacher_id);
            fscanf(fp9, "%d", &student_id);

            fclose(fp9);
        // ---------------------------------------------------------------


        printf("\n\n---------(no. of subjects - %d)--------- Attendance MANAGEMENT SYSTEM OF SECTION-KOCFM ---------(total no. of students - %d)---------\n\n", teacher_id, student_id);

        int operation;

        printf("\nPRESS 0 TO QUIT\n\npress 1 to sign up\npress 2 to delete a record\npress 3 to login\npress 4 to display a student data\npress 5 to search a student record\npress 6 to modify a student record: ");
        scanf("%d", &operation);

        if (operation == 0)
        {
            break;
        }

        else if (operation == 1)
        {
            int choice01;
            printf("\nPRESS 0 TO QUIT\n\npress 1 for teacher sign up\npress 2 for student sign up: ");
            scanf("%d", &choice01);

            if (choice01 == 0)
            {
                break;
            }
            else if (choice01 == 1)
            {
                teacher_signup();
            }
            else if (choice01 == 2)
            {
                student_signup();
            }
            else{
                printf("\nplease mind your input...");
            }
        }

        else if (operation == 2)
        {
            int choice02;
            printf("\nPRESS 0 TO QUIT\n\npress 1 to delete teacher record\npress 2 to delete student record: ");
            scanf("%d", &choice02);

            if (choice02 == 0)
            {
                break;
            }
            else if (choice02 == 1)
            {
                delete_teacher();
            }
            else if (choice02 == 2)
            {
                delete_student();
            }
            else{
                printf("\nplease mind your input...");
            }
        }

        else if (operation==3){
            int choice03;
            printf("\nPRESS 0 TO QUIT\n\npress 1 for teacher login\npress 2 for student login: ");
            scanf("%d", &choice03);

            if (choice03 == 0)
            {
                break;
            }
            else if (choice03 == 1)
            {
                teacher_login();
            }
            else if (choice03 == 2)
            {
                student_login();
            }
            else{
                printf("\nplease mind your input...");
            }
        }

        else if(operation==4){
            display();
        }

        else if(operation==5){
            search();
        }

        else if(operation==6){
            modify();
        }

        else{
                printf("\nplease mind your input...");
            }

        
        // --------------------------------------------------------------
            fp9=fopen("AMS_primary_key.txt", "r+");

            fprintf(fp9, "%d\n", teacher_id);
            fprintf(fp9, "%d", student_id);

            fclose(fp9);
        // ---------------------------------------------------------------

    }


    // --------------------------------------------------------------
        write_1(); 
        write_2(); 
        write_3(); 
        write_4(); 
        write_5(); 
        write_6(); 
        write_7(); 
        write_8(); 
    // -------------------------------------------------------------- 
}




void run2(){

    while (1)
    {
        FILE *fp9;

        // --------------------------------------------------------------
            fp9=fopen("AMS_primary_key.txt", "r+");

            fscanf(fp9, "%d", &teacher_id);
            fscanf(fp9, "%d", &student_id);

            fclose(fp9);
        // ---------------------------------------------------------------


        // ---------------------------------------------------------------
            assign_1();
            assign_2();
            assign_3();
            assign_4();
            assign_5();
            assign_6();
            assign_7();
            assign_8();
        // ---------------------------------------------------------------



        printf("\n\n---------(no. of subjects - %d)--------- Attendance MANAGEMENT SYSTEM OF SECTION-KOCFM ---------(total no. of students - %d)---------\n\n", teacher_id, student_id);

        int operation;

        printf("\nPRESS 0 TO QUIT\n\npress 1 to sign up\npress 2 to delete a record\npress 3 to login\npress 4 to display a student data\npress 5 to search a student record\npress 6 to modify a student record: ");
        scanf("%d", &operation);

        if (operation == 0)
        {
            break;
        }

        else if (operation == 1)
        {
            int choice01;
            printf("\nPRESS 0 TO QUIT\n\npress 1 for teacher sign up\npress 2 for student sign up: ");
            scanf("%d", &choice01);

            if (choice01 == 0)
            {
                break;
            }
            else if (choice01 == 1)
            {
                teacher_signup();
            }
            else if (choice01 == 2)
            {
                student_signup();
            }
            else{
                printf("\nplease mind your input...");
            }
        }

        else if (operation == 2)
        {
            int choice02;
            printf("\nPRESS 0 TO QUIT\n\npress 1 to delete teacher record\npress 2 to delete student record: ");
            scanf("%d", &choice02);

            if (choice02 == 0)
            {
                break;
            }
            else if (choice02 == 1)
            {
                delete_teacher();
            }
            else if (choice02 == 2)
            {
                delete_student();
            }
            else{
                printf("\nplease mind your input...");
            }
        }

        else if (operation==3){
            int choice03;
            printf("\nPRESS 0 TO QUIT\n\npress 1 for teacher login\npress 2 for student login: ");
            scanf("%d", &choice03);

            if (choice03 == 0)
            {
                break;
            }
            else if (choice03 == 1)
            {
                teacher_login();
            }
            else if (choice03 == 2)
            {
                student_login();
            }
            else{
                printf("\nplease mind your input...");
            }
        }

        else if(operation==4){
            display();
        }

        else if(operation==5){
            search();
        }

        else if(operation==6){
            modify();
        }

        else{
                printf("\nplease mind your input...");
            }

        
        // --------------------------------------------------------------
            fp9=fopen("AMS_primary_key.txt", "r+");

            fprintf(fp9, "%d\n", teacher_id);
            fprintf(fp9, "%d", student_id);

            fclose(fp9);
        // ---------------------------------------------------------------


    // --------------------------------------------------------------
        write_1(); 
        write_2(); 
        write_3(); 
        write_4(); 
        write_5(); 
        write_6(); 
        write_7(); 
        write_8(); 
    // -------------------------------------------------------------- 
    
    }

}





// ------------------------------------- main function -------------------------------------

FILE *fp10;

int main()
{   
    int run_try;

    fp10=fopen("run_count.txt", "r+");
    fscanf(fp10, "%d", &run_try);
    fclose(fp10);

    // printf("\n%d\n", run_try);


    if(run_try==1){
        run1();
    }
    else{
        run2();
    }


    run_try++;

    fp10=fopen("run_count.txt", "r+");
    fprintf(fp10, "%d", run_try);
    fclose(fp10);

    return 0;
}
