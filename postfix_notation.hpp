#ifndef MP_POSTFIX_NOTATION_HPP
#define MP_POSTFIX_NOTATION_HPP

#include "token_detector.hpp"
#include "string_misc.hpp"

namespace mp
{
	/**
	 * @class Postfix
	 *
	 * @fn Postfix()
     * Default constructor
	 *
	 * @fn Postfix(const string&)
     * Read an infix expression and convert it into postfix notation using
     * the internal function to_rpn.
	 *
	 * @fn to_rpn(const string&)
     * Convert a string in which an infix notation is stored to a postfix 
     * expression using the Shunting-yard Algorithm.
     * Note: tokens have to be separated by whitespace character.
     * @todo Possibility to input a string without whitespace. 
	 *
	 * @param vt
     * Postfix expression expressed as a vector of Token class instance.
     * It is obtained by reading an infix expression and by applying 
     * the Shunting-yard Algorithm.
	 */
	class Postfix
	{
		typedef std::shared_ptr<AbstractOperator> sp_ao;

	public:
        Postfix() = default;
        Postfix(const std::string& expr) { to_rpn(expr); }

        void to_rpn(const std::string&);
		double evaluate_rpn() const;

		std::string& to_infix() { return s_infix; }
		std::string to_postfix();

	protected:
		std::string s_infix;
		std::vector<sp_token> vsp_rpn;
	
	private:
		std::string infix_treatment(const std::string&);
	};
	

	std::string Postfix::to_postfix()
	{
		std::string result;
		for(auto &t : vsp_rpn)
			result += t->to_string() + " ";

		return result;
	}



	

	double Postfix::evaluate_rpn() const
	{
		std::stack<double> result;
		
		for(auto t : vsp_rpn)
		{
			if( is_operand(t) )
				result.push(t->evaluate());

			else if( is_function(t) )
				result.top() = t->evaluate(result.top());

			else if( is_operator(t) )
			{
				double rhs {result.top()};
				result.pop();
				result.top() = t->evaluate(result.top(), rhs);
			}
		}

		if(result.size() != 1)
			throw std::invalid_argument("Error while evaluating expression");
		
		return result.top();
	}



	std::string Postfix::infix_treatment(const std::string& expr)
	{
		std::string result {expr};

		// Delete possible whitespace at the beginning
		while( is_whitespace(result[0]) )
			result.erase(result.begin());

		// Delete possible duplicate whitespace
		for(size_t k=0; k<result.size(); k++)
		{
			if( is_whitespace(result[k]) )
			{
				for(size_t p=k+1; p<result.size() && is_whitespace(result[p]); )
					result.erase(result.begin() + p);
			}
		}

		// Delete last whitespace if one is detected
		if( is_whitespace(result[result.size()-1]) )
			result.erase(result.begin() + result.size()-1);
		
		
		// Add space when one is needed
		if( is_operator(result[0]) || is_left_bracket(result[0]) || is_right_bracket(result[0]) )
		{
			if( !is_whitespace(result[1]) )
				result.insert(1, " ");
		}
		
		for(size_t k=1; k<result.size()-1; k++)
		{
			if( is_operator(result[k]) || is_left_bracket(result[k]) || is_right_bracket(result[k]) )
			{
				if( !is_whitespace(result[k-1]) )
				{
					result.insert(k, " ");
					k++;
				}
				if( !is_whitespace(result[k+1]) )
				{
					result.insert(k+1, " ");
					k++;
				}
			}
		}
		
		if( is_operator(result[result.size()-1]) || is_left_bracket(result[result.size()-1]) || is_right_bracket(result[result.size()-1]) )
		{
			if( !is_whitespace(result[result.size()-2]) )
				result.insert(result.size()-1, " ");
		}

		return result;
	}



	void Postfix::to_rpn(const std::string& expr)
	{
		// Pre-treatment of input infix expression
		s_infix = infix_treatment(expr);

		// First step: split infix notation string into "string" tokens
		std::vector<std::string> expr_tokenized = str::split(s_infix, " ");

		// Conversion of "string" tokens to shared_ptr<Token> (s)
		std::vector<sp_token> vsp_raw_expr;
		vsp_rpn.clear();

		if( expr_tokenized[0] == "-" )
			vsp_raw_expr.push_back( detect_token(std::string ("0")) );
		for(size_t k=0; k<expr_tokenized.size(); k++)
		{
			if(k>0)
			{
				if( is_left_bracket(expr_tokenized[k-1]) && expr_tokenized[k] == "-" )
					vsp_raw_expr.push_back( detect_token(std::string ("0")) );
			}
			sp_token new_tok(detect_token(expr_tokenized[k]));
			vsp_raw_expr.push_back( new_tok );
		}

		// Third step: Constructing RPN expression
		std::stack<sp_token> stack;
		
		// Note: token is a shared_ptr to a Token
		for(auto token : vsp_raw_expr)
		{
			// If token is a number, add it to the vsp_rpn
			if( is_operand(token) )
			{
				bool is_already_detected {false};
				for(size_t k=0; k<vsp_rpn.size(); k++)
				{
					if(vsp_rpn[k] == token)
					{
						vsp_rpn.push_back(vsp_rpn[k]);
						is_already_detected = true;
						break;
					}
				}
				if( !is_already_detected )
					vsp_rpn.push_back(token);
			}
			
			// If token is a function, add it to the stack
			if( is_function(token) )
				stack.push(token);


			// If token is an operator
			else if( is_operator(token) )
			{
				sp_ao op1 = std::static_pointer_cast<AbstractOperator>(token);
				
				if( stack.size() > 0 )
				{
					// Token stored at the top of the stack
					while( is_operator(stack.top()) )
					{
						sp_token top_stack  = stack.top();
						sp_ao op2 = std::static_pointer_cast<AbstractOperator>(top_stack);

						if( (op1->is_left_associative()  && precedence_cmp(*op1, *op2) <= 0) 
						 || (op1->is_right_associative() && precedence_cmp(*op1, *op2) < 0) )
						{
							vsp_rpn.push_back(top_stack);
							stack.pop();
						}
						else 
							break;
							
						if(stack.size() == 0)
							break;
					}
				}

				// Operator is pushed onto the operator stack
				stack.push(token);
			}
			
			else if( is_left_bracket(token) )
				stack.push(token);

			else if( is_right_bracket(token) )
			{			
				while( !is_left_bracket(stack.top()) )
				{
					vsp_rpn.push_back(stack.top());
					stack.pop();
					if( stack.size() == 0 )
						throw std::invalid_argument("Missing brackets");
				}
				
				// Remove left bracket from stack
				stack.pop();

				// If function detectected, move it to ouput
				if( stack.size() > 0 )
				{
					if( is_function(stack.top()) )
					{
						vsp_rpn.push_back(stack.top());
						stack.pop();
					}
				}
			}
		}

		// All tokens have been read, place operator into the ouput queue
		while(stack.size() > 0)
		{
			if( is_right_bracket(stack.top()) )
				throw std::invalid_argument("Error while parsing expression.\nMismatched parenthesis.");

			else if( is_operator(stack.top()) )
			{
					vsp_rpn.push_back(stack.top());
					stack.pop();
			}

			else
				throw std::invalid_argument("Error while parsing expression.\nUnable to parse.");
		}
	}
}



#endif // MP_POSTFIX_NOTATION_HPP