#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>

// Defining Student 
typedef struct student
{
    char name[20];
    unsigned int id;
    double grade;
}Student;

// Defining Course
typedef struct course
{
    char name[20];
    double avgrade;
    unsigned int totStu;
    Student * stuArr;
}Course;

// Defining School
typedef struct school
{
    char name[20];
    unsigned int totCourse;
    Course * coursArr;
}School;

// Creating Student

Student * CreateStu(){
    Student* newStu = (Student*)malloc(sizeof(Student));

    printf("Enter Student name: ");
    scanf("%s", newStu->name);
    printf("Enter Student Id: ");
    scanf("%d", newStu->id);
    printf("Enter Student grade: ");
    scanf("%d", newStu->grade);

    return newStu;
}

void update_avgrade(Course * cors){
    double tot_grad = 0;
    for (size_t i = 0; i < cors->totStu; i++){
        tot_grad += cors->stuArr[i].grade;
    }
    cors->avgrade = (tot_grad/cors->totStu);
}

// Creating Course

Course * CreateCourse(){
    Course* newCourse = (Course*)malloc(sizeof(Course));

    printf("Enter Course name: ");
    scanf("%s", newCourse->name);
    printf("Enter total Students: ");
    scanf("%d", newCourse->totStu);
    newCourse->stuArr = (Student*)malloc(sizeof(Student)* newCourse->totStu);
    // assert
    for (int  i = 0; i < newCourse->totStu; i++){
        printf("Enter Student details #%d \n", i+1);
        Student* newStud = CreateStu();
        newCourse->stuArr[i] = *newStud;
        free(newStud);
    }
    update_avgrade(newCourse);
    return newCourse;
}

// Creating School

School * CreateSchool(){
    School* newSchool = (School*)malloc(sizeof(School));

    printf("Enter School name: ");
    scanf("%s", newSchool->name);
    printf("Enter total Cource: ");
    scanf("%s", newSchool->totCourse);
    newSchool->coursArr = (Course*)malloc(sizeof(Course)* newSchool->totCourse);
    // assert
    for (int  i = 0; i < newSchool->totCourse; i++){
        printf("Enter Course details #%d \n", i+1);
        Course* newCource = CreateCourse();
        newSchool->coursArr[i] = *newCource;
        free(newCource);
    }
    
    return newSchool;
}

// Print Student details

void printStuDetails(Student* stu){
    printf("Student Name : %s \n", stu->name);
    printf("Student ID : %u \n", stu->id);
    printf("Student's grade : %d \n", stu->grade);
}

// Print Student details

void printCourseDetails(Course* cource){
    printf("Course Name : %s \n", cource->name);
    printf("Course avg grade : %lf \n", cource->avgrade);
    printf("Total student : %u \n", cource->totStu);
    for (size_t i = 0; i < cource->totStu; i++){
        printf("Student id %d: \t", i+1);
        printStuDetails(&(cource->stuArr[i]));
    }
}

// Printing student's course

void printStuCourse(School* skol, int stuID){
    
    printf("Student ID = %d\n", stuID);
    for (int i = 0; i < skol->totCourse ; i++)
    {
        for (size_t j = 0; j < skol->coursArr[i].totStu ; j++)
        {
            if (skol->coursArr[i].stuArr[j].id == stuID)
            {
                printf(" - %s\n", skol->coursArr[i].name);
                break; //If student was found, no need to keep tracking
            }   
        }   
    }
}

// Printing student who failed

void failedStu(Course* cours, double cutoff){

    printf("Students who failed in %s\n", cours->name);
    for (size_t i = 0; i < cours->totStu; i++){
        printf("Student who failed : \n");
        if (cours->stuArr[i].grade < cutoff)
        {
            printStuDetails(&(cours->stuArr[i]));
        }
    }
    printf("\n");
}

// Printing student who passed

void passdStu(Course* cours, double cutoff){

    printf("Students who passed in %s\n", cours->name);
    for (size_t i = 0; i < cours->totStu; i++){
        printf("Student who failed : \n");
        if (cours->stuArr[i].grade >= cutoff)
        {
            printStuDetails(&(cours->stuArr[i]));
            printf("\n");
        }
    }
    printf("\n");
}

// Print cources with pass average grade

void CourePassAvg(School * skol, double cutof){
    
    printf("Courses with passed average grade : \n");
    for (size_t i = 0; i < skol->totCourse; i++)
    {
        if (skol->coursArr[i].avgrade >= cutof)
        {
            printCourseDetails(&(skol->coursArr[i]));
            printf("\n");
        }
    }
    printf("\n");
}

// Print cources with failed average grade

void CoureFailAvg(School * skol, double cutof){

    printf("Courses with failed average grade : \n");
    for (size_t i = 0; i < skol->totCourse; i++)
    {
        if (skol->coursArr[i].avgrade < cutof)
        {
            printCourseDetails(&(skol->coursArr[i]));
            printf("\n");
        }  
    }
    printf("\n");
}

// Printing average grade between all courses

void Avgrde_Courses(School * skol){
    
    double total_grade = 0;
    for (size_t i = 0; i < skol->totCourse; i++){
        total_grade += skol->coursArr[i].avgrade;
    }    
    printf("The average grade of school : %s ,betewwn all the Courses : %d \n", skol->name, (total_grade/skol->totCourse));
}

// Printing course with highest avg grade

void highest_average(School * skool){
    Course * highest_avg;
    double highst_till = 0;
    for (size_t i = 0; i < skool->totCourse; i++)
    {
        if (skool->coursArr[i].avgrade>highst_till)
        {
            highst_till = skool->coursArr[i].avgrade;
            highest_avg = &(skool->coursArr[i]);
        }        
    }
    printf("The Course with highest average : ");
    printCourseDetails(highest_avg);
}

//Printing school details

void PrintSchoolDet(School * skol){
    for (size_t i = 0; i < skol->totCourse; i++){
        printCourseDetails(&(skol->coursArr[i]));
    }    
}

void freeStudents(Student* stu){
    free(stu);
}

void FreeCourse(Course* cors, int tot_cors){
    for (size_t i = 0; i < cors->totStu; i++){
        freeStudents(cors[i].stuArr);   
        cors[i].stuArr= NULL;
    }
    
}

void freeSchool(School * schol){
    FreeCourse(schol->coursArr,schol->totCourse);
    free(schol->coursArr);
    schol->coursArr = NULL;
    free(schol);
}

int main(){
    School* my_skol = CreateSchool();

    PrintSchoolDet(my_skol);
    printStuCourse(my_skol, 123);
    failedStu(&(my_skol->coursArr[0]), 50.00);
    passdStu(&(my_skol->coursArr[0]),50.00);

    freeSchool(my_skol);
}
