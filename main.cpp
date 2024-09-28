// Project 3 Final Submission
// Naomi Shah - nns220002

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

const string database = "freeplay.dat"; // filestream for the the database will connect to this variable

// Structure definition for each record
struct gameRecord {
    string name;
    int highScore;
    string initials;
    int plays;
    double revenue;
    gameRecord *next; // points to next node
};


// Fucntion to add record
void AddRecord(string name, int highScore, string initials, int plays, double revenue, gameRecord *&head) {
    // Allocate memory for a new node
    gameRecord *newRecord = new gameRecord;
    
    // Assign values to each variable in node
    newRecord->name = name;
    newRecord->highScore = highScore;
    newRecord->initials = initials;
    newRecord->plays = plays;
    newRecord->revenue = revenue;
    newRecord->next = nullptr; // because adding to the end of the list
    
    // Add to linked list
    if (head == nullptr) { // if list is empty
        head = newRecord;
    } else { // if list is not empty
        gameRecord *ptr = head;
        
        // Iterate through list until reaching last node
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = newRecord;
    }
}


// Function to read records from the database file and store them into the linked list
void ReadDatabaseFile(string filename, gameRecord *&head) {
    // Open database file to read
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Unable to opem database file." << endl;
        return;
    }
    
    // Read in each line
    string line;
    while (getline(infile, line)) {
        // Parse line
        string name, initials;
        int highScore, plays;
        double revenue;
        
        auto index = line.find(','); // finds position first comma
        
        // Extract name
        name = line.substr(0, index);
        line = line.substr(index + 2); // removes name, comma, and space
        
        // Extract high score
        index = line.find(','); // finds comma after field
        highScore = stoi(line.substr(0, index));
        line = line.substr(index + 2); // removes comma, space, and score
        
        // Extract intials
        index = line.find(','); // finds comma after field
        initials = line.substr(0, index);
        line = line.substr(index + 2); // removes comma, space, and initials
        
        // Extract Plays
        index = line.find(','); // finds comma after field
        plays = stoi(line.substr(0, index));
        line = line.substr(index + 3); // removes comma, space, plays, and $
        
        // Extract revenue
        revenue = stod(line);
        
        // Add record to linked list
        AddRecord(name, highScore, initials, plays, revenue, head);
    }
    
    // Close file
    infile.close();
}


// Function to search for record
void SearchRecord(string searchTerm, gameRecord *head) {
    gameRecord *ptr = head;
    bool found = false;
    
    // Go through each each node
    while (ptr != nullptr) {
        // Check if name contains search term
        if (ptr->name.find(searchTerm) != string::npos) {
            found = true; // set flag to true
            // Print info to console
            cout << ptr->name << " FOUND" << endl;
            cout << "High Score: " << ptr->highScore << endl;
            cout << "Initials: " << ptr->initials << endl;
            cout << "Plays: " << ptr->plays << endl;
            cout << "Revenue: $" << fixed << setprecision(2) << ptr->revenue << endl << endl;
            break;
        }
        ptr = ptr->next; // move ptr to next node
    }
    
    if (found == false) {
        cout << searchTerm << " NOT FOUND" << endl << endl;
    }
}


// Function to edit record
void EditRecord(string nameToEdit, string fieldNum, string newValue, gameRecord *&head) {
    gameRecord *ptr = head;
    
    // Find node to edit
    while (ptr != nullptr) {
        if (ptr->name == nameToEdit) {
            
            // Print info to console
            cout << ptr->name << " UPDATED" << endl;
            
            
            switch (stoi(fieldNum)) {
                case 1:{ // edit high score
                    ptr->highScore = stoi(newValue);
                    
                    // Cout info to console
                    cout << "UPDATE TO high score - VALUE " << ptr->highScore << endl;
                    cout << "Name: " << ptr->name << endl;
                    cout << "High Score: " << ptr->highScore << endl;
                    cout << "Initials: " << ptr->initials << endl;
                    cout << "Plays: " << ptr->plays << endl;
                    cout << "Revenue: $" << fixed << setprecision(2) << ptr->revenue << endl << endl;
                    
                    break;
                    
                }
                case 2:{ // edit initials
                    ptr->initials = newValue;
                    
                    // Cout info to console
                    cout << "UPDATE TO initials - VALUE " << ptr->initials << endl;
                    cout << "Name: " << ptr->name << endl;
                    cout << "High Score: " << ptr->highScore << endl;
                    cout << "Initials: " << ptr->initials << endl;
                    cout << "Plays: " << ptr->plays << endl;
                    cout << "Revenue: $" << fixed << setprecision(2) << ptr->revenue << endl << endl;
                    break;
                    
                }
                case 3:{ // edit plays and revenue
                    ptr->plays = stoi(newValue);
                    ptr->revenue = static_cast<double>(ptr->plays) * 0.25;
                    
                    // Cout info to console
                    cout << "UPDATE TO plays - VALUE " << ptr->plays << endl;
                    cout << "Name: " << ptr->name << endl;
                    cout << "High Score: " << ptr->highScore << endl;
                    cout << "Initials: " << ptr->initials << endl;
                    cout << "Plays: " << ptr->plays << endl;
                    cout << "Revenue: $" << fixed << setprecision(2) << ptr->revenue << endl << endl;
                    break;
                }
                default:{
                    cout << "Invalid field number." << endl;
                    break;
                }
            }
        }
        ptr = ptr->next;
    }
}

