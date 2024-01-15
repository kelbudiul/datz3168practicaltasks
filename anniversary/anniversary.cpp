#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype> // for std::tolower


// ----------------------------------------------------------------
// [Important!] Assumptions: Nearest birthdays taken under the assumption in 7 upcoming days range
// ----------------------------------------------------------------


struct Person {
    std::string name;
    std::string surname;
    std::string dateOfBirth;
};

struct Celebration {
    std::string date;
    int age;
    std::string name;
    std::string surname;
};

bool compareCelebrations(const Celebration& a, const Celebration& b) {
    if (a.date != b.date) {
        return a.date < b.date;
    }
    if (a.age != b.age) {
        return a.age < b.age;
    }
    if (a.surname != b.surname) {
        return a.surname < b.surname;
    }
    return a.name < b.name;
}

int calculateAge(const std::string& birthDate, const std::string& currentDate) {
    int birthDay, birthMonth, birthYear, currentDay, currentMonth, currentYear;
    sscanf(birthDate.c_str(), "%d.%d.%d", &birthDay, &birthMonth, &birthYear);
    sscanf(currentDate.c_str(), "%d.%d.%d", &currentDay, &currentMonth, &currentYear);

    int age = currentYear - birthYear;
    if (birthMonth > currentMonth || (birthMonth == currentMonth && birthDay > currentDay)) {
        age--;
    }

    return age;
}

bool isWithinRange(const std::string& birthDate, const std::string& currentDate, int rangeDays) {
    int birthDay, birthMonth, currentDay, currentMonth;
    sscanf(birthDate.c_str(), "%d.%d", &birthDay, &birthMonth);
    sscanf(currentDate.c_str(), "%d.%d", &currentDay, &currentMonth);

    // Consider birthdays on the exact day as well
    if (birthMonth == currentMonth && birthDay == currentDay) {
        return true;
    }

    // Only consider upcoming birthdays
    if (birthMonth < currentMonth || (birthMonth == currentMonth && birthDay <= currentDay)) {
        birthMonth += 12; // Move to the next year
    }

    return (birthMonth - currentMonth) * 30 + birthDay - currentDay <= rangeDays;
}

bool isDuplicate(const std::vector<Person>& people, const Person& newPerson) {
    // Convert names to lowercase for case-insensitive comparison
    std::string lowercaseName = newPerson.name;
    std::string lowercaseSurname = newPerson.surname;
    std::transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);
    std::transform(lowercaseSurname.begin(), lowercaseSurname.end(), lowercaseSurname.begin(), ::tolower);

    for (const auto& person : people) {
        std::string existingLowercaseName = person.name;
        std::string existingLowercaseSurname = person.surname;
        std::transform(existingLowercaseName.begin(), existingLowercaseName.end(), existingLowercaseName.begin(), ::tolower);
        std::transform(existingLowercaseSurname.begin(), existingLowercaseSurname.end(), existingLowercaseSurname.begin(), ::tolower);

        if (lowercaseName == existingLowercaseName &&
            lowercaseSurname == existingLowercaseSurname &&
            newPerson.dateOfBirth == person.dateOfBirth) {
            return true; // Duplicate entry found
        }
    }

    return false; // No duplicate entry found
}

int main() {
    std::ifstream inputFile("anniversary.in");
    std::ofstream outputFile("anniversary.out");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    std::vector<Person> people;
    std::vector<Celebration> celebrations;

    char command;
    while (inputFile >> command) {
        if (command == 'P') {
            Person person;
            inputFile >> person.name >> person.surname >> person.dateOfBirth;

            // Check for duplicate entry before adding
            if (!isDuplicate(people, person)) {
                people.push_back(person);
            }
        } else if (command == 'D') {
            std::string currentDate;
            inputFile >> currentDate;

            celebrations.clear();

            for (const auto& person : people) {
                if (isWithinRange(person.dateOfBirth, currentDate, 7)) {
                    int age = calculateAge(person.dateOfBirth, currentDate);
                    Celebration celebration;
                    celebration.date = currentDate;
                    celebration.age = age;
                    celebration.name = person.name;
                    celebration.surname = person.surname;
                    celebrations.push_back(celebration);
                }
            }

            std::sort(celebrations.begin(), celebrations.end(), compareCelebrations);

            // Print each celebration date only once
            std::vector<std::string> printedDates;
            for (const auto& celebration : celebrations) {
                if (std::find(printedDates.begin(), printedDates.end(), celebration.date) == printedDates.end()) {
                    outputFile << celebration.date << std::endl;
                    printedDates.push_back(celebration.date);
                }
                outputFile << celebration.age << " " << celebration.name << " " << celebration.surname << std::endl;
            }
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}

// -------------------------------------------------
// Algorithm: Employee Celebration Tracker
// Input: A file containing commands
// Output: A file with sorted celebrations information
// [Important!] Assumptions: Nearest birthdays taken under the assumption in 7 upcoming days range

// 1. Initialize Data Structures:
//    - Let people be an empty vector to store individual's information.
//    - Let celebrations be an empty vector to store upcoming celebration details.

// 2. Read Input Commands:
//    - Open the input file.
//    - While not end of file:
//      - Read a command from the file.

// 3. Process Each Command:
//    - For each command read:
//      - If it is a 'P' command (Person):
//        - Read the name, surname, and date of birth.
//        - Check for duplicate in people vector.
//        - If unique, add to people vector.
//      - If it is a 'D' command (Date):
//        - Read today's date.
//        - Clear the celebrations vector.
//        - For each person in people vector:
//          - If birthday within next 7 days:
//            - Calculate age.
//            - Add to celebrations vector.

// 4. Sort and Output Celebrations:
//    - Sort celebrations by date, then age, surname, and name.
//    - For each unique date in celebrations:
//      - Print details, starting with oldest person.
//      - If same age, sort by surname alphabetically.
//      - If same surname, sort by name alphabetically.

// 5. Repeat Until End of Input:
//    - Continue reading and processing commands until end of file is reached.

// 6. Write Output:
//    - Open the output file.
//    - Write the sorted celebrations information.

// 7. End of Program:
//    - Close the input and output files.
