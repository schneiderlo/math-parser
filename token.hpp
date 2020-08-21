#ifndef MP_TOKEN_DYNAMIC_HPP
#define MP_TOKEN_DYNAMIC_HPP

#include "design_pattern.hpp"
#include "token_type.hpp"

namespace mp
{
	class Variable;

    /**
     *	@class Token
     *  Enum class to define the type of tokens that can have an expression
     *
     */
	class Token
	{
	public:
		Token() {}
		virtual ~Token() = default;

		static TokenType detect_tokenType(const std::string &var)
		{
			TokenType tt {TokenType::UNDEFINED_TOKEN};
			if(var.size() == 0)
				throw std::invalid_argument("\nError while reading raw expression:\nToken is empty");

			if( mp::is_operator(var) )
				tt = TokenType::OPERATOR;
			else if(is_digit(var[0]) || var[0] == '-' )
				tt = TokenType::NUMBER;
			else if(mp::is_function(var))
				tt = TokenType::FUNCTION;
			else if(mp::is_constant(var))
				tt = TokenType::CONSTANT;
			else if(var.size() == 1)
			{
				if( mp::is_left_bracket(var[0]) )
					tt = TokenType::LEFT_BRACKET;
				else if( mp::is_right_bracket(var[0]) )
					tt = TokenType::RIGHT_BRACKET;
				else
					tt = TokenType::VARIABLE;
			}
			else 
				tt = TokenType::VARIABLE;

			// PRINT("token \"" << var << "\"\t: " << mp::to_string(tt));

			return tt;
		}

		virtual bool is_function()	const { return false; };
		virtual bool is_operator()	const { return false; };
		virtual bool is_constant()	const { return false; };
		virtual bool is_variable()	const { return false; };
		virtual bool is_number()	const { return false; };
		virtual bool is_left_bracket()	const { return false; };
		virtual bool is_right_bracket()	const { return false; };

		virtual double evaluate() const = 0;
		virtual double evaluate(double const) const = 0;
		virtual double evaluate(double const, double const) const = 0;

		virtual void set_value( double const &a) { throw std::invalid_argument("Token does not handle set_value"); }

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
        {
			os << to_string();
			return os;
		}

		virtual std::string to_string() const { return "UndefinedToken"; }
	};


	typedef std::shared_ptr<Token> sp_token;


	

	std::ostream& operator<<(std::ostream& os, const Token& t) { return t.print(os); }

	std::string to_string(const Token& t) { return t.to_string(); }

	inline bool operator==(const Token &lhs, const Token &rhs) { return lhs.to_string() == rhs.to_string(); }
	inline bool operator!=(const Token &lhs, const Token &rhs) { return !(lhs==rhs); }


	// Friend function for better code writing (friend keyword could be deleted)
	inline bool is_function(const Token &t)		{ return t.is_function(); }
	inline bool is_operator(const Token &t)		{ return t.is_operator(); }
	inline bool is_constant(const Token &t)		{ return t.is_constant(); }
	inline bool is_variable(const Token &t)		{ return t.is_variable(); }
	inline bool is_number(const Token &t)		{ return t.is_number(); }
	inline bool is_left_bracket(const Token &t)	{ return t.is_left_bracket(); }
	inline bool is_right_bracket(const Token &t) { return t.is_right_bracket(); }
	inline bool is_operand(const Token &t)
		{ return is_number(t) || is_constant(t) || is_variable(t); }

	inline bool is_function(std::shared_ptr<Token> t)		{ return t->is_function(); }
	inline bool is_operator(std::shared_ptr<Token> t)		{ return t->is_operator(); }
	inline bool is_constant(std::shared_ptr<Token> t)		{ return t->is_constant(); }
	inline bool is_variable(std::shared_ptr<Token> t)		{ return t->is_variable(); }
	inline bool is_number(std::shared_ptr<Token> t)		{ return t->is_number(); }
	inline bool is_left_bracket(std::shared_ptr<Token> t)	{ return t->is_left_bracket(); }
	inline bool is_right_bracket(std::shared_ptr<Token> t) { return t->is_right_bracket(); }
	inline bool is_operand(std::shared_ptr<Token> t)
		{ return is_number(t) || is_constant(t) || is_variable(t); }
		



	
}



#endif // MP_TOKEN_DYNAMIC_HPP