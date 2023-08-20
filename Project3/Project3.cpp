//Albert Chapman
//Project 3
//8/13/23

// Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>//needed for input and output
#include <map>//makes creating the file and iterating over the data easier
#include <fstream>//needed to read and write files
#include <string>//needed to process strings

using namespace std;
/*
Creates an object for the sales of that day
*/
class DailySales {
    public:
        void CreateFile();
        int GetFrequency(string search);
        void PrintAllFrequencyNumber();
        void PrintAllFrequencyHistrogram();
    private:
        int itemFrequency = 0;
        string item = "-1";
        ofstream outFS;
        ifstream inFS;
        map<string, int> outItem;
        int j = 0;
};
/*
Creates the file and map container for the use of the rest of the program
*/
void DailySales::CreateFile() {

    //Opens and checks the input file
    inFS.open("CS210_Project_Three_Input_File.txt");
    if (!inFS.is_open()) {
        cout << "Could not open file CS210_Project_Three_Input_File.txt" << endl;
    }

    //opens and checks the writing file
    outFS.open("frequency.dat");
    if (!inFS.is_open()) {
        cout << "Could not open file frequency.dat" << endl;
    }

    //This while loop gets each line from the input file and puts it into a map container
    getline(inFS, item);
    while (!inFS.fail()) {
        if (outItem.count(item) == 0) {//if the key isnt created yet, create the key with a starting value of 1
            outItem.emplace(item, 1);
        }
        else if (outItem.count(item) == 1) {// if the key is created, increment the value by 1
            outItem[item]++;
        }
        getline(inFS, item);
    }

    //This for loop iterates over the map container, writing it onto the output file
    for (map<string, int>::iterator i = outItem.begin(); i != outItem.end(); ++i) {
        outFS << i->first;
        outFS << " " << i->second << endl;
    }

    //close the input and output files
    inFS.close();
    outFS.close();
}

//simply returns the value of a given key
int DailySales::GetFrequency(string search) {
    itemFrequency = outItem.at(search);
    return itemFrequency;
}

//Since the map container is already created, simply iterate over it again but write to the console instead
void DailySales::PrintAllFrequencyNumber() {
    for (map<string, int>::iterator i = outItem.begin(); i != outItem.end(); ++i) {
        cout << i->first;
        cout << " " << i->second << endl;
    }
}

//Same as the PrintAllFrequencyNumber function but with an added for loop to print the symbols
void DailySales::PrintAllFrequencyHistrogram() {
    for (map<string, int>::iterator i = outItem.begin(); i != outItem.end(); ++i) {
        cout << i->first;
        cout << " ";
        for (int j = 0; j < i->second; j++) {
            cout << "*";
         }
        cout << endl;
    }
}

int main()
{
    int option = 0;
    string search = "-1";
    DailySales salesToday; // creates the object
    salesToday.CreateFile(); // creates the objects file
    while (option != 4) { // while loop to keep the program running until the user presses 4
        cout << "Pick an option:"  << endl;
        cout << "1: Enter a item name and the frequency of todays sales will be returned"  << endl;
        cout << "2: Print out all of todays sales with frequency in numbers"  << endl;
        cout << "3: Print out all of todays sales with frequency in a historgram" << endl;
        cout << "4: Exit the program"  << endl;
        cin >> option;
        cout << endl;
        switch (option) { // switch statement that directs to the appropriate function inside the object
            case (1):
                cout << "Name of item: ";
                cin >> search;
                cout <<"Frequency: " << salesToday.GetFrequency(search) << endl << endl;
                break;
            case (2):
                salesToday.PrintAllFrequencyNumber();
                cout << endl;
                break;

            case (3):
                salesToday.PrintAllFrequencyHistrogram();
                cout << endl;
                break;
            case (4):
                break;
        }
    }

    return 0;
}
