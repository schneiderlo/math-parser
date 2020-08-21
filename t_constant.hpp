#ifndef MP_T_CONSTANT_HPP
#define MP_T_CONSTANT_HPP

#include "token.hpp"

namespace mp
{
	/**
	 * @class Constant
	 */
	class Constant : public Token
	{
	public:
		Constant(const std::string &var);

		bool is_constant()	const { return true; }

		virtual double evaluate() const
			{ return value; }
		virtual double evaluate(double const) const
			{ throw std::invalid_argument("Error while performing evaluation: Constant token "); }
		virtual double evaluate(double const, double const) const
			{ throw std::invalid_argument("Error while performing evaluation: Constant token "); }

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os <<  to_string();
			return os;
		}
		
		// Transform the Token to string
		virtual std::string to_string() const { return name; }
    
    private:
        double value;
		std::string name;
	};

//#define M_PI 3.14159265359
//#define M_E	2.71828182846

	Constant::Constant(const std::string &var)
	{
		name = var;
		if( var == "PI" || var =="pi" )
            value = M_PI;
		else if( var == "e" )
            value = M_E;
		else 
			throw std::invalid_argument("Error, constant does not exist in software");
    }
}



#endif // MP_T_CONSTANT_HPP