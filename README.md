NetflixRouletteC
================

A cross-platform C library for the [NetflixRoulette API](http://netflixroulette.net/api/). NetflixRouletteC uses libcurl and cJSON to
retreive and parse the data from the web. You don't need to have these dependencies pre-installed; NetflixRouletteC
downloads, builds, and links all dependencies for you.

Example
=======

```cpp
#include <stdio.h>
#include "netflixroulettec.h"

int main(int argc, char* argv[])
{
	struct nflx *movie;
	
	nflx_init();
	
	movie = nflx_get_data("House of Cards", 2013);

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
```

Building
========

You need [CMake](http://www.cmake.org/) in order to build NetflixRouletteC. CMake is a cross-platform build file generator.

On Windows, use CMake to generate Visual Studio build files, or build files for your preferred IDE. You can also
do this on Linux.

If you prefer Linux terminal commands and don't want to use an IDE, then run these commands to download and build
NetflixRouletteC:

```
$ git clone https://www.github.com/jgcoded/NetflixRouletteC
$ cd NetflixRouletteC && mkdir build && cd build
$ cmake -G "Unix Makefiles" ../
$ make
```

Contributing
============

If you would like to contribute, fork [this repository](https://github.com/jgcoded/NetflixRouletteC) on Github, and send a pull request with
your changes. 


