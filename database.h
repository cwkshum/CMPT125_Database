// database.h

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

#include <cstdlib>
#include <algorithm>
#include "sortComparisions.h"

using namespace std;

class Database{
private:
	int sz;
	int cap;
	Song* data;

	bool existInDatabase(const string& songName, const string& album, const string& artist, const int& year) const{
		for(int i = 0; i < sz; i++){
			if(toLowerCase(data[i].get_name()) == toLowerCase(songName) && 
				toLowerCase(data[i].get_album()) == toLowerCase(album) && 
				toLowerCase(data[i].get_artist()) == toLowerCase(artist) && 
				data[i].get_year() == year){
				return true;
			}
		}

		return false;
	}

	void validateSongInput(string& songName) const{
		// https://www.cplusplus.com/reference/string/string/find_first_not_of/
		while(songName.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid song name entered, please try again.\nEnter Song Name: ";
			getline(cin, songName);
		}
	}

	void validateAlbumInput(string& album) const{
		while(album.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid album name entered, please try again.\nEnter Album Name: ";
			getline(cin, album);
		}
	}

	void validateArtistInput(string& artist) const{
		while(artist.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid artist name entered, please try again.\nEnter Artist Name: ";
			getline(cin, artist);
		}
	}

	void validateNumInput(string& input, const int& min, const int& max, const string& errorMsg) const{
		if(input.length() == 0){
			input = "-1";
		} else{
			for(int i = 0; i < input.length(); i++){
				if(!isdigit(input[i])){
					input = "-1";
					break;
				} 
			}
		}

		while(stoi(input) < min || stoi(input) > max) {
			if(errorMsg == "year"){
				cout << "Invalid release year entered, please try again.\nEnter Year of Release: ";
			} else if(errorMsg == "choice"){
				cout << "Invalid choice.\n" 
					 << "Please enter the number of your choice: ";
			} else if(errorMsg == "rec"){
				cout << "Invalid choice.\n" 
					 << "Enter a number from " << min << " to " << max << ": ";
			} else if(errorMsg == "yearLow"){
				cout << "Invalid release year entered, please try again.\nEnter the lowest year range: ";
			} else if(errorMsg == "yearHigh"){
				cout << "Invalid release year entered. Please ensure that the year is "
					 << to_string(min) << " or higher and try again.\nEnter the highest year range: ";
			}
			
			getline(cin, input);

			if(input.length() == 0){
				input = "-1";
			} else{
				for(int i = 0; i < input.length(); i++){
					if(!isdigit(input[i])){
						input = "-1";
						break;
					} 
				}
			}
		} 
	}

	string requestedField(const int& choice) const{
		if(choice == 1){
			return "song";
		} else if(choice == 2){
			return "album";
		} else if(choice == 3){
			return "artist";
		} else {
			return "year";
		}
	}
public:
	// Empty Default Constructor
	Database()
	: sz(0), cap(10), data(new Song[cap])
	{
		// use current time as seed for random generator
		srand(time(0));
	}

	// Read from File Constructor
	// https://www.cplusplus.com/reference/string/string/getline/
	Database(const string& fname)
	: sz(0), cap(10), data(new Song[cap])
	{
		string songName, album, artist, year;
		int recordField = 0;

		// read from given file name
		ifstream textFile(fname);
		if(textFile.is_open()){
			while(!textFile.eof()){
				if(recordField == 0){
					getline(textFile, songName, '*'); //get first string delimited by comma 
				} else if(recordField == 1){
					getline(textFile, album, '*'); //get first string delimited by comma 
				} else if(recordField == 2){
					getline(textFile, artist, '*'); //get first string delimited by comma 
				} else if(recordField == 3){
					getline(textFile, year); //get first string delimited by comma
				}
		      
				recordField++;
				
				if(recordField == 4){
					// create a song element
					Song song(songName, album, artist, stoi(year));

					// add song to data array
					addData(song);
					recordField = 0;
				}
			}
			textFile.close();
		} else{
			// file error
			cout << "There was an error opening and reading the database textfile.\n";
		} 

		// use current time as seed for random generator
		srand(time(0));
	}

