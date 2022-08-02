#include <iostream>
#include <string>
using namespace  std;
// Default Course Number: 3
#define COURSE_NUM 3
// Default Student Number: 10
#define STUDENT_NUM 10
// Just for alignment
string OutputSpace(int num)
{
    string space = "";
    for (int i = 0; i < num; i++)
    {
        space += " ";
    }
    return space;
}
int main() {
    string student_name[STUDENT_NUM];
    int student_score[COURSE_NUM][STUDENT_NUM];
    int max_score[COURSE_NUM];
    int min_score[COURSE_NUM];
    float student_average[STUDENT_NUM];
    float average_score[COURSE_NUM];
    // Step 1: input the information of students
    std::cout << "Please input the students' names and scores" << std::endl;
    for (int i=0;i<STUDENT_NUM;i++) {
        std::cin >> student_name[i];
        student_average[i] = 0;
        for (int j=0;j<COURSE_NUM;j++) {
            std::cin >> student_score[j][i];
            student_average[i] += (float )student_score[j][i];
        }
        student_average[i] /= COURSE_NUM;
    }
    // Step 2: Calculate the average, min, max of each course of each student
    for (int i=0;i<COURSE_NUM;i++) {
        average_score[i] = 0;
        max_score[i] = 0;
        min_score[i] = 100;
        for (int j=0;j<STUDENT_NUM;j++) {
            average_score[i] += (float )student_score[i][j];
            if (student_score[i][j] > max_score[i]) {
                max_score[i] = student_score[i][j];
            }
            if (student_score[i][j] < min_score[i]) {
                min_score[i] = student_score[i][j];
            }
        }
        average_score[i] /= STUDENT_NUM;
    }
    // Step 3: Output the information of students
    cout<<"no      name    score1  score2  score3  average"<<endl;
    for(int i=0;i<STUDENT_NUM;i++) {
        cout<<i+1<<OutputSpace(7-(i+1)/10)<<student_name[i]<<OutputSpace(11-student_name[i].size())<<student_score[0][i];
        cout<<"      "<<student_score[1][i]<<"      "<<student_score[2][i];
        cout<<"      "<<student_average[i]<<endl;
    }
    cout<<"        average";
    for(int i=0;i<COURSE_NUM;i++) {
        cout<<"    "<<average_score[i];
    }
    cout<<endl;
    cout<<"        min  ";
    for (int i=0;i<COURSE_NUM;i++) {
        cout << "      " << min_score[i];
    }
    cout << endl;
    cout<<"        max  ";
    for (int i=0;i<COURSE_NUM;i++) {
        cout << "      " << max_score[i];
    }
    cout << endl;
    return 0;
}
