#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class Student {
private:
    string name;
    vector<int> grades;

public:
    // Constructor
    Student(const string& n, const vector<int>& g) : name(n), grades(g) {}

    // Getter functions
    string getName() const {return name; }

    double getAverage() const {
        double sum = 0;
        for (int grade : grades)
            sum += grade;
        return grades.empty() ? 0 : sum / grades.size();
    }

    const vector<int>& getGrades() const {return grades; }

    // the printing (separating of concerns)
    void print() const {
        cout << " | " << left << setw(15) << name
        << " | " << right << setw(7)
        << fixed << setprecision(2) << getAverage()
        << " |\n";
    }

};


class Classroom {
private:
    vector<Student> students;
    int numGrades;

public:
    // Constructor
    Classroom(int m) : numGrades(m) {}

    void addStudent(const Student& s){
        students.push_back(s);
    }

    void listStudents() const {
        cout << "\n---------------------------------------\n";
        cout << " | " << left << setw(15) << "Name"
        << " | " << right << setw(7) << "Average"
        << " |\n";
        cout << "---------------------------------------\n";

        for (const auto& s : students)
            s.print(); // Using Student's print method to separate concerns
            cout << "\n---------------------------------------\n";
    }

    void computeStatistics() const {
        if (students.empty()) {
            cout << "No students in the class!\n";
            return;
        }
        double classSum = 0;
        int minGrade = 100, maxGrade = 0;
        int topIndex = 0;

        for (size_t i = 0; i < students.size(); i++){
            double avg = students[i].getAverage();
            classSum += avg;

            const vector<int>& grades = students[i].getGrades();
            for (int g : grades){
                if (g < minGrade) minGrade = g;
                if (g > maxGrade) maxGrade = g;
            }
            if (avg > students[topIndex].getAverage())
                topIndex = i;
        }
        cout << "\n===== CLASS STATISTICS =====\n";
        cout << "Class average: " << fixed << setprecision(2) << classSum / students.size() << endl;
        cout << "Minimum grade: " << minGrade << endl;
        cout << "Maximum grade: " << maxGrade << endl;
        cout << "Top student: " << students[topIndex].getName() << " (Average = " << students[topIndex].getAverage() << ")\n";
    }

    void saveToFile(const string& filename) const{
        ofstream out(filename);
        out << students.size() << "," << numGrades << "\n";
        for (const auto& s : students){
            out << s.getName();
            for (int g : s.getGrades())
                out << "," << g;
            out << "\n";
        }
    }

    size_t size() const {return students.size();}
    int getNumGrades() const {return numGrades;}

};

int main() {
    ifstream in{"test.csv"};
    if (!in) {
        cout << "Error opening file!\n";
        return 0;
    }

    int N, M;
    string line;
    getline(in, line);
    stringstream ss(line);
    ss >> N;
    ss.ignore(); // ignore the comma ","
    ss >> M;

    Classroom classroom(M);

    for (int i = 0; i < N; i++){
        getline(in, line);
        stringstream s(line);
        string name;
        getline(s, name, ',');
        vector<int> grades;
        for (int j = 0; j < M; j++){
            int g;
            s >> g;
            s.ignore();
            if (g < 0 || g > 100) {
                cout << "Invalid grade!\n";
                return 0;
            }
            grades.push_back(g);
        }
        classroom.addStudent(Student(name, grades));
    }

    int choice;
    do {

        cout << "\n========= MENU =========\n";
        cout << "1. Add new student\n";
        cout << "2. List students\n";
        cout << "3. Compute statistics\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            cin.ignore();
            string name;
            cout << "Enter student name: ";
            getline(cin, name);

            vector<int> grades(M);
            cout << "Enter " << M << " grades (0-100), separated by space:\n";
            for (int j = 0; j < M; j++){
                cin >> grades[j];
                if (grades[j] < 0 || grades[j] > 100){
                    cout << "Invalid grade! Try again.\n";
                    j--;
                }
            }
            classroom.addStudent(Student(name, grades));
            cout << "Student addes successfully!\n";
        } else if (choice == 2)
            classroom.listStudents();
        else if (choice == 3)
            classroom.computeStatistics();
    }while (choice != 4);

    classroom.saveToFile("output.csv");
    cout << "Program finished, Thank you for your time!" << endl;


}
