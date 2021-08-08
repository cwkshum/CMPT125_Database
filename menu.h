// menu.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Carissa Shum
// St.# : 301359502
// Email: cws8@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
//
// Reference
// ---------
// 1. Using isdigit() to check if the character is a valid digit when 
// receiving an numeric input in the form of a string from getline()
// - https://www.cplusplus.com/reference/cctype/isdigit/
//
/////////////////////////////////////////////////////////////////////////

using namespace std;

class Menu{
private: 
	int menuChoice;
	int menuState;

	void promptChoice(const int& min, const int& max){
		string input;
		// reset menuChoice
		menuChoice = -1;

		// check if the choice is within the min and max
		while(menuChoice < min || menuChoice > max){
			// get user input
			cout << "Please enter the number of your choice: ";
			getline(cin, input);
			// check if the input contains any non digit character
			for(int i = 0; i < input.length(); i++){
				if(!isdigit(input[i])){
					// non digit value found, reset menuChoice and 
					// stop checking the rest of the input
					menuChoice = -1;
					break;
				} else if(i == input.length()-1){
					// no non digit values found
					menuChoice = stoi(input); 
				}
			}

			// if choice is out of range, print message
			if(menuChoice < min || menuChoice > max){
				cout << "Invalid choice.\n"; 
			} 
		}
	}
public: 

	// Constructor
	Menu()
	: menuChoice(0), menuState(0)
	{
		// display welcome message and main menu
		cout << "\n+==================================================+\n"
			 << "| Welcome to Carissa's Database of Favourite Songs |\n"
			 << "+==================================================+\n";
		printMainMenu();
	}

	int get_menuChoice() const{
		// return the stored menu choice
		return menuChoice;
	}

	int get_menuState() const{
		// return the menu state
		return menuState;
	}

	void printMainMenu(){
		// display the main menu for the user to decide
		// how they want to interact with the database
		menuState = 0;
		cout << "\nMain Menu\n"
			 << "=========\n"
			 << "1: Add a Song\n"
			 << "2: Find a Song\n"
			 << "3: Delete a Song\n"
			 << "4: List Songs\n"
			 << "5: Song Recommendation\n"
			 << "6: Clear Database\n"
			 << "7: Quit\n\n";
		// get user's choice and validate it
		promptChoice(1, 7);
	}

	void printFindSongMenu(const bool& deleteRecord){
		menuState = 1;
		// check if user wants to delete or find a song
		if(deleteRecord){
			cout << "\nDelete a Song\n"
				 << "=============\n";
		} else{
			cout << "\nFind a Song\n"
				 << "===========\n";
		}

		// display find by menu for users to determine which  
		// field in the database they want to search for
		cout << "You can find by:\n"
			 << "1: Name of Song\n"
			 << "2: Album that the Song is from\n"
			 << "3: Artist who Performed the Song\n"
			 << "4: Year of Song Release\n\n"
			 << "0: Return to Main Menu\n\n";
		// get user's choice and validate it
		promptChoice(0, 4);
	}

	void printSearchMenu(){
		// display search for menu for users to decide   
		// how they want to search the database
		if(menuChoice < 4 && menuChoice > 0){
			// options for string fields
			menuState = 2;
			cout << "Search for...\n"
				 << "1: Exact Match\n"
				 << "2: Substring Match\n\n";
			promptChoice(1, 2);
		} else if(menuChoice == 4){
			// options for integer fields
			menuState = 3;
			cout << "Search for...\n"
				 << "1: Exact Match\n"
				 << "2: Range Match\n\n";
			promptChoice(1, 2);
		}
	}

	void printListMenu(){
		// display list by menu for users to select which   
		// field they want to list the database records by
		menuState = 4;
		cout << "\nList Songs\n"
			 << "==========\n"
			 << "List by:\n"
			 << "1: Name of Song\n"
			 << "2: Album that the Song is from\n"
			 << "3: Artist who Performed the Song\n"
			 << "4: Year of Song Release\n\n"
			 << "0: Return to Main Menu\n\n";
		// get user's choice and validate it
		promptChoice(0, 4);
	}

	void printOrderMenu(){
		// print order by menu for users to decide how 
		// to order the selected field of the database
		if(menuChoice < 4 && menuChoice > 0){
			menuState = 5;
			cout << "Order for...\n"
				 << "1: Alphabetical Order\n"
				 << "2: Reverse Alphabetical Order\n\n";
			promptChoice(1, 2);
		} else if(menuChoice == 4){
			menuState = 6;
			cout << "Order for...\n"
				 << "1: Ascending Order\n"
				 << "2: Descending Order\n\n";
			// get user's choice and validate it
			promptChoice(1, 2);
		}
	}

	void printRecMenu(){
		// display recommendation menu for the user to decide if they want to manually 
		// input an index number or if they want to receive a random song from the database
		menuState = 7;
		cout << "\nSong Recommendation\n"
			 << "===================\n"
			 << "1: Select Song by Number\n"
			 << "2: Get a Random Song\n\n"
			 << "0: Return to Main Menu\n\n";
		// get user's choice and validate it
		promptChoice(0, 2);
	}

	// Destructor
	~Menu(){}
};