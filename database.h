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
//
// References
// ----------
// 1. Reference for using find_first_not_of() to determine if the 
// inputted string contains more than just whitespace characters.
// - https://www.cplusplus.com/reference/string/string/find_first_not_of/
// 2. Reference for isdigit() to check if the character is a decimal digit (learned in CMPT 127)
// - https://www.cplusplus.com/reference/cctype/isdigit/
// 3. Reference for using delimiter characters in getline()  
// to parse the records in the file by its field.
// - https://en.cppreference.com/w/cpp/string/basic_string/getline
// 4. Referenced CMPT 125 course notes on how to implement std::sort()  
// and std::reverse() with an array of objects
// - https://publish.obsidian.md/cmpt125/The+STL+and+generic+programming
// 5. Referenced how to write to files using ofstream
// - https://www.cplusplus.com/doc/tutorial/files/
// 6. Referenced my CMPT 125 Assignment 3 code  
//
/////////////////////////////////////////////////////////////////////////

// contains comparisions for std::sort
#include "sortComparisions.h" 

using namespace std;

class Database{
private:
	int sz;
	int cap;
	Song* data;

	bool existInDatabase(const string& songName, const string& album, 
						 const string& artist, const int& year) const{
		// go through the array and check if the song already exists in the database
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

	// 1. Reference for using find_first_not_of() to determine if the 
	// inputted string contains more than just whitespace characters.
	// - https://www.cplusplus.com/reference/string/string/find_first_not_of/
	void validateSongInput(string& songName) const{
		while(songName.find_first_not_of(" \n\t\r") == string::npos){
			// inputted song name only contains whitespace characters
			// (not valid), ask user for input again
			cout << "Invalid song name entered, please try again.\nEnter Song Name: ";
			getline(cin, songName);
		}
	}

	// check inputted album input for invalid characters
	void validateAlbumInput(string& album) const{
		while(album.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid album name entered, please try again.\nEnter Album Name: ";
			getline(cin, album);
		}
	}

	// check inputted artist input for invalid characters
	void validateArtistInput(string& artist) const{
		while(artist.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid artist name entered, please try again.\nEnter Artist Name: ";
			getline(cin, artist);
		}
	}

	// Check inputted numeric input for invalid characters
	// 1. Reference for isdigit() to check if the character is a decimal digit (learned in CMPT 127)
	// - https://www.cplusplus.com/reference/cctype/isdigit/
	void validateNumInput(string& input, const int& min, const int& max, 
						  const string& errorMsg) const{
		if(input.length() == 0){
			// empty string, not valid
			input = "-1";
		} else{
			// go through string and check if each character is a digit
			for(int i = 0; i < input.length(); i++){
				if(!isdigit(input[i])){
					// non-digit found, not valid
					input = "-1";
					break;
				} 
			}
		}

		// input is outside the min and max range
		while(stoi(input) < min || stoi(input) > max) {
			// print error message and ask for input again
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

			// check new input to see if it's a valid number
			if(input.length() == 0){
				// empty input, invalid
				input = "-1";
			} else{
				for(int i = 0; i < input.length(); i++){
					if(!isdigit(input[i])){
						// not a digit, invalid
						input = "-1";
						break;
					} 
				}
			}
		} 
	}

	// Return the corresponding string for the requested numeric choice
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
	// 1. Reference for using delimiter characters in getline()  
	// to parse the records in the file by its field.
	// - https://en.cppreference.com/w/cpp/string/basic_string/getline
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
					// read in the song name delimited by *
					getline(textFile, songName, '*');  
				} else if(recordField == 1){
					// read in the album delimited by *
					getline(textFile, album, '*'); 
				} else if(recordField == 2){
					// read in the artist delimited by *
					getline(textFile, artist, '*');  
				} else if(recordField == 3){
					// read in the year
					getline(textFile, year); 
				}
		      
				recordField++;
				
