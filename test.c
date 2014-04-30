#include <stdio.h>
#include <stdlib.h>
#include "netflixroulettec.h"

int main(int argc, char* argv[])
{
	struct nflx *movie1;
	
	nflx_init();
	
	movie1 = nflx_get_data("The Boondocks", 2005);
	
	nflx_destroy(movie1);

	nflx_deinit();

	return 0;
}
