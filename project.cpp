#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int maxS = 100; //global variable 
const int maxG = 100;

double computeAverage(int grades[], int m) //first parameter for grade   and the second parameter for unmber of studetn
{
    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        sum += grades[i];
    }
    return sum / (double)m;
}

int heightG(double avgs[], int n)// the first parameter is a average  the second parameter is a number of student 
{
    int place = 0;
    for (int i = 1; i < n; i++)
    {
        if (avgs[i] > avgs[place]) 
            place = i;
    }
    return place;
}

int main()
{
    int N = 0, M = 0;
    string names[maxS];
    int grades[maxS][maxG];
    double averages[maxS];

    cout << "Enter number of students: ";
    cin >> N; //student number 

    cout << "Enter number of grades per student: ";
    cin >> M; //number of grade for per student 

    for (int i = 0; i < N; i++)
    {
        cout << "\nEnter name of student #" << i + 1 << ": ";
        cin >> names[i];

        cout << "Enter " << M << " grades: ";
        for (int j = 0; j < M; j++)
        {
            cin >> grades[i][j];  

            while (grades[i][j] < 0 || grades[i][j] > 100) // for error
            {
                cout << "Invalid! Enter a grade between 0 and 100: ";
                cin >> grades[i][j];
            }
        }

        averages[i] = computeAverage(grades[i], M);
    }

    int choice;
    do
    {
        cout << "\n========= MENU =========\n";
        cout << "1. Add new student\n";
        cout << "2. List students\n";
        cout << "3. Compute statistics\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) // for add student 
        {
            if (N >= maxS)  //maxs == 100   
            {
                cout << "Cannot add more students!\n";
                continue;
            }

            cout << "\nEnter student name: ";
            cin >> names[N];

            cout << "Enter " << M << " grades: ";
            for (int j = 0; j < M; j++)
            {
                cin >> grades[N][j];

                while (grades[N][j] < 0 || grades[N][j] > 100)
                {
                    cout << "Invalid! Enter grade (between 0 : 100): ";
                    cin >> grades[N][j];
                }
            }

            averages[N] = computeAverage(grades[N], M);
            N++; 

            cout << "Student added!\n";
        }

        else if (choice == 2)
        {
            cout << "\n---------------------------------------\n";
            cout << "| Name            | Average |\n";
            cout << "---------------------------------------\n";

            for (int i = 0; i < N; i++)
            {
                cout << "| " << left << setw(15) << names[i]
                     << "| " << fixed << setprecision(2)
                     << averages[i] << " |\n";
            }

            cout << "---------------------------------------\n";
        }

        else if (choice == 3)
        {
            double classSum = 0;
            int minGrade = 100, maxGrade = 0;

            for (int i = 0; i < N; i++)
            {
                classSum += averages[i];

                for (int j = 0; j < M; j++)
                {
                    if (grades[i][j] < minGrade)
                        minGrade = grades[i][j];
                    if (grades[i][j] > maxGrade)
                        maxGrade = grades[i][j];
                }
            }

            double classAverage = classSum / N;
            int topPlace = heightG(averages, N);

            cout << "\n===== CLASS STATISTICS =====\n";
            cout << "Class average: " << fixed << setprecision(2) << classAverage << endl;
            cout << "Minimum grade: " << minGrade << endl;
            cout << "Maximum grade: " << maxGrade << endl;
            cout << "Top student: " << names[topPlace]
                 << " (Average = " << averages[topPlace] << ")\n";
        }

    } while (choice != 4);

    cout << "\nprogram finished \n";






    return 0;
}