	int size() const{
		// return size of database
		return sz;
	}

	int capacity() const{
		// return capacity of database
		return cap;
	}

	Song get_song(const int& i) const{
		if(i < 0 || i > sz-1){
			// invalid index
			cout << "The requested index location is outside the bounds of the array.\n";
		}

		// return song at requested index
		return data[i];
	}

	void addData(Song song){
		if(sz < cap){
			// increase size and set the right end slot to the new song
			sz++;
			data[sz - 1] = song;
		} else if(sz >= cap){
			// create a new array with double the capacity
			cap *= 2;
			Song* newArray = new Song[cap];

			// copy the old array values into the new array
			for(int i = 0; i < cap; i++){
				if(i < sz){
					newArray[i] = data[i];
				} 
			}

			// delete old array and set it to the new array
			delete[] data;
			data = newArray;
			// increase size and set the right end slot to the new value
			sz++;
			data[sz - 1] = song;
		}
	}

	void addSong(){
		string songName, album, artist, yearString;
		int year;

		cout << "\nAdd Song to Database\n"
			 << "--------------------\n";

		cout << "Enter Song Name: ";
		getline(cin, songName);
		// validate input
		validateSongInput(songName);

		cout << "Enter Album Name: ";
		getline(cin, album);
		// validate input
		validateAlbumInput(album);

		cout << "Enter Artist Name: ";
		getline(cin, artist);
		// validate input
		validateArtistInput(artist);

		cout << "Enter Year of Release: ";
		getline(cin, yearString);
		// validate input
		validateNumInput(yearString, 1000, 2021, "year");
		year = stoi(yearString);

		// validate entry
		if(existInDatabase(songName, album, artist, year)){
			// don't add to database
			cout << songName << " by " << artist << " already exists in the database.\n";
		} else {
			Song newSong(songName, album, artist, year);
			addData(newSong);

			cout << "\n" << songName << " by " << artist << " was successfully added!\n";
		}
	}

	void printRecord(const Song& song) const{
		cout << "Song: "
			 << song.get_name()
			 << "\nAlbum: "
			 << song.get_album()
			 << "\nArtist: "
			 << song.get_artist()
			 << "\nYear: "
			 << song.get_year()
			 << "\n\n";
	}

