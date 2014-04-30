#ifndef NETFLIXROULETTEC_H
#define NETFLIXROULETTEC_H

#ifdef NFLX_STATIC
#define CURL_STATICLIB
#endif /* NFLX_STATIC */

#define NFLX_OK 1
#define NFLX_BAD 0

#define API extern

typedef enum
{
	NFLX_MOVIE=0,
	NFLX_SHOW

} NFLX_MEDIATYPE;

struct nflx;

API void nflx_init();

API struct nflx* nflx_get_data(const char *title, const int year);

API int nflx_get_unit(const struct nflx *media);

API int nflx_get_showid(const struct nflx *media);

API int nflx_get_release_year(const struct nflx *media);

API char* nflx_get_show_title(const struct nflx *media);

API double nflx_get_rating(const struct nflx *media);

API char* nflx_get_category(const struct nflx *media);

API char* nflx_get_showcast(const struct nflx *media);

API char* nflx_get_director(const struct nflx *media);

API char* nflx_get_summary(const struct nflx *media);

API char* nflx_get_poster(const struct nflx *media);

API NFLX_MEDIATYPE nflx_get_mediatype(const struct nflx *media);

API void nflx_destroy(struct nflx *media);

API void nflx_deinit();

#endif /* NETFLIXROULETTEC_H */
