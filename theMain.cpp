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
#include <algorithm> 
#include <sstream>

using namespace std;

struct Pitch {
    string type = "";
    string result = "";
    string location = "";
    int speed = 0;
};

const vector<string> validPitchTypes = { "FB", "CH", "2S", "CC" };
const vector<string> validLocation = { "HA", "HM", "HI", "MA", "MM", "MI", "LA", "LM", "LI" };
const vector <string> validResult = { "S", "B", "F", "H", "O" };

//displays
void displayMenu();
void characterKey();

//functions
void addNewPitch(vector<Pitch>& pitchlog);
void viewPitches(const vector<Pitch>& pitchLog);
void calculateStats(const vector<Pitch>& pitchLog);
void sortPitchesBySpeed(vector<Pitch>& pitchLog);
void pitchesFromFile(vector<Pitch>& pitchLog, const string& filename);
void pitchesToFile(const vector<Pitch>& pitchLog, const string& filename);
void exportDataTXT(vector<Pitch>& pitchLog, const string& filename);

int main() {
    vector<Pitch> pitchLog;
    string filename = "pitch_log.txt";

    pitchesFromFile(pitchLog, filename);

    int userChoice = 0;
    while (userChoice != 5) {
        displayMenu();

        if (!(cin >> userChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-5)." << endl;
            continue;
        }

        switch (userChoice) {
        case 1:
            cout << " " << endl;
            addNewPitch(pitchLog);
            break;
        case 2:
            cout << " " << endl;
            viewPitches(pitchLog);
            break;
        case 3:
            cout << " " << endl;
            calculateStats(pitchLog);
            break;
        case 4:
            cout << " " << endl;
            exportDataTXT(pitchLog, "pitch_data_report.txt");
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
    cout << "(Enter 'X' to quit): " << endl;
    cout << " " << endl;
}

void displayMenu() {
        cout << "----------------Pitch Tracker Menu---------------------" << endl;
        cout << "1. Add Pitch Entry" << endl;
        cout << "2. View All Pitches" << endl;
        cout << "3. Calculate Statistics" << endl;
        cout << "4. Export Data" << endl;
        cout << "5. Save and Exit" << endl;
        cout << "Please select an option 1-5: " << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "Please select an option: " << endl;
}

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


void addNewPitch(vector<Pitch>& pitchLog) {
    string input;

    cout << "ADDING NEW PITCH: " << endl;

    while (true) {
        Pitch newPitch;
        characterKey();
        
        //Pitch type do while
        do {
            cout << "Enter Pitch Type: ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (input.size() == 1 && (input[0] == 'X' || input[0] == 'x')) {
                goto end_pitch_input;
                break;
            }

            for (char& c : input) c = toupper(c);

            if (find(validPitchTypes.begin(), validPitchTypes.end(), input) != validPitchTypes.end()) {
                newPitch.type = input;
                break;
            }
            cout << "Invalid pitch type " << input << ". Please enter FB, 2S, CH, or CC: " << endl;
            cout << "Input pitch twice for correction: ";
            cin >> input;
            
        } while (true);
       
        //pitch location do while
        do {
            cout << "Enter Pitch Location (ex. HA, MM, LI, etc.): ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (input.size() == 1 && (input[0] == 'X' || input[0] == 'x')) {
                goto end_pitch_input;
            }
            

            for (char& c : input) c = toupper(c);

            if (find(validLocation.begin(), validLocation.end(), input) != validLocation.end()) {
                newPitch.location = input;
                break;
            }

            cout << "Invalid location " << input << ". Please enter a 2 letter location code (ex. MA, LI): " << endl;
            cout << " " << endl;

        } while (true);

        
        do {
            //pitch result do-while
            cout << "Enter Pitch Result (S, B, F, H, O): ";
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (input.size() == 1 && (input[0] == 'X' || input[0] == 'x')) {
                goto end_pitch_input;
            }
            
            for (char& c : input) c = toupper(c);

            if (find(validResult.begin(), validResult.end(), input) != validResult.end()) {
                newPitch.result = input;
                break;
            }

            cout << "Invalid result " << input << ". Please enter result code using (S, B, F, H, O): ";

        } while (true);

        //pitch speed do-while
        cout << "Enter Speed of Pitch (mph): ";
        int tempSpeed;


        if (!(cin >> tempSpeed)) {
            cin.clear();
            string temp;
            cin >> temp;

            if (temp.size() == 1 && (temp[0] == 'x' || temp[0] == 'X')) {
                goto end_pitch_input;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid speed. Pitch discarded. Restarting input..." << endl;
            continue;
        }

        if (tempSpeed <= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Speed (must be positive). Pitch Discarded. Restarting input..." << endl;
            continue;
        }

        newPitch.speed = tempSpeed;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        pitchLog.push_back(newPitch);
        cout << " " << endl;
        cout << "Success! Pitch tracked: " << newPitch.type << " at " << newPitch.speed << "mph." << endl;
    }
end_pitch_input:
    cout << "Returning to main menu..." << endl;
    cout << " " << endl;
}

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
        << setw(10) << right << "SPEED (MPH)" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    for (int i = 0; i < pitchLog.size(); ++i) {
        const Pitch& p = pitchLog[i];
        cout << setw(8) << left << (i + 1)
            << setw(15) << left << p.type
            << setw(15) << left << p.location
            << setw(15) << left << p.result
            << setw(10) << right << p.speed << endl;
    }
    cout << "=================================================================" << endl;
    cout << " " << endl;

}