				// all fields of the record have been read in
				if(recordField == 4){
					// create a song element
					Song song(songName, album, artist, stoi(year));
					// add song to data array
					addData(song);
					// reset counter
					recordField = 0;
				}
			}
			textFile.close();
		} else{
			// file error
			cout << "There was an error opening and reading "
				 << fname << ".\n";
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

		// get song name and validate input
		cout << "Enter Song Name: ";
		getline(cin, songName);
		validateSongInput(songName);

		// get album and validate input
		cout << "Enter Album Name: ";
		getline(cin, album);
		validateAlbumInput(album);

		// get artist and validate input
		cout << "Enter Artist Name: ";
		getline(cin, artist);
		validateArtistInput(artist);

		// get year and validate input
		cout << "Enter Year of Release: ";
		getline(cin, yearString);
		validateNumInput(yearString, 1000, 2021, "year");
		// turn valid year string into an int
		year = stoi(yearString);

		// check if the song exists in the database
		if(existInDatabase(songName, album, artist, year)){
			// don't add to database
			cout << "\n" << songName << " by " << artist 
				 << " already exists in the database.\n";
		} else {
			// create a song instance
			Song newSong(songName, album, artist, year);
			// add to the array
			addData(newSong);
			cout << "\n" << songName << " by " << artist << " was successfully added!\n";
		}
	}

	void printRecord(const Song& song) const{
		// print the fields of the song
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

	void printSearchResults(int& results, const int& i) const{
		if(results == 0){
			// print header if the first match was found
			cout << "\nSearch Results\n"
				 << "--------------\n";
		}
		// print song details
		printRecord(data[i]);
		results++;
	}

	// search the array for an exact match
	void searchExact(const int& findChoice, const bool& deleteRecord){
		// get the corresponding field string based on the given numeric value
		string searchPrompt = requestedField(findChoice);
		string searchRequest;
		int results = 0;

		// get the user input
		cout << "Enter your " + searchPrompt + " search request: ";
		getline(cin, searchRequest);
		
		if(findChoice == 1){
			// validate song name input
			validateSongInput(searchRequest);
			// go through array and check for an exact song name match
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_name()) == toLowerCase(searchRequest)){
					printSearchResults(results, i);
				}
			}
		} else if(findChoice == 2){
			// validate album input
			validateAlbumInput(searchRequest);
			// go through array and check for an exact album match
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_album()) == toLowerCase(searchRequest)){
					printSearchResults(results, i);
				}
			}
		} else if(findChoice == 3){
			// validate artist input
			validateArtistInput(searchRequest);
			// go through array and check for an exact artist match
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_artist()) == toLowerCase(searchRequest)){
					printSearchResults(results, i);
				}
			}
		} else if(findChoice == 4){
			// validate year input
			validateNumInput(searchRequest, 1000, 2021, "year");
			// go through array and check for an exact year match
			for(int i = 0; i < sz; i++){
				if(data[i].get_year() == stoi(searchRequest)){
					printSearchResults(results, i);
				}
			}
		}

		if(results == 0){
			// no matching results were found
			cout << "\nNo " << searchPrompt << " results found matching " << searchRequest << ".\n";
		} else{
			// print the number of results found
			cout << to_string(results);
			if(results == 1){
				cout << " result "; 
			} else{
				cout << " results ";
			}
			cout << "found where the " << searchPrompt << " matches " << searchRequest << ".\n";

			// check if user wants to delete the results
			if(deleteRecord && deleteResults(results)){
				deleteExact(findChoice, searchRequest);
			}
		}
	}

	void searchSubstring(const int& findChoice, const bool& deleteRecord){
		// get the corresponding field string based on the given numeric value
		string searchPrompt = requestedField(findChoice);
		string searchRequest;
		int results = 0;

		// get user input
		cout << "Enter your " + searchPrompt + " substring search request: ";
		getline(cin, searchRequest);
		
		// validate the input and see if it occurs within the corresponding field in the array
		if(findChoice == 1){
			// Song Name
			validateSongInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_name()).find(toLowerCase(searchRequest)) != string::npos){
					printSearchResults(results, i);
				}
			}
		} else if(findChoice == 2){
			// Album
			validateAlbumInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_album()).find(toLowerCase(searchRequest)) != string::npos){
					printSearchResults(results, i);
				}
			}
		} else if(findChoice == 3){
			// Artist
			validateArtistInput(searchRequest);
			for(int i = 0; i < sz; i++){
				if(toLowerCase(data[i].get_artist()).find(toLowerCase(searchRequest)) != string::npos){
					printSearchResults(results, i);
				}
			}
		}

		if(results == 0){
			// no results found
			cout << "\nNo " + searchPrompt + " results found containing " + searchRequest + ".\n";
		} else{
			// print the number of results
			cout << to_string(results);
			if(results == 1){
				cout << " result "; 
			} else{
				cout << " results ";
			}
			cout << "found where the " << searchPrompt << " contains " << searchRequest << ".\n";

			// check if user wants to delete all results
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
		
		// check if the year range goes from low to high
		while(yearLow > yearHigh){
			// get lowest year and validate input
			cout << "Enter the lowest year range: ";
			getline(cin, yearInput);
			validateNumInput(yearInput, 1000, 2021, "yearLow");
			yearLow = stoi(yearInput);
			// get highest year and validate input
			cout << "Enter the highest year range: ";
			getline(cin, yearInput);
			validateNumInput(yearInput, yearLow, 2021, "yearHigh");
			yearHigh = stoi(yearInput);
		}

		// go through array and print the songs with years within the requested range
		for(int i = 0; i < sz; i++){
			if(data[i].get_year() >= yearLow && data[i].get_year() <= yearHigh){
				printSearchResults(results, i);
			}
		}

		if(results == 0){
			// no results found
			cout << "\nNo results found in the range of " << to_string(yearLow) 
				 << " to " + to_string(yearHigh) + ".\n";
		} else{
			// print the number of results
			cout << to_string(results);
			if(results == 1){
				cout << " result "; 
			} else{
				cout << " results ";
			}
			cout << "found where the year is in the range of " << to_string(yearLow) 
				 << " to " << to_string(yearHigh) << ".\n";

			// check if the user wants to delete all the results
			if(deleteRecord && deleteResults(results)){
				deleteRange(yearLow, yearHigh);
			}
		}
	}

	bool deleteResults(const int& results) const{
		string choice;
		// ask user if they want to delete all the results
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
		// get the user's choice and validate it
		getline(cin, choice);
		validateNumInput(choice, 1, 2, "choice");
		if(stoi(choice) == 1){
			// user has selected to delete results
			return true;
		}
		// don't delete results
		return false;
	}

	void deleteExact(const int& findChoice, const string& searchRequest){
		// go through array and if there's an exact match in  
		// the requested field, remove it from the array
		for(int i = 0; i < sz; i++){
			if(findChoice == 1){
				// check song name field
				if(toLowerCase(data[i].get_name()) == toLowerCase(searchRequest)){
					removeRecord(i);
				}
			} else if(findChoice == 2){
				// check album field
				if(toLowerCase(data[i].get_album()) == toLowerCase(searchRequest)){
					removeRecord(i);
				}
			} else if(findChoice == 3){
				// check artist field
				if(toLowerCase(data[i].get_artist()) == toLowerCase(searchRequest)){
					removeRecord(i);
				}
			} else if(findChoice == 4){
				// check year field
				if(data[i].get_year() == stoi(searchRequest)){
					removeRecord(i);
				}
			}
		}

		// print confirmation message
		cout << "\nAll records of " << searchRequest 
			 << " has been successfully removed from the database!\n";
	}

	void deleteSubstring(const int& findChoice, const string& searchRequest){
		// go through array and if the requested field contains 
		// the user's input string, remove it from the array
		for(int i = 0; i < sz; i++){
			if(findChoice == 1){
				// check song name field
				if(toLowerCase(data[i].get_name()).find(toLowerCase(searchRequest)) != string::npos){
					removeRecord(i);
				}
			} else if(findChoice == 2){
				// check album field
				if(toLowerCase(data[i].get_album()).find(toLowerCase(searchRequest)) != string::npos){
					removeRecord(i);
				}
			} else if(findChoice == 3){
				// check artist field
				if(toLowerCase(data[i].get_artist()).find(toLowerCase(searchRequest)) != string::npos){
					removeRecord(i);
				}
			} 
		}

		// print confirmation message
		cout << "\nAll records of " << searchRequest 
			 << " has been successfully removed from the database!\n";
	}

	void deleteRange(const int& yearLow, const int& yearHigh){
		// go through array and if the year is within
		// the given range, remove it from the array
		for(int i = 0; i < sz; i++){
			if(data[i].get_year() >= yearLow && data[i].get_year() <= yearHigh){
				// remove record
				removeRecord(i);
			}
		}

		// print confirmation message
		cout << "\nAll records with release years from " << yearLow << " to " << yearHigh 
			 << " has been successfully removed from the database!\n";
	}
	
	void removeRecord(int& i){
		// go through the array and move the elements down  
		// to fill in the gaps from the removed element
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

	// 1. Referenced CMPT 125 course notes on how to implement std::sort()  
	// and std::reverse() with an array of objects
	// - https://publish.obsidian.md/cmpt125/The+STL+and+generic+programming
	void sortRecords(const int& findChoice, const int& order) const{
		// get the corresponding field string based on the given numeric value
		string recordRequest = requestedField(findChoice);
		string orderRequest;

		// create a new array to store the sorted songs
		Song* sortedData = new Song[cap];
		for(int i = 0; i < sz; i++){
			// copy the songs over to the new array
			sortedData[i] = data[i];
		}

		if(findChoice != 4){
			if(findChoice == 1){
				// sort the array by song name (then by album if songs have the same name)
				std::sort(sortedData, sortedData + sz, byNameThenAlbum);
			} else if(findChoice == 2){
				// sort the array by album (then by song name if songs have the album)
				std::sort(sortedData, sortedData + sz, byAlbumThenName);
			} else if(findChoice == 3){
				// sort the array by artist (then by song name if songs have the artist)
				std::sort(sortedData, sortedData + sz, byArtistThenName);
			}

			// check which order the user requested 
			if(order == 1){
				orderRequest = "alphabetical";
			} else{
				orderRequest = "reverse alphabetical";
				// reverse the sorted array 
				std::reverse(sortedData, sortedData + sz);
			}
		} else if(findChoice == 4){
			// sort the array by year (then by song name if songs were released in the same year)
			std::sort(sortedData, sortedData + sz, byYearThenName);

			// check which order the user requested 
			if(order == 1){
				orderRequest = "ascending";
			} else{
				orderRequest = "descending";
				// reverse the sorted array
				std::reverse(sortedData, sortedData + sz);
			}
		}

		// print out the sorted array
   		cout << "\nDatabase Results\n" 
   			 << "----------------\n";
		for(int i = 0; i < sz; i++){
			printRecord(sortedData[i]);
		}

		// print a confirmation message
   		cout << "All " << to_string(sz) << " records displayed in " << orderRequest
   			 << " order according to " << recordRequest << "\n";
   		
   		// delete the sorted array
		delete[] sortedData;
	}

	void songRec(const int& choice) const{
		int numberInput;
		if(choice == 1){
			// ask user to enter an index number for the array and validate it
			string input;
			cout << "Enter a number from 0 to " + to_string(sz-1) + ": ";
			getline(cin, input);
			validateNumInput(input, 0, sz-1, "rec");
			numberInput = stoi(input);
		} else{
			// get a random index number
			numberInput = rand() % sz;
		}

		// print out the selected song based on index number
		cout << "\nSelected Song\n"
			 << "-------------\n";
		printRecord(get_song(numberInput));
	}

	void clearData(){
		// print out all the records in the array
		cout << "\nClear Database\n"
			 << "--------------\n";
		for(int i = 0; i < sz; i++){
			printRecord(get_song(i));
		}

		// check if user wants to delete all records
		if(deleteResults(sz)){
			// create a new empty array
			cap = 10;
			Song* emptyData = new Song[10];
			sz = 0;
			// delete the old array and set it to the empty array
			delete[] data;
			data = emptyData;
			cout << "\nDatabase successfully cleared!\n";
		} else {
			// user does not want to clear database
			cout << "\nDatabase was not cleared.\n";
		}
	}

	// 1. Referenced how to write to files using ofstream
	// - https://www.cplusplus.com/doc/tutorial/files/
	void saveToFile(const string& fname) const{
		// write to file from given file name
		ofstream textFile(fname);
		if(textFile.is_open()){
			// go through array and write the each record to the file
			for(int i = 0; i < sz; i++){
				// seperate the fields of each record using *
				textFile << data[i].get_name() << "*" 
						 << data[i].get_album() << "*"  
						 << data[i].get_artist() << "*" 
						 << to_string(data[i].get_year());
				if(i != sz-1){
					// start a new line if it is not the last record in the array
					textFile << "\n";
				}
			}
			textFile.close();
		} else{
			// file error
			cout << "There was an error saving the database to textfile.\n";
		} 

		// print confirmation message that the records have been saved
		cout << "\nSuccessfully saved all records to " << fname << "! Closing the database.\n";
	}

	// Destructor
	~Database(){
		// save the records stored in the array to the textfile
		saveToFile("database.txt");
		// delete array
		delete[] data;
		data = nullptr;
	}
};