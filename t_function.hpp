#ifndef MP_T_FUNCTION_HPP
#define MP_T_FUNCTION_HPP

#include "token.hpp"

namespace mp
{
	/**
	* @class AbstractFunction
	* Abstract class for function so they can be call the same way.
	*
	* @fn evaluate		Return value of f(a)
	*/
	class AbstractFunction : public Token
	{
	public:
		AbstractFunction() = default;

		virtual double evaluate() const
			{ throw std::invalid_argument("Error while performing evaluation. 1 arguments needed to evaluate function"); }
		virtual double evaluate(double const) const = 0;
		virtual double evaluate(double const, double const) const
			{ throw std::invalid_argument("Error while performing evaluation. 1 arguments needed to evaluate function"); }

		bool is_function()	const { return true; };
	};

	/**
	* @class Operator
	* Template class that specialize the AbstractOperator class
	*
	* @fn evaluate		Return value of (a op b)
	*/
	template<FunctionType FT> class Function : public AbstractFunction
	{
	public:
		Function() = default;

		double evaluate(double const) const;

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os << to_string();
			return os;
		}

		// Transform the Token to string
		virtual std::string to_string() const { return mp::to_string(FT); }
	};

	/**
	* @fn evaluate
	*/
	template<>
	double Function<FunctionType::SQRT>::evaluate(const double a) const { return std::sqrt(a); }
	
	template<>
	double Function<FunctionType::COS>::evaluate(const double a) const { return std::cos(a); }
	
	template<>
	double Function<FunctionType::SIN>::evaluate(const double a) const { return std::sin(a); }
	
	template<>
	double Function<FunctionType::ATAN>::evaluate(const double a) const { return std::atan(a); }
	
	template<>
	double Function<FunctionType::EXP>::evaluate(const double a) const { return std::exp(a); }
	
	template<>
	double Function<FunctionType::LOG>::evaluate(const double a) const { return std::log(a); }


	/**
	* @fn detect_function
	*
	* Return a shared_ptr to an AbstractFunction.
	*
	* It can be used as follow:
	*		2) op->evaluate(b)	to evaluate f(a)
	*		   where op = detect_function("op");
	*/

	std::shared_ptr<AbstractFunction> detect_function(const std::string &var)
	{
		FunctionType ft {sto_FunctionType(var)};
		switch(ft)
		{
			case FunctionType::SQRT	 : return std::make_shared<Function<FunctionType::SQRT>> ();
			case FunctionType::COS	 : return std::make_shared<Function<FunctionType::COS>> ();
			case FunctionType::SIN	 : return std::make_shared<Function<FunctionType::SIN>> ();
			case FunctionType::ATAN	 : return std::make_shared<Function<FunctionType::ATAN>> ();
			case FunctionType::EXP	 : return std::make_shared<Function<FunctionType::EXP>> ();
			case FunctionType::LOG	 : return std::make_shared<Function<FunctionType::LOG>> ();
			default: throw std::invalid_argument("Error while reading Function, invalid syntax");
		}			
	}
}



#endif // MP_T_FUNCTION_HPP