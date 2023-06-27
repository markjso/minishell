#include "minishell.h"

void debugFunctionName(char* function_name){
	 printf("%s\n", function_name); // Comment this line to prevent writing to console. 
	if (function_name)
		write(1, "", 1);
}