// Function to delete record
void DeleteRecord(string deleteName, gameRecord *&head) {
    gameRecord *ptr = head;
    gameRecord *hold = nullptr;
    
    if(!head) { // empty list
        return;
    }
    // Check if node is at beginning
    else if (head->name.find(deleteName) != string::npos) {
        // Cout info to console before deleting node
        cout << "RECORD DELETED" << endl;
        cout << "Name: " << ptr->name << endl;
        cout << "High Score: " << ptr->highScore << endl;
        cout << "Initials: " << ptr->initials << endl;
        cout << "Plays: " << ptr->plays << endl;
        cout << "Revenue: $" << fixed << setprecision(2) << ptr->revenue << endl << endl;
        
        hold = head; // hold onto node
        head = head->next; // move head to point at node after the one to delete
        hold->next = nullptr; // disconnect node
        
        return;
        
    } else {
         // Traverse loop to move pointer to node to delete
        while (ptr->next->name.find(deleteName) == string::npos) {
            ptr = ptr->next; // move ptr to next node
        }
        
        hold = ptr->next; //hold onto node to be deleted
        
        // middle or end of list
        // Cout info to console before deleting node
        cout << "RECORD DELETED" << endl;
        cout << "Name: " << hold->name << endl;
        cout << "High Score: " << hold->highScore << endl;
        cout << "Initials: " << hold->initials << endl;
        cout << "Plays: " << hold->plays << endl;
        cout << "Revenue: $" << fixed << setprecision(2) << hold->revenue << endl << endl;
        
        ptr->next = hold->next; // connect before node and after node
        hold->next = nullptr; // disconnect removed node
        
        return;
    }
}

// Function to print database to console (for sorting)
void PrintRecordsToConsole (gameRecord *current, string sortBy) {
    // Base case
    if (current == nullptr) {
        return;
    }
    
    if (sortBy == "plays" || sortBy == "name") {
        cout << "RECORDS SORTED BY " << sortBy << endl;
    }
    
    // Print record to console
    cout << current->name << ", " << current->highScore << ", " << current->initials << ", " << current->plays << ", $" << fixed << setprecision(2) << current->revenue << endl;
    
    // Call function
    PrintRecordsToConsole(current->next, "none");
}
 
// Function to sort values alphabetically
void SortRecordsByName(gameRecord *&head, string sortBy) {
    // If list is empty, don't need to sort
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    gameRecord *ptr1, *lastPtr = nullptr;

    do {
        swapped = false; // initialize swapped to false
        ptr1 = head;

        while (ptr1->next != lastPtr) {
            // Compare names
            if (ptr1->name > ptr1->next->name) {
                swap(ptr1->name, ptr1->next->name); // swap names
                swap(ptr1->highScore, ptr1->next->highScore); // swap scores
                swap(ptr1->initials, ptr1->next->initials); // swap initials
                swap(ptr1->plays, ptr1->next->plays); // swap plays
                swap(ptr1->revenue, ptr1->next->revenue); // swap revenue

                swapped = true;
            }
            ptr1 = ptr1->next; // move ptr
        }
        lastPtr = ptr1; // Update the last sorted position

    } while (swapped);

    // Print the sorted list to console
    PrintRecordsToConsole(head, sortBy);
    cout << endl;
}

// Function to sort values by plays ascending order
void SortRecordsByPlays(gameRecord *&head, string sortBy) {
    // If list is empty, don't need to sort
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    bool swapped;
    gameRecord *ptr1, *lastPtr = nullptr;

    do {
        swapped = false; // initialize swapped to false
        ptr1 = head;

        while (ptr1->next != lastPtr) {
            // Compare names
            if (ptr1->plays > ptr1->next->plays) {
                swap(ptr1->name, ptr1->next->name); // swap names
                swap(ptr1->highScore, ptr1->next->highScore); // swap scores
                swap(ptr1->initials, ptr1->next->initials); // swap initials
                swap(ptr1->plays, ptr1->next->plays); // swap plays
                swap(ptr1->revenue, ptr1->next->revenue); // swap revenue

                swapped = true;
            }
            ptr1 = ptr1->next; // move ptr
        }
        lastPtr = ptr1; // Update the last sorted position

    } while (swapped);

    // Print the sorted list to console
    PrintRecordsToConsole(head, sortBy);
    cout << endl;
}


