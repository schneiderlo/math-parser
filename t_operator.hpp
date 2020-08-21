#ifndef MP_T_OPERATOR_HPP
#define MP_T_OPERATOR_HPP

#include "token.hpp"

namespace mp
{
    /** ******************************************************* **/

	/**
	* @class AbstractOperator
	* Abstract class for operators so they can be call the same way.
	*
	* @fn evaluate		Return value of (a op b)
	*
	* @param associativity		Define if the operator is left or right 
	* @param precedence		Define the precedence (order) of the operator
	*/
	class AbstractOperator : public Token
	{
	public:
		AbstractOperator(const int as, const int pre) : associativity(as), precedence(pre) {}

		virtual double evaluate() const
			{ throw std::invalid_argument("Error while performing evaluation. 2 arguments needed to evaluate operator"); }
		virtual double evaluate(double const) const
			{ throw std::invalid_argument("Error while performing evaluation. 2 arguments needed to evaluate operator"); }
		virtual double evaluate(double const, double const) const = 0;

		bool is_operator()	const { return true; };

		bool is_left_associative() { return !associativity; }
		bool is_right_associative() { return associativity; }

		friend inline int precedence_cmp(const AbstractOperator &lhs, const AbstractOperator &rhs)
			{ return lhs.precedence - rhs.precedence; }
	
	protected:
		bool associativity;	// 0 = left associative, 1 = right associative
		int  precedence;		// Precedence of operator
	};

	/**
	* @class Operator
	* Template class that specialize the AbstractOperator class
	*
	* @fn evaluate		Return value of (a op b)
	*/
	template<OperatorType OT> class Operator : public AbstractOperator
	{
	public:
		Operator() {}

		double evaluate(double const, double const) const;

		std::vector<sp_token> df(std::vector<sp_token> &vsp_t, std::shared_ptr<Variable> &sp_v);

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os << to_string();
			return os;
		}

		// Transform the Token to string
		virtual std::string to_string() const { return mp::to_string(OT); }
	};

	/**
	* @fn Operator constructor
	*/
	template<>
	Operator<OperatorType::PLUS>::Operator() : AbstractOperator(0,0) {}

	template<>
	Operator<OperatorType::MINUS>::Operator() : AbstractOperator(0,0) {}

	template<>
	Operator<OperatorType::MUL>::Operator() : AbstractOperator(0,1) {}

	template<>
	Operator<OperatorType::DIV>::Operator() : AbstractOperator(0,1) {}

	template<>
	Operator<OperatorType::POW>::Operator() : AbstractOperator(1,2) {}



	/**
	* @fn evaluate
	*/
	template<>
	double Operator<OperatorType::PLUS>::evaluate(const double a, const double b) const { return a + b; }

	template<>
	double Operator<OperatorType::MINUS>::evaluate(const double a, const double b) const { return a - b; }

	template<>
	double Operator<OperatorType::MUL>::evaluate(const double a, const double b) const { return a * b; }

	template<>
	double Operator<OperatorType::DIV>::evaluate(const double a, const double b) const
	{ 
		if( b == 0 )
			throw std::invalid_argument("Error: Division by 0 detected");
		return a / b;
	}

	template<>
	double Operator<OperatorType::POW>::evaluate(const double a, const double b) const { return std::pow(a,b); }



	/**
	* @fn detect_operator
	*
	* Return a shared_ptr to an AbstractOperator.
	* Current implementation :		+, -, *, / and ^
	*
	* It can be used as follow:
	*		2) op->evaluate(a,b)	to evaluate a op b
	*		   where op = detect_operator("op");
	*/

	std::shared_ptr<AbstractOperator> detect_operator(const std::string &var)
	{
		OperatorType ot {sto_OperatorType(var)};
		switch(ot)
		{
			case OperatorType::PLUS	 : return std::make_shared<Operator<OperatorType::PLUS>> ();
			case OperatorType::MINUS : return std::make_shared<Operator<OperatorType::MINUS>> ();
			case OperatorType::MUL   : return std::make_shared<Operator<OperatorType::MUL>> ();
			case OperatorType::DIV   : return std::make_shared<Operator<OperatorType::DIV>> ();
			case OperatorType::POW   : return std::make_shared<Operator<OperatorType::POW>> ();
			default: throw std::invalid_argument("Error while reading operator, invalid syntax");
		}			
	}




/*
    std::vector<sp_token> df(std::vector<sp_token> &vsp_t, std::shared_ptr<Variable> &sp_v)
    {
        
        return merge()
    }
    */
}



#endif // MP_T_OPERATOR_HPP