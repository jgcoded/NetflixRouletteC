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

#define NFLX_OK 1
#define NFLX_BAD -1

typedef enum
{
	NFLX_MOVIE=0,
	NFLX_SHOW

} NFLX_MEDIA;

struct nflx;

API void nflx_init();

API struct nflx* nflx_get_data(const char *title, const int year);

API int nflx_get_unit(struct nflx *media, int* dest);

API int nflx_get_showid(struct nflx *media, int* dest);

API int nflx_get_release_year(struct nflx *media, int *dest);

API int nflx_get_show_title(struct nflx *media, char *dest);

API int nflx_get_rating(struct nflx *media, double *dest);

API int nflx_get_category(struct nflx *media, char *dest);

API int nflx_get_showcast(struct nflx *media, char* dest);

API int nflx_get_director(struct nflx *media, char *dest);

API int nflx_get_summary(struct nflx *media, char *dest);

API int nflx_get_poster(struct nflx *media, char *dest);

API int nflx_get_mediatype(struct nflx *media);

API void nflx_destroy(struct nflx *media);

API void nflx_deinit();

#endif /* NETFLIXROULETTEC_H */
