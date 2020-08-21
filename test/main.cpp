#include "../postfix_notation.hpp"

using namespace std::chrono;


int main()
{
	

	std::vector<std::string> vs_infix = {
		"    ( 3 +   4 *   x - 2 ) ",
		"  2  / 4 - 2 ",
		"  sin ( 2 * 1.4 * 1.123 )     ",
		"2 * cos ( 1.4 * 1.123 ) * sin ( 1.4 * 1.123 )",
		"x ^ 4 + 2 - exp ( -2 /       pi)*(sin(x+pi / 2 ) + y)",
		"1 + x + x ^ 2 + y",
		"(2+ (   SD_OCR    -   SQRT    (    SD_OCR ^ 2 - ( SD_OCR - 56 * 0.9 ) ^ 2 ) ) + ( CD_ACTI_ETCH - 64 ) / 2 + ACTI_EDGE_RETARGETING_OPC_WC - ( PSD_EG_ADI_CD_ISO - 184 ) / 2 + SD_STACK_EFFECT + EPI_LATERAL_GROWTH + PGL2_4SIG_VARIABILITY_RX_PSD ) / 0.9"
	};

	for(auto e : vs_infix)
	{
		mp::Postfix pf(e);
		PRINT(pf.to_infix());
		PRINT(pf.to_postfix());
		PRINT("");
	}

	return 1;
}


/*
int main()
{
	std::vector<std::string> vs_infix;
	std::ifstream fl("equation.v");
	std::string line;
	while (std::getline(fl, line))
		vs_infix.push_back(line);

	int n(1000000);
	
	for (auto &e : vs_infix)
	{
		mp::Postfix pf(e);
		PRINT(pf.to_infix());

		// Start clock
 		steady_clock::time_point begin = steady_clock::now();	
		
		for(int i=0;i<n;i++)
			pf.evaluate_rpn();

		// End clock
		steady_clock::time_point end = steady_clock::now();	

		double runTimeInSecond =  duration_cast<milliseconds>(end - begin).count() / 1000.;
		PRINT( std::endl << "runtime (s): " << runTimeInSecond );
		PRINT(" ");
	}

		for (auto &v : mp::VariableInstance::stored)
			PRINT("VARIABLE: " << v->name << ",\tcount: " << v.use_count() );
 
    return 1;
}
*/