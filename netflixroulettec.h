#ifndef NETFLIXROULETTEC_H
#define NETFLIXROULETTEC_H

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef NFLX_EXPORTS
#define API __declspec(dllexport)
#else
#ifndef NFLX_STATIC
#define API __declspec(dllimport)
#else
#define API extern
#define CURL_STATICLIB
#endif /*NFLX_STATIC */
#endif /*NFLX_EXPORTS */

/*! \brief Signifies operation completed succesfully 
 */
#define NFLX_OK 1

/*! \brief Signifies operation did not complete succesfully
 */
#define NFLX_BAD 0

/*! \brief The netflix media type. Compare with result to determine type
 */
typedef enum
{
	NFLX_MOVIE=0,
	NFLX_SHOW

} NFLX_MEDIATYPE;

/*! \brief Holds necessary data used to fulfill data requests
 * 
 * nflx is an opaque structure. Pass the structure to appropriate nflx_*
 * functions to receive data pertaining to the media obtained from the
 * nflx_get_data() function.
 */
struct nflx;

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Initializes NetflixRouletteC and its dependencies
 *
 * Sets up libcurl and takes care of any NetflixRouletteC specific
 * initializations. **Must be called before using any other function.**
 */
API void nflx_init();

/*! \brief Retrieves media data using the NetflixRoulette API
 * 
 * Sends a request to the NetflixRoulette API with the title and year
 * provided in the parameters. The year that is passed in can be 0.
 *
 * \param title The title of the media
 * \param year The media's release year (Can be 0 if unknown)
 * \return A valid nflx structure. If there was an error, returns NULL.
 */
API struct nflx* nflx_get_data(const char *title, const int year);

/*! \brief Retrieves the media's unit number
 *
 * \param media An initialized nflx structure
 * \return The unit number. On error, NFLX_BAD
 */
API int nflx_get_unit(const struct nflx *media);

/*! \brief Retrieves the media's show ID
 *
 * \param media An initialized nflx structure
 * \return The show ID. On error, NFLX_BAD
 */
API int nflx_get_showid(const struct nflx *media);

/*! \brief Retrieves the media's release year
 *
 * \param media An initialized nflx structure
 * \return The release year. On error, NFLX_BAD
 */
API int nflx_get_release_year(const struct nflx *media);

/*! \brief Retrieves the media's title
 *
 * \param media An initialized nflx structure
 * \return The show title. On error, NFLX_BAD
 */
API char* nflx_get_show_title(const struct nflx *media);

/*! \brief Retrieves the media's rating
 *
 * \param media An initialized nflx structure
 * \return The rating. On error, NFLX_BAD
 */
API double nflx_get_rating(const struct nflx *media);

/*! \brief Retrieves the media's category
 *
 * \param media An initialized nflx structure
 * \return The category. On error, NFLX_BAD
 */
API char* nflx_get_category(const struct nflx *media);

/*! \brief Retrieves the media's cast list
 *
 * \param media An initialized nflx structure
 * \return The cast list. On error, NFLX_BAD
 */
API char* nflx_get_showcast(const struct nflx *media);

/*! \brief Retrieves the media's director
 *
 * \param media An initialized nflx structure
 * \return The director. On error, NFLX_BAD
 */
API char* nflx_get_director(const struct nflx *media);

/*! \brief Retrieves the media's summary
 *
 * \param media An initialized nflx structure
 * \return The summaryr. On error, NFLX_BAD
 */
API char* nflx_get_summary(const struct nflx *media);

/*! \brief Retrieves the media's poster URL
 *
 * \param media An initialized nflx structure
 * \return The URL to the poster. On error, NFLX_BAD
 */
API char* nflx_get_poster(const struct nflx *media);

/*! \brief Retrieves the media's type
 *
 * \param media An initialized nflx structure
 * \return The NFLX_MEDIATYPE enum value. On error, -1
 */
API NFLX_MEDIATYPE nflx_get_mediatype(const struct nflx *media);

/*! \brief Frees up memory allocated by the nflx structure
 *
 * This function must be called once the nflx structure is no longer
 * needed. Once called, the nflx structure can no longer be used.
 *
 * param media An initialized nflx structure
 */
API void nflx_destroy(struct nflx *media);

/*! \brief Deinitializes NetflixRouletteC and its dependencies 
 *
 * ** Must be called at the end of program execution. **
 */
API void nflx_deinit();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NETFLIXROULETTEC_H */
