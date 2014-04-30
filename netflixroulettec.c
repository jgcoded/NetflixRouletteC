#include "netflixroulettec.h"
#include <curl/curl.h>
#include <cJSON.h>

#define API_URL "http://netflixroulette.net/api/api.php?title=%s&year=%d"
#define API_URL_LENGTH 47

struct nflx
{
	char* url;
	CURL *curl;
	cJSON *cjson;
	char *data;
};

static size_t on_data_receive(void *content, size_t size, size_t nmemb, void *userData)
{
	struct nflx *n = (struct nflx*)userData;

	n->data = malloc(size * nmemb + 1);

	// out of memory 
	if (n->data == NULL)
		return 0;

	memcpy(&(n->data[0]), content, size*nmemb);

	n->data[size*nmemb] = 0;

	return size * nmemb;
}

char* replace_spaces(const char *title)
{
	int i = -1, j = 0;
	int numSpaces = 0;
	int newSize = 0;
	char* dest;

	while (title[++i] != '\0')
		if (isspace(title[i]))
			++numSpaces;

	newSize = strlen(title) + numSpaces * 3;
	dest = (char*)calloc(newSize, sizeof(char));
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

void generate_api_url(struct nflx *n, const char *title, int year)
{
	int titleLength, yearLength, newSize;
	char* newTitle = replace_spaces(title);

	titleLength = strlen(newTitle);
	yearLength = (year == 0) ? 1 : 4;
	newSize = API_URL_LENGTH + titleLength + yearLength + 1;

	n->url = (char*)malloc(newSize);
	n->url[newSize] = '\0';

	sprintf(n->url, API_URL, newTitle, year);
}

struct nflx* nflx_get_data(const char *title, int year)
{
	struct nflx n;
	CURLcode res;

	generate_api_url(&n, title, year);

	n.curl = curl_easy_init();

	if (n.curl == NULL)
		return NULL;

	curl_easy_setopt(n.curl, CURLOPT_WRITEFUNCTION, on_data_receive);
	curl_easy_setopt(n.curl, CURLOPT_WRITEDATA, (void *)&n);
	curl_easy_setopt(n.curl, CURLOPT_URL, n.url);

	res = curl_easy_perform(n.curl);

	if (res != CURLE_OK)
	{
		free(n.url);
		curl_easy_cleanup(n.curl);
		return NULL;
	}
	
	n.cjson = cJSON_Parse(n.data);

	return &n;
}

void nflx_init()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

int nflx_destroy(struct nflx *n)
{
	//if (n->url != NULL)
	//	free(n->url);

	if (n->curl != NULL)
		curl_easy_cleanup(n->curl);

	if (n->cjson != NULL)
		cJSON_Delete(n->cjson);

	if (n->data != NULL)
		free(n->data);
}

void nflx_deinit()
{
	curl_global_cleanup();
}