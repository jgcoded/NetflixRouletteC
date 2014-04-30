#include <stdio.h>
#include "netflixroulettec.h"

int main(int argc, char* argv[])
{
	struct nflx *movie;
	
	nflx_init();
	
	movie = nflx_get_data("The Boondocks", 2005);

	if (movie == NULL)
		exit(1);
	
	printf("unit: %d\n",         nflx_get_unit(movie));
	printf("show id: %d\n",      nflx_get_showid(movie));
	printf("release year: %d\n", nflx_get_release_year(movie));
	printf("show title: %s\n",   nflx_get_show_title(movie));
	printf("rating: %.1f\n",     nflx_get_rating(movie));
	printf("category: %s\n",     nflx_get_category(movie));
	printf("show cast: %s\n",    nflx_get_showcast(movie));
	printf("directory: %s\n",    nflx_get_director(movie));
	printf("summary: %s\n",      nflx_get_summary(movie));
	printf("poster: %s\n",       nflx_get_poster(movie));
	printf("media type: %s\n",   nflx_get_mediatype(movie) == NFLX_MOVIE
                                                     ? "movie" : "show");

	nflx_destroy(movie);
	nflx_deinit();

	return 0;
}