	void searchExact(const int& findChoice, const bool& deleteRecord){
		string searchPrompt = requestedField(findChoice);
		string searchRequest;
		int results = 0;

		cout << "Enter your " + searchPrompt + " search request: ";
		getline(cin, searchRequest);
		
		if(findChoice == 1){
			validateSongInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_name()) == toLowerCase(searchRequest)){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		} else if(findChoice == 2){
			validateAlbumInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_album()) == toLowerCase(searchRequest)){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		} else if(findChoice == 3){
			validateArtistInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_artist()) == toLowerCase(searchRequest)){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		} else if(findChoice == 4){
			validateNumInput(searchRequest, 1000, 2021, "year");
			for(int i = 0; i < sz; i++){
				if(data[i].get_year() == stoi(searchRequest)){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		}

		if(results == 0){
			cout << "\nNo " << searchPrompt << " results found matching " << searchRequest << ".\n";
		} else{
			cout << to_string(results);
			if(results == 1){
				cout << " result "; 
			} else{
				cout << " results ";
			}
			cout << "found where the " << searchPrompt << " matches " << searchRequest << ".\n";

			if(deleteRecord && deleteResults(results)){
				deleteExact(findChoice, searchRequest);
			}
		}
	}

	void searchSubstring(const int& findChoice, const bool& deleteRecord){
		string searchPrompt = requestedField(findChoice);
		string searchRequest;
		int results = 0;

		cout << "Enter your " + searchPrompt + " substring search request: ";
		getline(cin, searchRequest);
		
		
		if(findChoice == 1){
			validateSongInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_name()).find(toLowerCase(searchRequest)) != string::npos){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		} else if(findChoice == 2){
			validateAlbumInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_album()).find(toLowerCase(searchRequest)) != string::npos){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		} else if(findChoice == 3){
			validateArtistInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_artist()).find(toLowerCase(searchRequest)) != string::npos){
					if(results == 0){
						cout << "\nSearch Results\n"
							 << "--------------\n";
					}
					// print record
					printRecord(data[i]);
					results++;
				}
			}
		}

		if(results == 0){
			cout << "\nNo " + searchPrompt + " results found containing " + searchRequest + ".\n";
		} else{
			cout << to_string(results);
			if(results == 1){
				cout << " result "; 
			} else{
				cout << " results ";
			}
			cout << "found where the " << searchPrompt << " contains " << searchRequest << ".\n";

			if(deleteRecord && deleteResults(results)){
				deleteSubstring(findChoice, searchRequest);
			}
		}
	}

	void searchRange(const bool& deleteRecord){
		string yearInput;
		int yearLow = 1; 
		int yearHigh = 0;
		int results = 0;
		
		while(yearLow > yearHigh){
			cout << "Enter the lowest year range: ";
			getline(cin, yearInput);
			validateNumInput(yearInput, 1000, 2021, "yearLow");
			yearLow = stoi(yearInput);
			cout << "Enter the highest year range: ";
			getline(cin, yearInput);
			validateNumInput(yearInput, yearLow, 2021, "yearHigh");
			yearHigh = stoi(yearInput);
		}

		for(int i = 0; i < sz; i++){
			if(data[i].get_year() >= yearLow && data[i].get_year() <= yearHigh){
				if(results == 0){
					cout << "\nSearch Results\n"
						 << "--------------\n";
				}
				// print record
				printRecord(data[i]);
				results++;
			}
		}

		if(results == 0){
			cout << "\nNo results found in the range of " + to_string(yearLow) + " to " + to_string(yearHigh) + ".\n";
		} else{
			cout << to_string(results);
			if(results == 1){
				cout << " result "; 
			} else{
				cout << " results ";
			}
			cout << "found where the year is in the range of " << to_string(yearLow) + " to " + to_string(yearHigh) + ".\n";

			if(deleteRecord && deleteResults(results)){
				deleteRange(yearLow, yearHigh);
			}
		}
	}

	bool deleteResults(const int& results) const{
		string choice;
		cout << "\nDo you want to delete ";
		if(results == 1){
			cout << "this result ";
		} else{
			cout << "all " + to_string(results) + " results ";
		}
		cout << "from the database?\n"
			 << "1: Yes\n"
			 << "2: No\n"
			 << "Please enter the number of your choice: ";
		getline(cin, choice);
		validateNumInput(choice, 1, 2, "choice");
		if(stoi(choice) == 1){
			return true;
		}
		return false;
	}

	void deleteExact(const int& findChoice, const string& searchRequest){
		for(int i = 0; i < sz; i++){
			if(findChoice == 1){
				if(toLowerCase(data[i].get_name()) == toLowerCase(searchRequest)){
					// remove record
					removeRecord(i);
				}
			} else if(findChoice == 2){
				if(toLowerCase(data[i].get_album()) == toLowerCase(searchRequest)){
					// remove record
					removeRecord(i);
				}
			} else if(findChoice == 3){
				if(toLowerCase(data[i].get_artist()) == toLowerCase(searchRequest)){
					// remove record
					removeRecord(i);
				}
			} else if(findChoice == 4){
				if(data[i].get_year() == stoi(searchRequest)){
					// remove record
					removeRecord(i);
				}
			}
		}

		cout << "\nAll records of " + searchRequest + " has been successfully removed from the database!\n";
	}

	void deleteSubstring(const int& findChoice, const string& searchRequest){
		for(int i = 0; i < sz; i++){
			if(findChoice == 1){
				if(toLowerCase(data[i].get_name()).find(toLowerCase(searchRequest)) != string::npos){
					// remove record
					removeRecord(i);
				}
			} else if(findChoice == 2){
				if(toLowerCase(data[i].get_album()).find(toLowerCase(searchRequest)) != string::npos){
					// remove record
					removeRecord(i);
				}
			} else if(findChoice == 3){
				if(toLowerCase(data[i].get_artist()).find(toLowerCase(searchRequest)) != string::npos){
					// remove record
					removeRecord(i);
				}
			} 
		}

		cout << "All records of " + searchRequest + " has been successfully removed from the database!\n";
	}

	void deleteRange(const int& yearLow, const int& yearHigh){
		for(int i = 0; i < sz; i++){
			if(data[i].get_year() >= yearLow && data[i].get_year() <= yearHigh){
				// remove record
				removeRecord(i);
			}
		}

		cout << "All records with release years from " << yearLow << " to " << yearHigh 
			 << " has been successfully removed from the database!\n";
	}
	
	void removeRecord(int& i){
		// when a match is found, go through the array and move the
		// elements down to fill in the gaps from the removed element
		for(int j = i; j < sz; j++){
			if(j != sz-1){
				// replace current element with the value of the next index
				data[j] = data[j+1];
			}
		}

		// decrease the array size by one
		sz -= 1;
		// decrease the counter by one so that the loop can check the 
		// new element in the slot that it was shifted down to
		i--;
	}

	// https://publish.obsidian.md/cmpt125/The+STL+and+generic+programming
	void sortRecords(const int& findChoice, const int& order) const{
		string recordRequest = requestedField(findChoice);
		string orderRequest;
		Song* sortedData = new Song[cap];
		for(int i = 0; i < sz; i++){
			sortedData[i] = data[i];
		}

		if(findChoice != 4){
			if(findChoice == 1){
				std::sort(sortedData, sortedData + sz, byNameThenAlbum);
			} else if(findChoice == 2){
				std::sort(sortedData, sortedData + sz, byAlbumThenName);
			} else if(findChoice == 3){
				std::sort(sortedData, sortedData + sz, byArtistThenName);
			}

			if(order == 1){
				orderRequest = "alphabetical";
			} else{
				orderRequest = "reverse alphabetical";
				std::reverse(sortedData, sortedData + sz);
			}
		} else if(findChoice == 4){
			std::sort(sortedData, sortedData + sz, byYearThenName);

			if(order == 1){
				orderRequest = "ascending";
			} else{
				orderRequest = "descending";
				std::reverse(sortedData, sortedData + sz);
			}
		}

   		cout << "\nDatabase Results\n" 
   			 << "----------------\n";
		for(int i = 0; i < sz; i++){
			// print record
			printRecord(sortedData[i]);
		}

   		cout << "All " << to_string(sz) << " records displayed in " << orderRequest
   			 << " order according to " << recordRequest << "\n";
   		
		delete[] sortedData;
	}

	void songRec(const int& choice) const{
		int numberInput;

		if(choice == 1){
			string input;
			cout << "Enter a number from 0 to " + to_string(sz-1) + ": ";
			getline(cin, input);
			validateNumInput(input, 0, sz-1, "rec");
			numberInput = stoi(input);
		} else{
			// get a random index number
			numberInput = rand() % sz;
		}

		cout << "\nSelected Song\n"
			 << "-------------\n";
		printRecord(get_song(numberInput));
	}

	void clearData(){
		cout << "\nClear Database\n"
			 << "--------------\n";
		for(int i = 0; i < sz; i++){
			printRecord(get_song(i));
		}

		if(deleteResults(sz)){
			cap = 10;
			Song* emptyData = new Song[10];
			sz = 0;
			delete[] data;
			data = emptyData;
			cout << "\nDatabase successfully cleared!\n";
		} else {
			cout << "\nDatabase was not cleared.\n";
		}
	}

	// https://www.cplusplus.com/doc/tutorial/files/
	void saveToFile(const string& fname) const{
		// write to file from given file name
		ofstream textFile(fname);
		if(textFile.is_open()){

			for(int i = 0; i < sz; i++){
				textFile << data[i].get_name() << "*" 
						 << data[i].get_album() << "*"  
						 << data[i].get_artist() << "*" 
						 << to_string(data[i].get_year());
				if(i != sz-1){
					textFile << "\n";
				}
			}

			textFile.close();
		} else{
			// file error
			cout << "There was an error saving the database to textfile.\n";
		} 
		cout << "\nSuccessfully saved all records to " << fname << "! Closing the database.\n";
	}

	// Destructor
	~Database(){
		saveToFile("database.txt");
		delete[] data;
		data = nullptr;
	}
};