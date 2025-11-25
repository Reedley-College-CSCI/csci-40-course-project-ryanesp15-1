// CSCI-40 Final Project
// Author: [Ryan Esparza]

/*
 * Description:This code allows simple data collection on pitchers in the sport baseball.
 * Users will be able to use program to view stats and save data between each session.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>


using namespace std;


//declaring struct pitch needed as foundation. struct will contain variables about the pitch, speed can be initialized as int.
struct Pitch {
    string type;
    string result;
    string location;
    int speed;
};


void displayMenu();
void characterKey();




/*loading pitches from file function
needing same things as pitchesFromFile
*/
void pitchesFromFile(vector<Pitch>& pitchLog, const string& filename);


/*
* Export pitch function. 
* needing the first parameter to call to te data type pitch s a pass by ref. 
* need to set parameters both parameters as pass by ref.
* need to declare as const so no change in data
* needing 2nd param fr filename
*/
void pitchesToFile(const vector<Pitch>& pitchLog, const string& filename);

int main() {
    
    //created vector to store pitches since we will be exporting them.
    //vector will be managing struct pitch. 
    //intitializing filename pitch_log as well, this will be exported.
    vector<Pitch> pitchLog;
    string filename = "pitch_log.txt";



    pitchesFromFile(pitchLog, filename);

    //creating the option menu for options on display menu initializing variable userChoice
    int userChoice = 0;
    while (userChoice != 5) {
        displayMenu();

        //need to create if statement with switch statement to allow for options displayMenu options to be selected
        //creating validation check
        if (!(cin >> userChoice)) {
            cin.clear();
            cout << "Invalid input. Please enter a number (1-5)." << endl;
            continue;
        }

        //for switch statements, putting an output statement to verify functionality.
        switch (userChoice) {
        case 1:
            cout << "Calling function addNewPitch" << endl;
            //will place function once created
            break;
        case 2:
            cout << "Calling function viewPitches" << endl;
            //will place function once created
            break;
        case 3:
            cout << "Calling function calculateStats" << endl;
            //will place function once created
            break;
        case 4:
            cout << "calling function exportData" << endl;
            //will place function once created
            break;
        case 5:
            cout << "Saving and exiting" << endl;
            pitchesToFile(pitchLog, filename);
            break;
        default:
            cout << "Invalid choice. Please select an option 1-5." << endl;
        }
    }
    
    characterKey();
    return 0;
}






/*Function displaying to users a key for their inputs.

  still need:
  -wanting this to display as the user is inputting information 
  -incorporate into while loop
*/
void characterKey() {
    cout << "-----------------------------------------------------------------" << endl;
    cout << "|                          Pitch Key:                           |" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "| Pitch Types: FB (Fastball), 2S (2-Seam FB),CH (Changeup),     |" << endl;
    cout << "|              CC (Circle Change)                               |" << endl;
    cout << "|                                                               |" << endl;
    cout << "| Location: HA (High Away), HM (High Middle), HI (High In)      |" << endl;
    cout << "|           MA (Middle Away), MM (Middle Middle), MI (Middle In)|" << endl;
    cout << "|           LA (Low Away), LM (Low Middle), LI (Low In)         |" << endl;
    cout << "|                                                               |" << endl;
    cout << "| Results: S (Strike), B (Ball), F (Foul), H (Hit), O (Out)     |" << endl;
    cout << "-----------------------------------------------------------------" << endl;
}


//display menu will allow users to select from
/*
    still need: 
    -create functions for options requiring functions
    -export data task, view pitches task, save and exit.
*/
void displayMenu() {
        cout << "----------------Pitch Tracker Menu---------------------" << endl;
        cout << "1. Add Pitch Entry" << endl;
        cout << "2. View All Pitches" << endl;
        cout << "3. Calculate Statistics" << endl;
        cout << "4. Export Data" << endl;
        cout << "5. Save and Exit" << endl;
        cout << "Please select an option 1-5: " << endl;
}


/*loading pitches from file function
needing to bring file in and have outputs if no data present/if data present. 
need infile to import data to speed location result and type.
declare variable that stores pitches imported
*/
void pitchesFromFile(vector<Pitch>& pitchLog, const string& filename) {
    ifstream inFile(filename);
    int pitchesLoaded = 0;

    if (inFile.is_open()) {
        Pitch pitch;

        while (inFile >> pitch.type
            >> pitch.location
            >> pitch.result
            >> pitch.speed) {
            pitchLog.push_back(pitch);
            pitchesLoaded++;
        }
        inFile.close();
        cout << "Success! Loaded " << pitchesLoaded << " pitches from " << filename << endl;
    } else {
        cout << "No log found, restarting program." << endl;
    }
}







/*Export pitch function
* needing ofstream to open the file
* use if statement for operation and for error message
* needing for loop that exports all variables for pitch
* need output statments for success or fail of export
*/
void pitchesToFile(const vector<Pitch>& pitchLog, const string& filename) {
    ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const Pitch& pitch : pitchLog) {
            outFile << pitch.type << " "
                << pitch.location << " "
                << pitch.result << " "
                << pitch.speed << endl;
        }
        outFile.close();
        cout << "Success! Saved " << pitchLog.size() << " pitches to " << filename << endl;
    }
    else {
        cout << "ERROR! Unable to save pitches to " << filename << endl;
    }
}