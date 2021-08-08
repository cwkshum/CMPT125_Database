CMPT 125 Assignment 5
=====================

Names of Team Members
---------------------
Carissa Shum, cws8@sfu.ca, 301359502


Limitations
-----------
N/A


Known Bugs
----------
N/A


Extra Features
--------------
1. A song recommendation feature was implemented where users
can choose to input an index number within the range of the 
array storing the database records and the program will 
return the corresponding song at that index, or the user can 
request for a random song recommendation which will cause the
program to generate a random index location and display the 
corresponding song to the user.

2. A clear database feature was implemented where the program 
will all the records that are being stored in the array and the 
user can decide if they want to clear the database, which will
empty the array. 


Implementation Notes
--------------------
1. The program is case insensitive, thus when searching in
for a match in the database, if the user inputs the song name 
in all capital letters but the song name in the database is in 
a mix of lower and uppercase letters, it will still register that
the search input and the record in the database are the same.

2. When finding an exact match for the artist, if the user searches
the name of an artist such as Bon Iver, it will only return the records
in which Bon Iver is the only artist of the song. It will not return
songs in which there are multiple artists that share the song with
Bon Iver. For instance, if Bon Iver is featured on a song with Taylor
Swift, that song will not be considered an exact match. 