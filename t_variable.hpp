#ifndef MP_T_VARIABLE_HPP
#define MP_T_VARIABLE_HPP

#include "token.hpp"

namespace mp
{
	class VariableInstance
	{
	public:
		VariableInstance() = default;
		VariableInstance(const std::string &var) : name{var}, val{0}
			{}

		static std::vector<std::shared_ptr<VariableInstance>> stored;
		
		std::string name;
		double val;
	};

	std::vector<std::shared_ptr<VariableInstance>> VariableInstance::stored;

	/**
	* @class Variable
	* Class for Variable 
	*
	* @fn evaluate	Return Variable value
	*
	* @param val	Stored value
	*/
	class Variable : public Token
	{
		friend class VariableInstance;

	public:
		Variable(const std::string &var);

		double evaluate() const { return sp_link->val; }
		//double evaluate() const { return val; }
		double evaluate(double const) const
			{ throw std::invalid_argument("Error while performing token evaluation.\nToken: Variable, no argument needed"); }
		double evaluate(double const, double const) const
			{ throw std::invalid_argument("Error while performing token evaluation.\nToken: Variable, no argument needed"); }

		bool is_variable()	const { return true; };

		void set_value(double const &a) { sp_link->val = a; }
		//void set_value(double const &a) { val = a; }

		// Friend streaming function
		virtual std::ostream& print(std::ostream& os) const
		{
			os << to_string();
			return os;
		}
		
		// Transform the Token to string
		std::string to_string() const { return sp_link->name; }
		// std::string to_string() const { return name; }
		
		// Count the number of variables
		size_t count() const { return sp_link.use_count(); }

	private:
		std::shared_ptr<VariableInstance> sp_link;
		//std::string name;
		//double		val;
	};


	Variable::Variable(const std::string &var)
	{
		// Check if the variable has already been created
		// Equivalent that they share same VariableInstance
		bool is_already_created {false};
		for(auto vi : VariableInstance::stored)
		{
			if(vi->name == var)
			{
				is_already_created = true;
				sp_link = vi;
				break;
			}
		}
		if(!is_already_created)
		{
			VariableInstance::stored.push_back( std::make_shared<VariableInstance>(var) );
			sp_link = VariableInstance::stored[VariableInstance::stored.size()-1];
		}
				// PRINT("var : " << to_string() << "\t" << sp_link.use_count());
	}
}

#endif // MP_T_VARIABLE_HPP