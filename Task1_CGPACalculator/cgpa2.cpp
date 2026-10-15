#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // to ask for the number of semesters
    int semesters;
    cout << "How many semesters? ";
    cin >> semesters;
    // to create overall total
    double overallPoints = 0;
    double overallCredits = 0;

    // putting the actions of a whole semester in one loop
    for (int s = 0; s < semesters; s++)
    {
        int n;
        cout << "Semester " << s + 1 << " - how many courses? ";
        cin >> n;

        double totalPoints = 0;
        double totalCredits = 0;

        vector<double> grades;
        vector<double> creditList;

        for (int i = 0; i < n; i++)
        {
            double grade, credits;
            cout << "Course " << i + 1 << " grade: ";
            cin >> grade;
            cout << "Course " << i + 1 << " credit hours: ";
            cin >> credits;

            grades.push_back(grade);
            creditList.push_back(credits);

            totalPoints += grade * credits;
            totalCredits += credits;
        }

        for (int i = 0; i < n; i++)
        {
            cout << "Course " << i + 1 << ": grade: " << grades[i]
                 << ", credits: " << creditList[i] << endl;
        }
         // printing GPA, but first checking that credit hours != 0.
        if (totalCredits == 0)
        {
            cout << "Semester " << s + 1 << " has no credit hours, GPA cannot be calculated." << endl;
        }
        else
        {
            cout << "Semester " << s + 1 << " GPA = " << totalPoints / totalCredits << endl;
        }

        // feeding total at the end of each semester
        overallPoints += totalPoints;
        overallCredits += totalCredits;
    }
    cout << endl;
    // printing cgpa after the loop, but checking that credit hours != 0
    if (overallCredits == 0)
    {
        cout << "Zero(0) credit hours entered, GPA/CGPA cannot be calculated." << endl;
    }
    else
    {
        cout << "Your CGPA = " << overallPoints / overallCredits << endl;
    }
    return 0;
}