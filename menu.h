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
/////////////////////////////////////////////////////////////////////////

#include <cctype>

using namespace std;

class Menu{
private: 
	int menuChoice;
	int menuState;

	// https://www.cplusplus.com/reference/cctype/isdigit/
	void promptChoice(const int& min, const int& max){
		string input;
		menuChoice = -1;

		while(menuChoice < min || menuChoice > max){
			cout << "Please enter the number of your choice: ";
			
			getline(cin, input);
			for(int i = 0; i < input.length(); i++){
				if(!isdigit(input[i])){
					menuChoice = -1;
					break;
				} else if(i == input.length()-1){
					menuChoice = stoi(input); 
				}
			}

			if(menuChoice < min || menuChoice > max){
				cout << "Invalid choice.\n"; 
			} 
		}
	}

public: 
	Menu()
	: menuChoice(0), menuState(0)
	{
		cout << "\n+==================================================+\n"
			 << "| Welcome to Carissa's Database of Favourite Songs |\n"
			 << "+==================================================+\n";
		printMainMenu();
	}

	int get_menuChoice() const{
		return menuChoice;
	}

	int get_menuState() const{
		return menuState;
	}

	// void set_menuState(const int& i){
	// 	if(i < 0 || i > 1){
	// 		cout << "Invalid menu state.";
	// 	} 

	// 	menuState = i;
	// }

	// void displayMenu(){
	// 	if(menuState == 0){
	// 		printMainMenu();
	// 	} else if(menuState == 1){

	// 	}
	// }

	void printMainMenu(){
		menuState = 0;
		cout << "\nMain Menu\n"
			 << "=========\n"
			 << "1: Add a Song\n"
			 << "2: Find a Song\n"
			 << "3: Delete a Song\n"
			 << "4: List Songs\n"
			 << "5: Song Recommendation\n"
			 << "6: Quit\n\n";
		promptChoice(1, 6);
	}

	void printFindSongMenu(const bool& deleteRecord){
		menuState = 1;
		if(deleteRecord){
			cout << "\nDelete a Song\n"
				 << "=============\n";
		} else{
			cout << "\nFind a Song\n"
				 << "===========\n";
		}

		cout << "You can find by:\n"
			 << "1: Name of Song\n"
			 << "2: Album that the Song is from\n"
			 << "3: Artist who Performed the Song\n"
			 << "4: Year of Song Release\n\n"
			 << "0: Return to Main Menu\n\n";
		promptChoice(0, 4);
	}

	void printSearchMenu(){
		if(menuChoice < 4 && menuChoice > 0){
			menuState = 2;
			cout << "Search for...\n"
				 << "1: Exact Match\n"
				 << "2: Substring Match\n\n";
			promptChoice(1, 2);
		} else if(menuChoice == 4){
			menuState = 3;
			cout << "Search for...\n"
				 << "1: Exact Match\n"
				 << "2: Range Match\n\n";
			promptChoice(1, 2);
		}
	}

	void printListMenu(){
		menuState = 4;
		cout << "\nList Songs\n"
			 << "==========\n"
			 << "List by:\n"
			 << "1: Name of Song\n"
			 << "2: Album that the Song is from\n"
			 << "3: Artist who Performed the Song\n"
			 << "4: Year of Song Release\n\n"
			 << "0: Return to Main Menu\n\n";
		promptChoice(0, 4);
	}

	void printOrderMenu(){
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
			promptChoice(1, 2);
		}
	}

	void printRecMenu(){
		menuState = 7;
		cout << "\nSong Recommendation\n"
			 << "===================\n"
			 << "1: Select Song by Number\n"
			 << "2: Get a Random Song\n\n"
			 << "0: Return to Main Menu\n\n";
		promptChoice(0, 2);
	}

	// Destructor
	~Menu(){}
};

