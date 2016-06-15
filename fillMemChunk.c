#include "fillMemChunk.h"

MemoryStruct chunk;

static size_t WriteMemCallback(void *contents, size_t size, size_t nmemb,
			       void *userp)
{
	size_t realsize = size * nmemb;
	MemoryStruct *mem = (MemoryStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL)
	{
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		exit(EXIT_FAILURE);
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

void fillmemchunk(const char chunkURL[])
{
	CURL *curl_handle;
	CURLcode res;

	chunk.memory = malloc(1);
	/* will be grown as needed by the realloc above */
	chunk.size = 0; /* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init(); /* init the curl session */

	/* specify URL to get */
	curl_easy_setopt(curl_handle, CURLOPT_URL, chunkURL);

	/* send all data to this function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent
	   field, so we provide one */
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	res = curl_easy_perform(curl_handle); /* get it! */

	if (res != CURLE_OK) /* check for errors */
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		exit(EXIT_FAILURE);
	}
	else if (strcmp(chunk.memory, "HTTP") == 0) // redirect
	{
		long response_code;
		char *location;
		res = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE,
					&response_code);
		if ((res == CURLE_OK) && ((response_code / 100) != 3))
		{
			/* a redirect implies a 3xx response code */
			fprintf(stderr, "Not a redirect.\n");
		}
		else
		{
			res = curl_easy_getinfo(
				curl_handle, CURLINFO_REDIRECT_URL, &location);

			if ((res == CURLE_OK) && location)
			{
				/* This is the new absolute URL that you could
				 * redirect to, even if
				 * the Location: response header may have been a
				 * relative URL. */
				printf("Redirected to: %s\n", location);
			}
		}
	}

	curl_easy_cleanup(curl_handle); /* cleanup curl stuff */
	curl_global_cleanup();		/* we're done with libcurl, so clean it
					   up */
}
