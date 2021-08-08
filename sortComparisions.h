// sortComparisions.h

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
// 1. Referenced CMPT 125 course notes on how to implement std::sort()  
// and std::reverse() with an array of objects
// - https://publish.obsidian.md/cmpt125/The+STL+and+generic+programming
// 2. Method for turning strings into all lowercase was learned in CMPT 127
//
/////////////////////////////////////////////////////////////////////////

string toLowerCase(string originalString){
	// go through the passed in string
	for(int i = 0; i < originalString.size(); i++){
		// if any characters are uppercase letters, turn it into lowercase
		if(originalString[i] >= 'A' && originalString[i] <= 'Z'){
			originalString[i] += 32;
		}
	}
	// return the lowercase string
	return originalString; 
}

// song name comparision for std::sort
bool bySongName(const Song& songA, const Song& songB){
	return toLowerCase(songA.get_name()) <= toLowerCase(songB.get_name());
}

// album comparision for std::sort
bool byAlbum(const Song& songA, const Song& songB){
	return toLowerCase(songA.get_album()) <= toLowerCase(songB.get_album());
}

// artist comparision for std::sort
bool byArtist(const Song& songA, const Song& songB){
	return toLowerCase(songA.get_artist()) <= toLowerCase(songB.get_artist());
}

// year comparision for std::sort
bool byYear(const Song& songA, const Song& songB){
	return songA.get_year() <= songB.get_year();
}

// compares the song name and then the album if the names are the same
bool byNameThenAlbum(const Song& songA, const Song& songB){
	if(toLowerCase(songA.get_name()) == toLowerCase(songB.get_name())){
		return byAlbum(songA, songB);
	} else{
		return bySongName(songA, songB);
	}
}

// compares the album and then the song name if the albums are the same
bool byAlbumThenName(const Song& songA, const Song& songB){
	if(toLowerCase(songA.get_album()) == toLowerCase(songB.get_album())){
		return bySongName(songA, songB);
	} else{
		return byAlbum(songA, songB);
	}
}

// compares the artist and then the song name is the artist is the same
bool byArtistThenName(const Song& songA, const Song& songB){
	if(toLowerCase(songA.get_album()) == toLowerCase(songB.get_album())){
		return bySongName(songA, songB);
	} else{
		return byArtist(songA, songB);
	}
}

// comapres the year and then the song name if the year is the same
bool byYearThenName(const Song& songA, const Song& songB){
	if(songA.get_year() == songB.get_year()){
		return bySongName(songA, songB);
	} else{
		return byYear(songA, songB);
	}
}