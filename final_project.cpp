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
#include <cstdlib>
#include <cctype> 

#include "song.h"
#include "database.h"
#include "menu.h"

using namespace std;

void findSong(Database& database, Menu& menu, const bool& isDelete){
	// display find song sub menu
	menu.printFindSongMenu(isDelete);
	// save the requested field selection
	int findChoice = menu.get_menuChoice();
	while(findChoice != 0){
		// display the search by sub menu
		menu.printSearchMenu();
		if(menu.get_menuChoice() == 1){
			// search for an exact match in the database
			database.searchExact(findChoice, isDelete);
		} else{
			if(menu.get_menuState() == 2){
				// search for a sub string match in the database
				database.searchSubstring(findChoice, isDelete);
			} else{
				// search for a range match in the database
				database.searchRange(isDelete);
			}
		}
		// display find song sub menu and save the updated choice
		menu.printFindSongMenu(isDelete);
		findChoice = menu.get_menuChoice();
	}
}

void databaseProgram(Database& database, Menu& menu){
	// check the stored choice in the menu class
	if(menu.get_menuChoice() == 0){
		// display main menu
		menu.printMainMenu();
	} else if(menu.get_menuChoice() == 1){
		// add song to database
		database.addSong();
		menu.printMainMenu();
	} else if(menu.get_menuChoice() == 2){
		// check if database is empty
		if(database.size() == 0){
			cout << "\nSorry, the database appears to be empty! "
				 << "Please add some songs before finding a song in the database.\n";
			menu.printMainMenu();
		} else{
			// find song (user does not want to delete results)
			findSong(database, menu, false);
		}
	} else if(menu.get_menuChoice() == 3){
		// check if database is empty
		if(database.size() == 0){
			cout << "\nSorry, the database appears to be empty! "
				 << "Please add some songs before deleting a song from the database.\n";
			menu.printMainMenu();
		} else{
			// find song and ask if the user wants to delete the results
			findSong(database, menu, true);
		}
	} else if(menu.get_menuChoice() == 4){
		// check if the database is empty
		if(database.size() == 0){
			cout << "\nSorry, the database appears to be empty! "
				 << "Please add some songs before requesting to list the songs in the database.\n";
			menu.printMainMenu();
		} else{
			// display list sub menu
			menu.printListMenu();
			// save the requested field selection
			int findChoice = menu.get_menuChoice();
			while(menu.get_menuChoice() != 0){
				// display the order by sub menu
				menu.printOrderMenu();
				// sort the records in the database
				database.sortRecords(findChoice, menu.get_menuChoice());
				// display the list sub menu and save updated choice
				menu.printListMenu();
				findChoice = menu.get_menuChoice();
			}
		}
	} else if(menu.get_menuChoice() == 5){
		// check if the database is empty
		if(database.size() == 0){
			cout << "\nSorry, the database appears to be empty! "
				 << "Please add some songs before getting a song recommendation.\n";
			menu.printMainMenu();
		} else{
			// display the recommendation sub menu
			menu.printRecMenu();
			while(menu.get_menuChoice() != 0){
				// get a song recommendation from the database
				database.songRec(menu.get_menuChoice());
				menu.printRecMenu();
			}
		}
	} else if(menu.get_menuChoice() == 6){
		// check if the database is empty
		if(database.size() == 0){
			cout << "\nThe database is currently empty!\n";
		} else{
			// clear the database
			database.clearData();
		}
		// bring the user back to the main menu
		menu.printMainMenu();
	}
}

int main(){
	// create instances of the database and menu
	Database database("database.txt");
	Menu menu;

	// when the user selectes '7', the program will end
	while(menu.get_menuChoice() != 7){
		// prompt the user with menus and get their choices
		databaseProgram(database, menu);
	}
}