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

#include <sstream>
#include <cstdlib>

using namespace std;

class Database{
private:
	int sz;
	int cap;
	Song* data;

	string toLowerCase(string originalString) const{
		for(int i = 0; i < originalString.size(); i++){
			if(originalString[i] >= 'A' && originalString[i] <= 'Z'){
				originalString[i] += 32;
			}
		}
		return originalString; 
	}

	bool existInDatabase(const string& songName, const string& album, const string& artist, const int& year) const{
		for(int i = 0; i < sz; i++){
			if(toLowerCase(data[i].get_name()) == toLowerCase(songName) && 
				toLowerCase(data[i].get_album()) == toLowerCase(album) && 
				toLowerCase(data[i].get_artist()) == toLowerCase(artist) && data[i].get_year() == year){
				return true;
			}
		}

		return false;
	}

	void validateSongInput(string& songName){
		// https://www.cplusplus.com/reference/string/string/find_first_not_of/
		while(songName.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid song name entered, please try again.\nEnter Song Name: ";
			getline(cin, songName);
		}
	}

	void validateAlbumInput(string& album){
		while(album.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid album name entered, please try again.\nEnter Album Name: ";
			getline(cin, album);
		}
	}

	void validateArtistInput(string& artist){
		while(artist.find_first_not_of(" \n\t\r") == string::npos){
			cout << "Invalid artist name entered, please try again.\nEnter Artist Name: ";
			getline(cin, artist);
		}
	}

	void validateYearInput(int& year){
		while(cin.fail() || year < 1000 || year > 2021){ // ?????????????????? GET CURRENT YEAR ???????????????????????????????????
			if(cin.fail()){
				cin.clear(); // put us back in 'normal' operation mode
    			cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
			}
			cout << "Invalid release year entered, please try again.\nEnter Year of Release: ";
			cin >> year;
		}
	}

public:

	Database()
	: sz(0), cap(10), data(new Song[cap])
	{
		// use current time as seed for random generator
		srand(time(0));
	}

	Database(const string& fname)
	: sz(0), cap(10), data(new Song[cap])
	{
		string record, songName, album, artist, year;
		int recordField = 0;

		// read from given file name
		ifstream textFile(fname);
		if(textFile.is_open()){

			while(getline(textFile, record)){
				// parse the string 
				stringstream stream(record); //create string stream from the string
				recordField = 0;
				while(stream.good()) {
					if(recordField == 0){
						getline(stream, songName, '*'); //get first string delimited by comma 
					} else if(recordField == 1){
						getline(stream, album, '*'); //get first string delimited by comma 
					} else if(recordField == 2){
						getline(stream, artist, '*'); //get first string delimited by comma 
					} else if(recordField == 3){
						getline(stream, year, '*'); //get first string delimited by comma
					}
			      
					recordField++;
			   	}
				
				// create a song element
				Song song(songName, album, artist, stoi(year));

				// add song to data array
				addData(song);
			}

			textFile.close();
		} else{
			// file error
			cout << "There was an error opening and reading the database textfile.\n";
		} 

		// use current time as seed for random generator
		srand(time(0));
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
		string songName, album, artist;
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
		cin >> year;
		// validate input
		validateYearInput(year);


		// validate entry
		if(existInDatabase(songName, album, artist, year)){
			// don't add to database
			cout << songName << " by " << artist << " already exists in the database.\n";
		} else {
			Song newSong(songName, album, artist, year);
			addData(newSong);

			cout << songName << " by " << artist << " was successfully added!\n";
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
		string searchPrompt, searchRequest;
		int results = 0;
		int yearRequest;
		if(findChoice == 1){
			searchPrompt = "song";
		} else if(findChoice == 2){
			searchPrompt = "album";
		} else if(findChoice == 3){
			searchPrompt = "artist";
		} else if(findChoice == 4){
			searchPrompt = "year";
		}

		// !!!!!!! CONVERT YEAR TO GETLINE !!!!!!!!!
		cout << "Enter your " + searchPrompt + " search request: ";
		if(findChoice != 4){
			getline(cin, searchRequest);
		} else{
			cin >> yearRequest;
		}
		
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
			validateYearInput(yearRequest);
			for(int i = 0; i < sz; i++){
				if(data[i].get_year() == yearRequest){
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
			cout << "\nNo " + searchPrompt + " results found matching " + searchRequest + ".\n";
		} else{
			cout << to_string(results);
			if(results == 1){
				cout << " result found.\n";
			} else{
				cout << " results found.\n";
			}

			if(deleteRecord){
				int choice;
				cout << "\nDo you want to delete ";
				if(results == 1){
					cout << "this result ";
				} else{
					cout << "all " + to_string(results) + " results ";
				}
				cout << "from the database?\n"
					 << "1. Yes\n"
					 << "2. No\n"
					 << "Please enter the number of your choice: ";
				cin >> choice;
				while(cin.fail() || choice < 1 || choice > 2){
					if(cin.fail()){
						cin.clear(); // put us back in 'normal' operation mode
		    			cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
					}
					cout << "Invalid choice.\n" 
						 << "Please enter the number of your choice: ";
					cin >> choice;
				}
				cin.ignore(1,'\n');

				if(choice == 1){
					if(findChoice == 4){
						searchRequest = to_string(yearRequest);
					}
					deleteExact(findChoice, searchRequest);
				}
			}
		}
	}

	void searchSubstring(const int& findChoice, const bool& deleteRecord){
		string searchPrompt, searchRequest;
		int results = 0;
		if(findChoice == 1){
			searchPrompt = "song";
		} else if(findChoice == 2){
			searchPrompt = "album";
		} else if(findChoice == 3){
			searchPrompt = "artist";
		} 

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
				cout << " result found.\n";
			} else{
				cout << " results found.\n";
			}

			if(deleteRecord){
				int choice;
				cout << "\nDo you want to delete ";
				if(results == 1){
					cout << "this result ";
				} else{
					cout << "all " + to_string(results) + " results ";
				}
				cout << "from the database?\n"
					 << "1. Yes\n"
					 << "2. No\n"
					 << "Please enter the number of your choice: ";
				cin >> choice;
				while(cin.fail() || choice < 1 || choice > 2){
					if(cin.fail()){
						cin.clear(); // put us back in 'normal' operation mode
		    			cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
					}
					cout << "Invalid choice.\n" 
						 << "Please enter the number of your choice: ";
					cin >> choice;
				}
				cin.ignore(1,'\n');

				if(choice == 1){
					deleteSubstring(findChoice, searchRequest);
				}
			}
		}
	}

