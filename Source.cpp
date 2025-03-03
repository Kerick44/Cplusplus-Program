#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Grocery {
private:
	map<string, int> groceryList; // Stores grocery items and their frequencies
	string fileName;

public:
	Grocery() {
		fileName = "CS210_Project_Three_Input_File.txt"; // Default filename for data storage
	}

	// Reads item names and counts from file and stores them in the map
	void processInputFile(const string& filePath) {
		ifstream inputfile(filePath);
		string itemName;
		int itemCount;

		if (!inputfile.is_open()) {
			cout << "Error opening file: " << filePath << endl;
			return;
		}

		while (inputfile >> itemName >> itemCount) { // Read item name and count
			groceryList[itemName] = itemCount; // Store data in the map
		}
		inputfile.close();
	}

	// Saves the grocery list to a file
	void saveDataToFile() {
		ofstream outputfile(fileName);

		if (outputfile.is_open()) {
			for (auto& item : groceryList) {
				outputfile << item.first << " " << item.second << endl; // Write item name and count
			}
			outputfile.close();
			cout << "Data saved to file: " << fileName << endl;
		}
		else {
			cout << "Error creating output file: " << fileName << endl;
		}
	}

	// Prints the grocery list to the console
	void printGroceryList() {
		for (const auto& item : groceryList) {
			cout << item.first << " " << item.second << endl; // Display item and frequency
		}
	}

	// Prints a histogram representation of grocery item counts
	void printHistogram() {
		for (auto& item : groceryList) {
			cout << item.first << " ";
			for (int i = 0; i < item.second; i++) {
				cout << "-"; // Print dashes to represent count visually
			}
			cout << endl;
		}
	}

	// Adds a new item or increases its count
	void addItem() {
		string newItem;
		cout << "Enter item to add: ";
		getline(cin, newItem);
		groceryList[newItem]++; // Increment count or add new entry
		cout << newItem << " has been added." << endl;
	}

	// Removes an item from the grocery list
	void removeItem() {
		string removeItem;
		cout << "Enter item to remove: ";
		getline(cin, removeItem);
		if (groceryList.count(removeItem) > 0) { // Check if item exists
			groceryList.erase(removeItem); // Remove from map
			cout << removeItem << " has been removed." << endl;
		}
		else {
			cout << removeItem << " not found in the list." << endl;
		}
	}

	// Displays menu and handles user input
	void run() {
		int choice;
		string userInput;

		do {
			cout << "===================================" << endl;
			cout << "|           Menu Options          |" << endl;
			cout << "===================================" << endl;
			cout << "|1. Search up item frequency      |" << endl;
			cout << "|2. Save data to file             |" << endl;
			cout << "|3. Print a grocery list          |" << endl;
			cout << "|4. Print a histogram             |" << endl;
			cout << "|5. Add a new item                |" << endl;
			cout << "|6. Remove an item                |" << endl;
			cout << "|7. Exit                          |" << endl;
			cout << "===================================" << endl;
			cout << endl;
			cout << "Please enter a number from the menu: ";
			cin >> choice;
			cin.ignore(); // Clear buffer before taking string input

			switch (choice) {
			case 1:
				cout << "Enter item to search: ";
				getline(cin, userInput);
				cout << "Frequency of " << userInput << ": " << groceryList[userInput] << endl;
				break;
			case 2:
				saveDataToFile();
				break;
			case 3:
				printGroceryList();
				break;
			case 4:
				printHistogram();
				break;
			case 5:
				addItem();
				break;
			case 6:
				removeItem();
				break;
			case 7:
				cout << "Exiting program. Goodbye!" << endl;
				return;
			default:
				cout << "Invalid option. Please try again." << endl;
				break;
			}
		} while (true); // Loop until exit is chosen
	}
};

int main() {
	Grocery grocery;
	grocery.processInputFile("CS210_Project_Three_Input_File.txt"); // Load grocery data from file
	grocery.run(); // Start user menu interaction

	return 0;
}
