// final_project.cpp

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

#include <iostream>     
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert>  

#include "song.h"
#include "database.h"
#include "menu.h"

using namespace std;

int main(){
	Database database("database.txt");
	// Database database("empty_db.txt");
	Menu menu;

	while(menu.get_menuChoice() != 6){
		if(menu.get_menuChoice() == 0){
			// display main menu
			menu.printMainMenu();
		} else if(menu.get_menuChoice() == 1){
			database.addSong();
			// display main menu
			menu.printMainMenu();
		} else if(menu.get_menuChoice() == 2){
			if(database.size() == 0){
				cout << "\nSorry, the database appears to be empty! "
					 << "Please add some songs before finding a song in the database.\n";
				menu.printMainMenu();
			} else{
				// display find song sub menu
				menu.printFindSongMenu(false);
				int findChoice = menu.get_menuChoice();
				while(findChoice != 0){
					menu.printSearchMenu();
					if(menu.get_menuChoice() == 1){
						database.searchExact(findChoice, false);
					} else{
						if(menu.get_menuState() == 2){
							database.searchSubstring(findChoice, false);
						} else{
							database.searchRange(false);
						}
					}
					// display find song sub menu
					menu.printFindSongMenu(false);
					findChoice = menu.get_menuChoice();
				}
			}
		} else if(menu.get_menuChoice() == 3){
			if(database.size() == 0){
				cout << "\nSorry, the database appears to be empty! "
					 << "Please add some songs before deleting a song from the database.\n";
				menu.printMainMenu();
			} else{
				// display find song sub menu
				menu.printFindSongMenu(true);
				int findChoice = menu.get_menuChoice();
				while(findChoice != 0){
					menu.printSearchMenu();
					if(menu.get_menuChoice() == 1){
						if(menu.get_menuChoice() == 1){
							database.searchExact(findChoice, true);
						}
					} else{
						if(menu.get_menuState() == 2){
							database.searchSubstring(findChoice, true);
						} else{
							database.searchRange(true);
						}
					}
					// display find song sub menu
					menu.printFindSongMenu(true);
					findChoice = menu.get_menuChoice();
				}
			}
		} else if(menu.get_menuChoice() == 4){
			if(database.size() == 0){
				cout << "\nSorry, the database appears to be empty! "
					 << "Please add some songs before requesting to list the songs in the database.\n";
				menu.printMainMenu();
			} else{
				menu.printListMenu();
				int findChoice = menu.get_menuChoice();
				while(menu.get_menuChoice() != 0){
					menu.printOrderMenu();
					database.sortRecords(findChoice, menu.get_menuChoice());
					menu.printListMenu();
					findChoice = menu.get_menuChoice();
				}
			}
		} else if(menu.get_menuChoice() == 5){
			if(database.size() == 0){
				cout << "\nSorry, the database appears to be empty! "
					 << "Please add some songs before getting a song recommendation.\n";
				menu.printMainMenu();
			} else{
				menu.printRecMenu();
				while(menu.get_menuChoice() != 0){
					database.songRec(menu.get_menuChoice());
					menu.printRecMenu();
				}
			}
		}
	}
}