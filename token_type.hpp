#ifndef MP_TOKEN_TYPE_HPP
#define MP_TOKEN_TYPE_HPP

#include "library.hpp"

#define MATCHING_FUNCTIONS(enumType, stable_enumType, str_to_enumType)	\
	inline std::string	to_string(const enumType t) { return stable_enumType[static_cast<int>(t)]; }	\
	inline enumType		str_to_enumType(const std::string &str) {		\
        auto matched_str_index{ std::find(stable_enumType.begin(), stable_enumType.end(), str) };   \
		auto pos{ std::distance(stable_enumType.begin(), matched_str_index) };	\
		if (pos < 0 || pos >= stable_enumType.size())		\
			throw std::invalid_argument("\nConversion from std::string to TokenType error.\nInvalid string.");		\
		return static_cast<enumType>(pos);		\
	}


namespace mp
{

    /**
     *	@enum TokenType
     *  Enum class to define the type of tokens that can have an expression
     *
     */

    enum class TokenType {
        NUMBER, FUNCTION, ARGUMENT_SEPARATOR, OPERATOR, CONSTANT,
        LEFT_BRACKET, RIGHT_BRACKET, VARIABLE, UNDEFINED_TOKEN
    };

    static const std::vector<std::string> vs_tt = {
        "NUMBER", "FUNCTION", "ARGUMENT_SEPARATOR", "OPERATOR", "CONSTANT",
        "LEFT_BRACKET", "RIGHT_BRACKET", "VARIABLE", "UNDEFINED_TOKEN"
	};
    


    /**
     *	@enum FunctionType
     *  Enum class that defined the implemented functions.
     */
    enum class FunctionType {
        SQRT, COS, SIN, ATAN, EXP, LOG
    };

    static const std::vector<std::string> vs_ft = {
        "sqrt", "cos", "sin", "atan", "exp", "log"
	};

	/**
     *	@fn bool is_function(const std::string &str)
     *  @return true if str is a function and false if not.
     */
    inline bool is_function(const std::string &str)
    {
        auto matched_str_index{ std::find(vs_ft.begin(), vs_ft.end(), str) };
		auto pos{ std::distance(vs_ft.begin(), matched_str_index) };
        if( pos < 0 || pos >= vs_ft.size() )
            return false;
        return true; 
    }



    
    /**
     *	@enum OperatorType
     *  Enum class that defined the implemented operator.
     */
    enum class OperatorType {
        PLUS, MINUS, MUL, DIV, POW
    };

    static const std::vector<std::string> vs_ot = {
        "+", "-", "*", "/", "^" };



    /**
     *	@fn bool is_operator(const std::string &str)
     *  @return true if str is an operator and false if not.
     */
    inline bool is_operator(const std::string &str)
    {
        auto matched_str_index{ std::find(vs_ot.begin(), vs_ot.end(), str) };
		auto pos{ std::distance(vs_ot.begin(), matched_str_index) };
        if( pos < 0 || pos >= vs_ot.size() )
            return false;
        return true; 
    }
	inline bool is_operator(const char c) { return is_operator(std::string(1,c)); }
    
    




    /**
     *	@enum ConstantType
     *  Enum class that defined the implemented operator.
     */
    enum class ConstantType {
        pi, e
    };

    static const std::vector<std::string> vs_ct = {
        "pi", "e" };

    /**
     *	@fn bool is_constant(const std::string &str)
     *  @return true if str is a constant and false if not.
     */
    inline bool is_constant(const std::string &str)
    {
        auto matched_str_index{ std::find(vs_ct.begin(), vs_ct.end(), str) };
		auto pos{ std::distance(vs_ct.begin(), matched_str_index) };
        if( pos < 0 || pos >= vs_ct.size() )
            return false;
        return true; 
    }
	inline bool is_constant(const char c) { return is_constant(std::string(1,c)); }

	/**
	*	@preprocessor function
	*	create functions to easily switch from string to enum class easily.
	*
	*	@fn std::string to_string(const EnumType et)
	*	@fn EnumType sto_EnumType(const std::string &var)
	*/

	MATCHING_FUNCTIONS(TokenType, vs_tt, sto_TokenType)
	MATCHING_FUNCTIONS(FunctionType, vs_ft, sto_FunctionType)
	MATCHING_FUNCTIONS(OperatorType, vs_ot, sto_OperatorType)
	MATCHING_FUNCTIONS(ConstantType, vs_ct, sto_ConstantType)
		

	inline bool is_whitespace(const char c) {
        return  (' '  == c) || ('\n' == c) ||
                ('\r' == c) || ('\t' == c) ||
                ('\b' == c) || ('\v' == c) || ('\f' == c) ;
	}

	inline bool is_letter(const char c) {
		return  (('a' <= c) && (c <= 'z')) ||
				(('A' <= c) && (c <= 'Z')) ;
	}

	inline bool is_digit(const char c) { return ('0' <= c) && (c <= '9'); }

	inline bool is_left_bracket(const char c) { return ('(' == c) || ('[' == c) || ('{' == c); }
	inline bool is_left_bracket(const std::string &str) { return is_left_bracket(str[0]); }

	inline bool is_right_bracket(const char c) { return (')' == c) || (']' == c) || ('}' == c); }

	inline bool is_argument_separtor(const char c) { return c == ','; }   
}

#endif // MP_TOKEN_TYPE_HPP