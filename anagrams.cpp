//
// CST 420 - Assignment # 4
//
// Author: Leander Rodriguez
//
// File: anagrams.cpp
//
// Due date:  Monday, August 12th by 11:59pm
//


#include  <fstream>
#include  <iostream>
#include  <string>
#include  <vector>
#include  <set>
#include  <algorithm>
#include  <iterator>

using namespace std;


typedef  ostream_iterator<string>  StrOStreamIter;
typedef  istream_iterator<string>  DictInIter;


//
// Finds anagrams in dictionary
//
class inDictionary
{
  public  :

    inDictionary( vector<string> dictionary )  :  m_dictionary(dictionary)  {}

	bool  operator()( string anagram )
    {
		return !binary_search( m_dictionary.begin(), m_dictionary.end(), anagram );
    }

  private  :

    vector<string>  m_dictionary;
};



//
// Returns factorial values
//
int  fact( int  num )
{
  if  (num == 0)  return  1;

  return  num * fact( num - 1 );
}



//
// Permutes userWord
//
class Permute
{
  public  :

    Permute( const string  &userWord )  :  m_word(userWord)  {}

    void  operator()( string  &newPerm )
    {
		next_permutation( m_word.begin(), m_word.end() );
		newPerm  =  m_word;
    }

  private  :

    string  m_word;
};



//
// Displays existing anagrams of the user's word
//
void display( set<string> anagrams, string userWord )
{
	if( anagrams.empty() )
	{
		cout  <<  "  "  <<  userWord  <<  " does not have any anagrams";
	}
	else
	{
		cout <<  "  "  <<  "Anagram: ";

		StrOStreamIter  output(cout, " ");

		copy( anagrams.begin(), anagrams.end(), output );	
	}

	cout  <<  endl  <<  endl;
}



//
// Permute userWord and find existing anagrams in dictionary
//
void findAnagrams( vector<string> dictionary, string userWord )
{		
	//
	// userWord is permuted and stored in container
	//
	vector<string> perms( fact(userWord.length() ) );
	for_each( perms.begin(), perms.end(), Permute(userWord) );

	
	//
	// Eliminate anagrams not found in dictionary
	//
	vector<string>::iterator new_end = remove_if( perms.begin(), perms.end(), inDictionary( dictionary ) );
	perms.erase(new_end, perms.end());

	
	// 
	// Remove duplicate anagrams and eliminate anagram if 
	// it is the same as the userWord and 
	//
	set<string> anagrams( perms.begin(), perms.end() );
	anagrams.erase( userWord );


	//
	// Display anagrams
	//
	display( anagrams, userWord );
}



//
// Main routine
//
int  main()
{
	
	string  dictFilename( "dictionary.txt" ),
			userWord;
	
	
	//
	// Prompt user for file name
	//
	cout  <<  "Enter dictionary file name: ";

	getline( cin, dictFilename );

	cout <<  endl;
	

	//
	// Open file and store dictionary entries read in from file
	// 
	ifstream in( dictFilename );

	vector<string> dictionary;
	copy( DictInIter( in ), DictInIter(), inserter( dictionary, dictionary.end() ) );


	//
	// Prompt user for word and find anagrams 
	//
	while( 1 )
	{

		cout  <<  "Enter a word: ";
		getline( cin, userWord );


		//
		// Break out of the loop if the word is "quit"
		//
		if( userWord == "quit" )  break;


		//
		// Check if userWord is in dictionary
		//
		if( !binary_search( dictionary.begin(), dictionary.end(), userWord ) )
		{
			cout  <<  "  "  <<  userWord  <<  " is not a valid word"  <<  endl  <<  endl;  
			continue;
		}


		findAnagrams( dictionary, userWord );
	}
	
  return  EXIT_SUCCESS;

}
