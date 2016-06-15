#ifndef CONSTANTS_H
#define CONSTANTS_H

/* maximum toon name's length */
#define MAX_TOON_NAME 100
/* maximum toon count */
#define MAX_TOON_COUNT 200
/* maximum match count */
#define TABLE_MATCH_ARGS_COUNT 5
/* toon id's length */
#define toonIdLength 6
/* maximum comicURL length */
#define MAX_COMIC_URL 200
/* maximum episodeTitle length */
#define MAX_EPISODE_TITLE 200
/* maximum episode Digit count */
#define MAX_EPISODE_DIGIT_COUNT 4

// CURL chunk maximum size

// clang-format off
static const char tableChunkURL[] = "http://comic.naver.com/webtoon/weekday.nhn";

static const char tableRegexString[] ="<a href=\"\\/webtoon\\/list\\.nhn\\?titleId=([[:digit:]]{0,6})&weekday=([[:alpha:]]{3})\" onclick=\"clickcr\\(this,'thm\\*[[:alpha:]]\\.tit','','[[:digit:]]+',event\\)\" class=\"title\" title=\"([^[:cntrl:]]+)\">([^[:cntrl:]]+)<\\/a>";
// clang-format on

#endif /* CONSTANTS_H */
