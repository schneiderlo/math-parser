#ifndef STRING_MISC_H
#define STRING_MISC_H

#include "library.hpp"

	

namespace str
{

/**
* @brief split Split a line according to a specific seperator
*
* @param line 
*		String to be split
* @param separator
*		Character or string to use for the split
* @param list 
*		Either input or return variable of the function in which the 
*		splitted portions of the line are stored.
*/

std::vector<std::string> &split( std::string const& line, std::string const& separator, std::vector<std::string> &list );
std::vector<std::string>  split( std::string const& line, std::string const& separator );
std::vector<std::string>  split( std::string const& line, const char* separator );

/**
* @brief split Split a line according to a specific seperator
*
* @param line 
*		String to be split
* @param separator
*		Character or string to use for the split
* @param list 
*		Either input or return variable of the function in which the 
*		splitted portions of the line are stored.
*/

std::vector<std::string> &split( std::string const& line, std::string const& separator, std::vector<std::string> &list )
{
	// Vector initialization
	list.clear();
	
	// Index initialization
	size_t start(0);
	size_t end(0);
	
	// Iteration to split line string
	while( end!= std::string::npos )
	{
		end = line.find( separator, start );
		
		// Get the new item
		list.push_back( line.substr( start, end - start ) );
		
		start = end + separator.size();
	}
	
	return list;
}


std::vector<std::string> split( std::string const& line, std::string const& separator )
{
	std::vector<std::string> list;
	return split( line, separator, list );
}

std::vector<std::string> split( std::string const& line, const char* separator )
{
	return split( line, std::string(separator) );
}




	
/**
* @brief Misceallenous function to identity the type of character.
*
*/
inline bool is_whitespace(const char c)
{
 return (' '  == c) || ('\n' == c) ||
		('\r' == c) || ('\t' == c) ||
		('\b' == c) || ('\v' == c) ||
		('\f' == c) ;
}

inline bool is_operator_char(const char c)
{
 return ('+' == c) || ('-' == c) ||
		('*' == c) || ('/' == c) ||
		('^' == c) || ('<' == c) ||
		('>' == c) || ('=' == c) ||
		(',' == c) || ('!' == c) ||
		('(' == c) || (')' == c) ||
		('[' == c) || (']' == c) ||
		('{' == c) || ('}' == c) ||
		('%' == c) || (':' == c) ||
		('?' == c) || ('&' == c) ||
		('|' == c) || (';' == c) ;
}

inline bool is_math_operator(const char c)
{
 return ('+' == c) || ('-' == c) ||
		('*' == c) || ('/' == c) ;
}

inline bool is_letter(const char c)
{
 return (('a' <= c) && (c <= 'z')) ||
		(('A' <= c) && (c <= 'Z')) ;
}

inline bool is_digit(const char c)
{
 return ('0' <= c) && (c <= '9');
}

inline bool is_letter_or_digit(const char c)
{
 return is_letter(c) || is_digit(c);
}

inline bool is_left_bracket(const char c)
{
 return ('(' == c) || ('[' == c) || ('{' == c);
}

inline bool is_left_bracket(const std::string s)
{
	if( s.size() != 1 )
		return false;
	else return is_left_bracket( s[0] );
}

inline bool is_right_bracket(const char c)
{
 return (')' == c) || (']' == c) || ('}' == c);
}

inline bool is_bracket(const char c)
{
 return is_left_bracket(c) || is_right_bracket(c);
}

inline bool is_sign(const char c)
{
 return ('+' == c) || ('-' == c);
}
}

#endif // STRING_MISC_H