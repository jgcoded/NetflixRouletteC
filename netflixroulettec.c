/* System includes */
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "netflixroulettec.h"
#include <curl/curl.h>
#include <cJSON.h>

#define API_URL "http://netflixroulette.net/api/api.php?title=%s&year=%d"
#define API_URL_LENGTH 51

#define API_ERRORCODE_STR "errorcode"
#define API_UNIT_STR "unit"
#define API_SHOWID_STR "show_id"
#define API_RELEASEYEAR_STR "release_year"
#define API_SHOWTITLE_STR "show_title"
#define API_RATING_STR "rating"
#define API_CATEGORY_STR "category"
#define API_SHOWCAST_STR "show_cast"
#define API_DIRECTOR_STR "director"
#define API_SUMMARY_STR "summary"
#define API_POSTER_STR "poster"
#define API_MEDIATYPE_STR "mediatype"

struct nflx
{
	CURL *curl;
	cJSON *cjson;
	char *data;
};

static size_t on_data_receive(void *content, size_t size, size_t nmemb, void *userData)
{
	struct nflx *n = (struct nflx*)userData;

	n->data = malloc(size * nmemb + 1);

	if (n->data == NULL)
		return 0;

	memcpy(n->data, content, size*nmemb);
	n->data[size*nmemb] = 0;

	return size * nmemb;
}

char* replace_spaces(const char *title)
{
	int i = -1, j = 0;
	int numSpaces = 0;
	size_t newSize = 0;
	char *dest;

	while (title[++i] != '\0')
		if (isspace(title[i]))
			++numSpaces;

	newSize = strlen(title) + numSpaces * 2;
	dest = (char*)malloc(newSize + 1);
	
	dest[newSize] = '\0';
	i = -1;
	while (title[++i] != '\0') {

		if (isspace(title[i])) {
			dest[j] = '%';
			dest[j + 1] = '2';
			dest[j + 2] = '0';
			j += 3;
		}
		else {
			dest[j] = title[i];
			++j;
		}
	}

	return dest;
}

char* generate_api_url(const char *title, const int year)
{
	size_t titleLength, yearLength, newSize;
	char *newTitle = replace_spaces(title);
	char *url;

	titleLength = strlen(newTitle);
	yearLength = (year == 0) ? 1 : 4;
	newSize = API_URL_LENGTH + titleLength + yearLength;

	url = (char*)malloc(newSize + 1);
	url[newSize] = '\0';

	sprintf(url, API_URL, newTitle, year);

	return url;
}

struct nflx* nflx_get_data(const char *title, const int year)
{
	CURLcode res;
	struct nflx *empty = (struct nflx*)malloc(sizeof(struct nflx));

	// out of memory
	if (empty == NULL)
		return NULL;

	empty->cjson = NULL;
	empty->curl = NULL;
	empty->data = NULL;

	char *url = generate_api_url(title, year);

	empty->curl = curl_easy_init();

	if (empty->curl == NULL)
		goto out;

	curl_easy_setopt(empty->curl, CURLOPT_WRITEFUNCTION, on_data_receive);
	curl_easy_setopt(empty->curl, CURLOPT_WRITEDATA, (void *)empty);
	curl_easy_setopt(empty->curl, CURLOPT_URL, url);

	res = curl_easy_perform(empty->curl);

	if (res != CURLE_OK)
		goto out;
	
	empty->cjson = cJSON_Parse(empty->data);

	if (empty->cjson == NULL)
		goto out;

	cJSON *errorCheck = cJSON_GetObjectItem(empty->cjson, API_ERRORCODE_STR);

	if (errorCheck != NULL)
		goto out;

	free(url);

	return empty;

out:
	if (url != NULL)
		free(url);

	nflx_destroy(empty);

	return NULL;
}

void nflx_init()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

int nflx_get_unit(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_UNIT_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valueint;
}

int nflx_get_showid(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_SHOWID_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valueint;
}

int nflx_get_release_year(const struct nflx *media)
{
	int year = 0;
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_RELEASEYEAR_STR);

	if (item == NULL)
		return NFLX_BAD;

	year = strtol(item->valuestring, NULL, 0);

	return year;
}

char* nflx_get_show_title(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_SHOWTITLE_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valuestring;
}

double nflx_get_rating(const struct nflx *media)
{
	double rating = 0;
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_RATING_STR);

	if (item == NULL)
		return NFLX_BAD;

	rating = strtod(item->valuestring, NULL);

	if (errno == ERANGE)
		return -1;

	return rating;
}

char* nflx_get_category(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_CATEGORY_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valuestring;
}

char* nflx_get_showcast(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_SHOWCAST_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valuestring;
}

char* nflx_get_director(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_DIRECTOR_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valuestring;
}

char* nflx_get_summary(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_SUMMARY_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valuestring;
}

char* nflx_get_poster(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_POSTER_STR);

	if (item == NULL)
		return NFLX_BAD;

	return item->valuestring;
}

NFLX_MEDIATYPE nflx_get_mediatype(const struct nflx *media)
{
	cJSON *item = cJSON_GetObjectItem(media->cjson, API_POSTER_STR);

	if (item == NULL)
		return -1;

	return item->valueint == 0 ? NFLX_MOVIE : NFLX_SHOW;
}

void nflx_destroy(struct nflx *media)
{
	if (media->cjson != NULL)
		cJSON_Delete(media->cjson);

	if (media->data != NULL)
		free(media->data);

	if (media->curl != NULL)
		curl_easy_cleanup(media->curl);

	if (media != NULL)
		free(media);
}

void nflx_deinit()
{
	curl_global_cleanup();
}
