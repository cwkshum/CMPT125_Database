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
/////////////////////////////////////////////////////////////////////////

string toLowerCase(string originalString){
	for(int i = 0; i < originalString.size(); i++){
		if(originalString[i] >= 'A' && originalString[i] <= 'Z'){
			originalString[i] += 32;
		}
	}
	return originalString; 
}

// https://publish.obsidian.md/cmpt125/The+STL+and+generic+programming
bool bySongName(const Song& songA, const Song& songB){
	return toLowerCase(songA.get_name()) <= toLowerCase(songB.get_name());
}

bool byAlbum(const Song& songA, const Song& songB){
	return toLowerCase(songA.get_album()) <= toLowerCase(songB.get_album());
}

bool byArtist(const Song& songA, const Song& songB){
	return toLowerCase(songA.get_artist()) <= toLowerCase(songB.get_artist());
}

bool byYear(const Song& songA, const Song& songB){
	return songA.get_year() <= songB.get_year();
}

bool byNameThenAlbum(const Song& songA, const Song& songB){
	if(toLowerCase(songA.get_name()) == toLowerCase(songB.get_name())){
		return byAlbum(songA, songB);
	} else{
		return bySongName(songA, songB);
	}
}

bool byAlbumThenName(const Song& songA, const Song& songB){
	if(toLowerCase(songA.get_album()) == toLowerCase(songB.get_album())){
		return bySongName(songA, songB);
	} else{
		return byAlbum(songA, songB);
	}
}

bool byArtistThenName(const Song& songA, const Song& songB){
	if(toLowerCase(songA.get_album()) == toLowerCase(songB.get_album())){
		return bySongName(songA, songB);
	} else{
		return byArtist(songA, songB);
	}
}

bool byYearThenName(const Song& songA, const Song& songB){
	if(songA.get_year() == songB.get_year()){
		return bySongName(songA, songB);
	} else{
		return byYear(songA, songB);
	}
}