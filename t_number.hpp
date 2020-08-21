#ifndef MP_T_NUMBER_HPP
#define MP_T_NUMBER_HPP

#include "token.hpp"

namespace mp
{
	/**
	* @class Number
	* Class for number 
	*
	* @fn evaluate	Return number value
	*
	* @param val	Stored value
	*/
	class Number : public Token
	{
	public:
		Number(const double tval) : val(tval) {}
		Number(const std::string &var);

		//std::vector<sp_token> df(std::vector<sp_token> &vsp_t, std::shared_ptr<Variable> &sp_v);

		double evaluate() const { return val; }
		double evaluate(double const) const
			{ throw std::invalid_argument("Error while performing token evaluation. Token: number, no argument needed"); }
		double evaluate(double const, double const) const
			{ throw std::invalid_argument("Error while performing token evaluation. Token: number, no argument needed"); }

		bool is_number()		const { return true; };

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os << val;
			return os;
		}
		
		// Transform the Token to string
		virtual std::string to_string() const { return std::to_string(val); }

	private:
		double val;
	};


	Number::Number(const std::string &var)
	{
		try {
			val = std::stod(var);
		}
		catch(const std::invalid_argument& ia) {
			std::cerr << "Error while reading number instance: " << ia.what() << std::endl;
		}
	}
}



#endif // MP_T_NUMBER_HPP