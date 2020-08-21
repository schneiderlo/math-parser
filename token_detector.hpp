#ifndef MP_TOKEN_DETECTOR_HPP
#define MP_TOKEN_DETECTOR_HPP

#include "t_bracket.hpp"
#include "t_constant.hpp"
#include "t_function.hpp"
#include "t_number.hpp"
#include "t_operator.hpp"
#include "t_variable.hpp"

namespace mp
{
	std::shared_ptr<Token> detect_token(const std::string &var)
	{
		TokenType tt{ Token::detect_tokenType(var) };
		switch (tt)
		{
			case TokenType::NUMBER:		return std::make_shared<Number>(var);
			case TokenType::CONSTANT:	return std::make_shared<Constant>(var);
			case TokenType::VARIABLE:	return std::make_shared<Variable>(var);
			case TokenType::LEFT_BRACKET:	return std::make_shared<LeftBracket>();
			case TokenType::RIGHT_BRACKET:	return std::make_shared<RightBracket>();
			case TokenType::OPERATOR: return detect_operator(var);
			case TokenType::FUNCTION: return detect_function(var);
			default: throw std::invalid_argument("Error while detecting token, invalid syntax");
		}
	}
}



#endif // MP_TOKEN_DETECTOR_HPP