	void searchRange(const bool& deleteRecord){
		int yearLow = 1; 
		int yearHigh = 0;
		int results = 0;
		
		while(yearLow > yearHigh){
			cout << "Enter the lowest year range: ";
			cin >> yearLow;
			validateYearInput(yearLow);
			cout << "Enter the highest year range: ";
			cin >> yearHigh;
			validateYearInput(yearHigh);
			if(yearLow > yearHigh){
				cout << "Invalid range. Please input lowest year first.\n";
			}
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
				cout << " result found.\n";
			} else{
				cout << " results found.\n";
			}

			if(deleteRecord){
				int choice;
				cout << "\nDo you want to delete ";
				if(results == 1){
					cout << "this result ";
				} else{
					cout << "all " + to_string(results) + " results ";
				}
				cout << "from the database?\n"
					 << "1. Yes\n"
					 << "2. No\n"
					 << "Please enter the number of your choice: ";
				cin >> choice;
				while(cin.fail() || choice < 1 || choice > 2){
					if(cin.fail()){
						cin.clear(); // put us back in 'normal' operation mode
		    			cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
					}
					cout << "Invalid choice.\n" 
						 << "Please enter the number of your choice: ";
					cin >> choice;
				}
				cin.ignore(1,'\n');

				if(choice == 1){
					deleteRange(yearLow, yearHigh);
				}
			}
		}
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

		cout << "All records of " + searchRequest + " has been successfully removed from the database!\n";
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

	// https://publish.obsidian.md/cmpt125/notes+on+basic+sorting
	void sortRecords(const int& findChoice, const int& order){
		string recordRequest, orderRequest;
		Song* sortedData = new Song[cap];
		for(int i = 0; i < sz; i++){
			sortedData[i] = data[i];
		}

		if(findChoice == 1){
			recordRequest = "song";
		} else if(findChoice == 2){
			recordRequest = "album";
		} else if(findChoice == 3){
			recordRequest = "artist";
		} else if(findChoice == 4){
			recordRequest = "year";
			if(order == 1){
				orderRequest = "ascending";
			} else{
				orderRequest = "descending";
			}
		}

		if(findChoice != 4){
			if(order == 1){
				orderRequest = "alphabetical";
			} else{
				orderRequest = "reverse alphabetical";
			}
		}
		
		for(int i = 1; i < sz; ++i) {
			if(findChoice == 1){
				sortSong(sortedData, order, i);
			} else if(findChoice == 2){
				sortAlbum(sortedData, order, i);
			} else if(findChoice == 3){
				sortArtist(sortedData, order, i);
			} else if(findChoice == 4){
				sortYear(sortedData, order, i);
			}
   		}

   		cout << "\nDatabase Results\n" << "----------------\n";
		for(int i = 0; i < sz; i++){
			// print record
			printRecord(sortedData[i]);
		}

   		cout << "All " << to_string(sz) << " records displayed in " << orderRequest
   			 << " order according to " << recordRequest << "\n";
   		
		delete[] sortedData;
	}

