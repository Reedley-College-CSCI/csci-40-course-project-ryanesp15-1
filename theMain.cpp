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

//declaring const string vector for validation of input(moved them to global why not)
const vector<string> validPitchTypes = { "FB", "CH", "2S", "CC" };
const vector<string> validLocation = { "HA", "HM", "HI", "MA", "MM", "MI", "LA", "LM", "LI" };
const vector <string> validResult = { "S", "B", "F", "H", "O" };

//displays
void displayMenu();
void characterKey();

//add pitch feature. No const vect since data will change
void addNewPitch(vector<Pitch>& pitchlog);

//view pitches feature. For function look at Vincent in class display
void viewPitches(const vector<Pitch>& pitchLog);

//Calculating the stats function
void calculateStats(const vector<Pitch>& pitchLog);

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
            addNewPitch(pitchLog);
            break;
        case 2:
            cout << "Calling function viewPitches" << endl;
            viewPitches(pitchLog);
            break;
        case 3:
            cout << "Calling function calculateStats" << endl;
            calculateStats(pitchLog);
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
    
    pitchesToFile(pitchLog, filename);
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



/*addNewPitch function
* need input loop for adding new pitches and a validation input feature.
* need character X to allow user to quit.
* Need search to validate user inputs to valid inputs
* convert character inputs to uppercase. 
* variable for the actual newpitch being added.
*/
void addNewPitch(vector<Pitch>& pitchLog) {
    string input;

    cout << "ADDING NEW PITCH: " << endl;


    //needing main while loop, use sentinel value X for user to quit, have character key displayed in THISSS loop.
    while (true) {
        Pitch newPitch;
        characterKey();

        cout << "Enter Pitch Type (Enter 'X' to quit): ";
        cin >> input;

        if (input == "X" || input == "x") {
            cout << "Returning to main menu..." << endl;
            break;
        }

        //create do-while loops for each variable member of the class pitch. 
        // -Needing the code to convert char to uppercase.
        // -Needing search method to validate input to characters.
        // -total of 4 do-while loops, should be pretty much same

        //pitch type do while
        do {
            //need to convert characters to uppercase for cleanliness
            for (char& c : input) c = toupper(c);

            if (find(validPitchTypes.begin(), validPitchTypes.end(), input) != validPitchTypes.end()) {
                newPitch.type = input;
                break;
            }
            cout << "Invalid pitch type " << input << ". Please enter FB, 2S, CH, or CC: ";
            cin >> input;

            if (input == "X" || input == "x") { return; }

        } while (true);
        //pitch location do-while 
        cout << "Enter Pitch Location (ex. HA, MM, LI, etc.): ";
        cin >> input;
        do {
            for (char& c : input) c = toupper(c);

            if (find(validLocation.begin(), validLocation.end(), input) != validLocation.end()) {
                newPitch.location = input;
                break;
            }
            cout << "Invalid location " << input << ". Please enter a 2 letter location code (ex. MA, LI): ";
            cin >> input;
            if (input == "X" || input == "x") { return;}

        } while (true);

        //pitch result do-while
        cout << "Enter Pitch Result (S, B, F, H, O): ";
        cin >> input;
        do {
            for (char& c : input) c = toupper(c);

            if (find(validResult.begin(), validResult.end(), input) != validResult.end()) {
                newPitch.result = input;
                break;
            }

            cout << "Invalid result " << input << ". Please enter result code using (S, B, F, H, O): ";
            cin >> input;
            if (input == "X" || input == "x") { return;}

        } while (true);

        //pitch speed do-while
        cout << "Enter Speed of Pitch (mph): ";
        int tempSpeed;
        if (!(cin >> tempSpeed) || tempSpeed <= 0) {
            cin.clear();
            cout << "Invalid speed entered. Pitch deleted, restarting process..." << endl;
            continue;
        }
        newPitch.speed = tempSpeed;
        cin.ignore();

        //adding the pitch to our vector. Use output statement to verify successful output
        pitchLog.push_back(newPitch);
        cout << "Success! Pitch tracked: " << newPitch.type << " at " << newPitch.speed << "mph." << endl;
    }


}

//view pitches fucntion.
/*
* need to have a setw feature for display
* need to design display 
* need if statement to check if their is pitches to view, use statement to output error msg.
* 
*/
void viewPitches(const vector<Pitch>& pitchLog) {
    if (pitchLog.empty()) {
        cout << "No pitches recorded. Selection option number 1 to add data." << endl;
        return;
    }

    cout << "=================================================================" << endl;
    cout << "                        FULL PITCH LOG: " << endl;
    cout << "=================================================================" << endl;

    cout << setw(8) << left << "INDEX"
        << setw(15) << left << "PITCH TYPE"
        << setw(15) << left << "LOCATION"
        << setw(15) << left << "RESULT"
        << setw(10) << right << "SPEED (MPH)";
    cout << "-----------------------------------------------------------------" << endl;

    for (int i = 0; i < pitchLog.size(); ++i) {
        //call to pitch log and output stats
        const Pitch& p = pitchLog[i];
        cout << setw(8) << left << (i + 1)
            << setw(15) << left << p.type
            << setw(15) << left << p.location
            << setw(15) << left << p.result
            << setw(10) << right << p.speed << endl;
    }
    cout << "=================================================================" << endl;

}


void calcualteStats(const vector<Pitch>& pitchLog) {
    //need if statement to ensure data is in pitchLog.
    if (pitchLog.empty()) {
        cout << "Cannot calculate statistics. Pitch log is empty." << endl;
        return;
    }

    string pitchType;

    //do loop needs character toupper code
    
    do {
        cout << "-----STATS-----" << endl;
        cout << "Enter Pitch Type you would like to see statistics for (FB, 2S, CH, CC) or 'X' to return:" << endl;
        cin >> pitchType;
        if (pitchType == "X" || pitchType == "x") { return; }
        for (char& c : pitchType) c = toupper(c);

        //need to compare user input with valid const declared globally
        bool valid = false;
        for (const string& validCode : validPitchTypes) {
            if (pitchType == validCode) {
                valid = true;
                break;
            }
        }
        
        //if statement runs its else staement which has the search run. 
        if (!valid) {
            cout << " Invalid pitch type entered. Please try again." << endl;
            continue;
        }

        //need to initialize variables that will store data/results of putches.
        //total = all pitches thrown
        int totalCount = 0;
        int strikeCount = 0;
        int ballCount = 0;
        int foulCount = 0;
        int hitCount = 0;
        int outCount = 0;

        //linear search needed
        for (const Pitch& pitch : pitchLog) {
            if (pitch.type == pitchType) {
                totalCount++;

                if (pitch.result == "S") strikeCount++;
                else if (pitch.result == "B") ballCount++;
                else if (pitch.result == "F") foulCount++;
                else if (pitch.result == "H") hitCount++;
                else if (pitch.result == "O") outCount++;
            }
        }

        if (totalCount == 0) {
            cout << " No pitch statistics for pitch type " << pitchType << " found in the log." << endl;
            continue;
        }



    }
}