void calculateStats(const vector<Pitch>& pitchLog) {
    if (pitchLog.empty()) {
        cout << "[ERROR] Cannot calculate statistics. Pitch log is empty." << endl;
        return;
    }

    string pitchType;
    
    do {
        cout << "-----STATS-----" << endl;
        cout << "Enter Pitch Type you would like to see statistics for (FB, 2S, CH, CC) or 'X' to return:" << endl;
        cin >> pitchType;
        if (pitchType == "X" || pitchType == "x") return;
        for (char& c : pitchType) c = toupper(c);

        bool valid = false;
        for (const string& validCode : validPitchTypes) {
            if (pitchType == validCode) {
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << " Invalid pitch type entered. Please try again." << endl;
            cout << " " << endl;
            continue;
        }

        int totalCount = 0;
        int strikeCount = 0;
        int ballCount = 0;
        int foulCount = 0;
        int hitCount = 0;
        int outCount = 0;
    
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
       
        double strikePercent = (static_cast<double>(strikeCount) / totalCount) * 100.0;
        double ballPercent = (static_cast<double>(strikeCount) / totalCount) * 100.0;
        double hitPercent = (static_cast<double>(strikeCount) / totalCount) * 100.0;

        cout << "=======================================================" << endl;
        cout << "Stats for Pitch Type: " << pitchType << endl;
        cout << "=======================================================" << endl;
        cout << "Total pitches Thrown: " << totalCount << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "Strikes (S): " << setw(5) << strikeCount << " (" << fixed << setprecision(1) << strikePercent << "%)" << endl;
        cout << "Balls (B): " << setw(5) << ballCount << " (" << fixed << setprecision(1) << ballPercent << "%)" << endl;
        cout << "Foul Balls (F): " << setw(5) << foulCount << endl;
        cout << "Hits Allowed (H): " << setw(4) << hitCount << " (" << fixed << setprecision(1) << hitPercent << "%)" << endl;
        cout << "Outs Recorded (O): " << setw(4) << outCount << endl;
        cout << "=======================================================" << endl;

    } while (true);
}

void sortPitchesBySpeed(vector<Pitch>& pitchLog) {
    if (pitchLog.empty()) {
        return;
    }

    int n = pitchLog.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; ++j) {
            if (pitchLog[j].speed < pitchLog[j + 1].speed) {
                swap(pitchLog[j], pitchLog[j + 1]);
            }
        }
    }
}

void exportDataTXT(vector<Pitch>& pitchLog, const string& filename) {
    if (pitchLog.empty()) {
        cout << "[ERROR] Cannot export data. Pitch log is empty." << endl;
        return;
    }

    sortPitchesBySpeed(pitchLog);
    cout << "Pitch log sorted by speed (Fastest to Slowest)" << endl;

    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "[ERROR] Could not open file " << filename << " for exporting." << endl;
        return;
    }

    outFile << "Type\tLocation\tResult\tSpeed" << endl;

    for (const Pitch& pitch : pitchLog) {
        outFile << pitch.type << "\t"
            << pitch.location << "\t"
            << pitch.result << "\t"
            << pitch.speed << endl;
    }

    outFile.close();
    cout << "[SUCCESS] Exported " << pitchLog.size() << " pitches to " << filename << "." << endl;
}