	void sortSong(Song*& sortedData, const int& order, int& i){
		string key = toLowerCase(sortedData[i].get_name());    

		Song temp = sortedData[i];

		int j = i - 1;     

		if(order == 1){
			while(j >= 0 && toLowerCase(sortedData[j].get_name()) > key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		} else{
			while(j >= 0 && toLowerCase(sortedData[j].get_name()) < key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		}

		sortedData[j + 1] = temp;   
	}

	void sortAlbum(Song*& sortedData, const int& order, int& i){
		string key = toLowerCase(sortedData[i].get_album());    

		Song temp = sortedData[i];

		int j = i - 1;     

		if(order == 1){
			while(j >= 0 && toLowerCase(sortedData[j].get_album()) > key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		} else{
			while(j >= 0 && toLowerCase(sortedData[j].get_album()) < key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		}

		sortedData[j + 1] = temp;   
	}

	void sortArtist(Song*& sortedData, const int& order, int& i){
		string key = toLowerCase(sortedData[i].get_artist());    

		Song temp = sortedData[i];

		int j = i - 1;     

		if(order == 1){
			while(j >= 0 && toLowerCase(sortedData[j].get_artist()) > key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		} else{
			while(j >= 0 && toLowerCase(sortedData[j].get_artist()) < key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		}

		sortedData[j + 1] = temp;   
	}

	void sortYear(Song*& sortedData, const int& order, int& i){
		int key = sortedData[i].get_year();    // key is the value we are going to insert
		                // into the sorted part of v

		Song temp = sortedData[i];

		int j = i - 1;     // j points to one position before the 
		                // (possible) insertion point of the key;
		                // thus, key will eventually be inserted at 
		                // v[j + 1]

		//
		// This loop determines where to insert the key into the sorted part
		// of v. It does this by searching backwards through the sorted part
		// for the first value that is less than, or equal to, key.
		//
		// This loop combines searching with element moving. Every time an 
		// element bigger than the key is found, it is moved up one position.
		//
		// It's possible that there is no value in the sorted part that is 
		// smaller than key, in which case key gets inserted at the very
		// start of v. This is a special case that is handled by j >= 0 in
		// the loop condition.

		if(order == 1){
			while(j >= 0 && sortedData[j].get_year() > key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		} else{
			while(j >= 0 && sortedData[j].get_year() < key) {
				sortedData[j + 1] = sortedData[j];
				--j;
			}
		}

		sortedData[j + 1] = temp;   // j points to the location *before*
		               // the one where key will be inserted
	}

	void songRec(const int& choice){

		int numberInput;

		if(choice == 1){
			cout << "Enter a number from 0 to " + to_string(sz-1) + ": ";
			cin >> numberInput;

			// https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
			while(cin.fail() || numberInput < 0 || numberInput > sz-1){
				if(cin.fail()){
					cin.clear(); // put us back in 'normal' operation mode
	    			cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
				}
				cout << "Invalid choice.\n" 
					 << "Enter a number from 0 to " + to_string(sz) + ": ";
				cin >> numberInput;
			}

			// https://stackoverflow.com/questions/10311382/c-issue-getline-skips-first-input
			cin.ignore(1,'\n');

		} else{
			// get a random index number
			numberInput = rand() % sz;
		}

		cout << "\nSelected Song\n"
			 << "-------------\n";
		printRecord(get(numberInput));
	}

	Song get(const int& i) const{
		if(i < 0 || i > sz-1){
			// invalid index
			cout << "The requested index location is outside the bounds of the array.\n";
		}

		// return song at requested index
		return data[i];
	}

	// https://www.cplusplus.com/doc/tutorial/files/
	void saveToFile(const string& fname) const{
		// write to file from given file name
		ofstream textFile(fname);
		if(textFile.is_open()){

			for(int i = 0; i < sz; i++){
				textFile << data[i].get_name() << "*" 
						 << data[i].get_album() << "*"  
						 << data[i].get_artist() + "*" 
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
	}

	// Destructor
	~Database(){
		saveToFile("database.txt");
		delete[] data;
		data = nullptr;
	}

};