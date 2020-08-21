#include "postfix_notation.hpp"

using namespace std::chrono;

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
