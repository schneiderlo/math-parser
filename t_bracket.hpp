#ifndef MP_T_BRACKET_HPP
#define MP_T_BRACKET_HPP

#include "token.hpp"

namespace mp
{
	/**
	 * @class LeftBracket
	 */
	class LeftBracket : public Token
	{
	public:
		LeftBracket() {}

		bool is_left_bracket()	const { return true; }

		virtual double evaluate() const
			{ throw std::invalid_argument("Error while performing evaluation: left bracket token "); }
		virtual double evaluate(double const) const
			{ throw std::invalid_argument("Error while performing evaluation: left bracket token "); }
		virtual double evaluate(double const, double const) const
			{ throw std::invalid_argument("Error while performing evaluation: left bracket token "); }

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os <<  to_string();
			return os;
		}
		
		// Transform the Token to string
		virtual std::string to_string() const { return "("; }
	};



    
	/**
	 * @class RightBracket
	 */
	class RightBracket : public Token
	{
	public:
		RightBracket() {}

		bool is_right_bracket()	const { return true; }

		virtual double evaluate() const
			{ throw std::invalid_argument("Error while performing evaluation: right bracket token "); }
		virtual double evaluate(double const) const
			{ throw std::invalid_argument("Error while performing evaluation: right bracket token "); }
		virtual double evaluate(double const, double const) const
			{ throw std::invalid_argument("Error while performing evaluation: right bracket token "); }

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os <<  to_string();
			return os;
		}
		
		// Transform the Token to string
		virtual std::string to_string() const { return ")"; }
	};
}



#endif // MP_T_BRACKET_HPP