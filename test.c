#include <stdio.h>
#include <stdlib.h>
#include "netflixroulettec.h"
#include "cJSON.h"


int main(int argc, char* argv[])
{

	struct nflx *movie1;

	nflx_init();
	
	movie1 = nflx_get_data("Attack On Titan", 2010);

	nflx_destroy(movie1);

	nflx_deinit();

	return 0;
}

/*
const char *data = "{"
"\"unit\": 6596,"
"\"show_id\": 70153391,"
"\"show_title\": \"The Boondocks\","
"\"release_year\": \"2005\","
"\"rating\": \"4\","
"\"category\": \"Comedies\n\","
"\"show_cast\": \"Regina King, John Witherspoon, Cedric Yarbrough, Gary Anthony Williams, Jill Talley, Gabby Soleil\","
"\"director\": \"\","
"\"summary\": \"Based on the comic strip by Aaron McGruder, this satirical animated series follows the socially conscious misadventures of Huey Freeman,"
"a preternaturally smart 10-year-old who relocates from inner-city Chicago to the suburbs.\","
"\"poster\": \"http:\/\/cdn-2.nflximg.com\/en_us\/boxshots\/ghd\/70153391.jpg\","
"\"mediatype\": 1"
"}";

cJSON *root = cJSON_Parse(data);

int unit = cJSON_GetObjectItem(root, "unit")->valueint;

printf("\n%d\n", unit);
*/