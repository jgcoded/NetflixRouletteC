#ifndef NETFLIXROULETTEC_H
#define NETFLIXROULETTEC_H

#ifdef WIN32
#pragma warning(disable : 4193)
#pragma warning(disable : 4005)
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef NFLX_STATIC
#define CURL_STATICLIB
#endif /* NFLX_STATIC */

/* System includes */
#include <stdlib.h>
#include <string.h>

#define API extern

typedef enum
{
	NFLX_MOVIE=0,
	NFLX_SHOW

} NFLX_MEDIA;

struct nflx;

API void nflx_init();

API struct nflx* nflx_get_data(const char *title, const int year);

API int nflx_release_year(struct nflx *media, int *year);

API void nflx_destroy(struct nflx *n);

API void nflx_deinit();

#endif /* NETFLIXROULETTEC_H */
