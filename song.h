// song.h

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

using namespace std;

class Song{
private: 
	// fields of the individual song record
	string name;
	string album;
	string artist;
	int year;
public: 
	// Empty Default Constructor
	Song()
	{}

	// Constructor
	Song(const string& name, const string& album, const string& artist, const int& year)
	: name(name), album(album), artist(artist), year(year)
	{}

	string get_name() const{
		// return song name
		return name;
	}

	string get_album() const{
		// return album name
		return album;
	}

	string get_artist() const{
		// return artist name
		return artist;
	}

	int get_year() const{
		// return release year
		return year;
	}

	// Destructor
	~Song(){}	
};