void PrintRecordsToFile(gameRecord *current, ofstream &filePtr) {
    // Base case
    if (current == nullptr) {
        return;
    }
    
    // Print record to file
    filePtr << current->name << ", " << current->highScore << ", " << current->initials << ", " << current->plays << ", $" << fixed << setprecision(2) << current->revenue << endl;
    
    // Call function
    PrintRecordsToFile(current->next, filePtr);
}


int main() {
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    string temp;  //variable for database filename
    string batch; //variable for batch filename
    
    cout << "Enter Database Name: ";
    cin >> temp;
    
    ifstream infile(temp, ios::binary);
    ofstream outfile(database, ios::binary);
    string line;
    if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }
    
    infile.close();
    outfile.close();
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    
    // Add code for main here ----
    // Get batch file name from user
    cout << "Enter batch file name: ";
    cin >> batch;
    
    // Create empty linked list
    gameRecord *head = nullptr;
    
    // Store all records from database into linked list
    ReadDatabaseFile(database, head);
    
    // Open batch file
    ifstream batchfile(batch, ios::in);
    
    while (getline(batchfile, line)) {
        switch (line[0]) {
            case '1': {
                // Parse command line
                string name, initials;
                int highScore, plays;
                double revenue;
                
                auto index = line.find(' '); // finds position first space
                line = line.substr(index + 2); // remove beginning of line
                
                // Extract name
                index = line.find('"'); // finds second quote after name
                name = line.substr(0, index);
                line = line.substr(index + 2); // removes name, quote, and space
                
                // Extract high score
                index = line.find(' '); // finds space after field
                highScore = stoi(line.substr(0, index));
                line = line.substr(index + 1); // removes space and score
                
                // Extract intials
                index = line.find(' '); // finds space after field
                initials = line.substr(0, index);
                line = line.substr(index + 1); // removes space and initials
                
                // Extract Plays
                index = line.find(' '); // finds space after field
                plays = stoi(line.substr(0, index));
                line = line.substr(index + 2); // removes space and plays and $
                
                // Extract revenue
                revenue = stod(line);
                
                // Call Add Record function
                AddRecord(name, highScore, initials, plays, revenue, head);
                
                // Print info to console
                cout << "RECORD ADDED" << endl;
                cout << "Name: " << name << endl;
                cout << "High Score: " << highScore << endl;
                cout << "Initials: " << initials << endl;
                cout << "Plays: " << plays << endl;
                cout << "Revenue: $" << fixed << setprecision(2) << revenue << endl << endl;
                break;
            }
                
            case '2': {
                // Parse command line
                auto index = line.find(' '); // finds space after digit
                string searchTerm = line.substr(index + 1);
                
                SearchRecord(searchTerm, head);
                break;
            }
                
            case '3': {
                // Parse command line
                string name, fieldNum, value;
                auto index = line.find(' '); // finds position first space
                line = line.substr(index + 2); // remove beginning of line
                
                // Extract name
                index = line.find('"'); // finds second quote after name
                name = line.substr(0, index);
                line = line.substr(index + 2); // removes name, quote, and space
                
                // Extract field number
                index = line.find(' '); // finds space after field
                fieldNum = line.substr(0, index);
                line = line.substr(index + 1); // removes space and field number
                
                // Extract value
                value = line;
                
                EditRecord(name, fieldNum, value, head);
                break;
            }
             
            case '4': {
                // Parse command line
                string name;
                auto index = line.find(' '); // find position of first space
                name = line.substr(index + 1); // removes number and space at beginning
                
                DeleteRecord(name, head);
                break;
            }
            case '5': {
                // Parse command line
                string sortBy;
                auto index = line.find(' '); // find position of first space
                sortBy = line.substr(index + 1); // removes number and space at beginning
                
                if (sortBy == "name") {
                    SortRecordsByName(head, sortBy); // A-Z
                } else if (sortBy == "plays") {
                    SortRecordsByPlays(head, sortBy); // low-high
                } else {
                    cout << "Unable to sort by " << sortBy << endl << endl;
                }
                break;
            }
             
            default:{
                cout << "Invalid command" << endl;
                break;
            }
        }
    }
    
    // Close file
    batchfile.close();
    
    outfile.open(database);
    
    PrintRecordsToFile(head, outfile);
    
    outfile.close();
    
    return 0;
}

