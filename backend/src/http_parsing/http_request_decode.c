#include "http.h"
#include "pthread.h"

extern pthread_key_t http_request_key;

void http_request_init(http_request_t *request, const char *request_str)
{
	request->_origin_addr = request_str;
	request->_source = (char *)malloc(strlen(request_str) + 1);
	strcpy(request->_source, request_str);

	request->method = NULL;
	request->host = NULL;
	request->path = NULL;
	request->_query_params_capacity = STARTING_QUERY_PARAMS_CAPACITY;
	request->query_params = (query_param_t*)malloc(request->_query_params_capacity * sizeof(struct query_param));
	request->query_params_num = 0;
	request->version = NULL;
	request->_headers_capacity = STARTING_HEADERS_CAPACITY;
	request->headers = (header_line_t*)malloc(request->_headers_capacity * sizeof(struct header_line));
	request->headers_num = 0;
	request->payload = NULL;
}

int on_method(llhttp_t *parser, const char *start, size_t length)
{
	http_request_t *request = (http_request_t *)pthread_getspecific(http_request_key);
	char *method = request->_source + (start - request->_origin_addr);
	request->method = method;
	method[length] = '\0';
	return 0;
}

int http_request_add_query_param_name(http_request_t *request, char *name)
{
	if (request->query_params_num >= request->_query_params_capacity)
	{
		request->_query_params_capacity *= QUERY_PARAMS_MULTIPLICATION_FACTOR;
		request->query_params = (query_param_t*)realloc(request->query_params, request->_query_params_capacity);
	}
	request->query_params[request->query_params_num].name = name;
	request->query_params_num++;
	return 0;
}

int on_url(llhttp_t *parser, const char *start, size_t length)
{
	http_request_t *request = (http_request_t *)pthread_getspecific(http_request_key);
	char *source_url = request->_source + (start - request->_origin_addr);
	source_url[length] = '\0';
	char buffer[length + 16] = "";
	char *scheme = NULL;
	char *host = NULL;
	char *path = NULL;
	char *query = NULL;
	CURLUcode curl_valid;
	int valid = 1;
	CURLU *curl = curl_url();
	char* contains_scheme = strstr(source_url, "://");
	if (contains_scheme == NULL)
	{
		strcpy(buffer, "http://");
		if(source_url[0] == '/') strcat(buffer, "no-host");
	}
	strcat(buffer, source_url);
	curl_valid = curl_url_set(curl, CURLUPART_URL, buffer, 0);

	if (curl_valid != CURLUE_OK)
	{
		curl_url_cleanup(curl);
		return -1;
	}

	if(contains_scheme != NULL){
		curl_url_get(curl, CURLUPART_SCHEME, &scheme, CURLU_URLDECODE);
		source_url[strlen(scheme)] = '\0';
		source_url += strlen(scheme) + 3;
	}

	curl_url_get(curl, CURLUPART_HOST, &host, CURLU_URLDECODE);

	if (strcmp(host, "no-host") != 0)
	{
		request->host = source_url;
		strcpy(source_url, host);
		source_url[strlen(host)] = '\0';
		source_url += strlen(host) + 1;
	}
	curl_url_get(curl, CURLUPART_PATH, &path, CURLU_URLDECODE);
	request->path = source_url;
	strcpy(source_url, path + 1);
	source_url[strlen(path) - 1] = '\0';
	source_url += strlen(path);

	if (curl_url_get(curl, CURLUPART_QUERY, &query, 0) == CURLUE_OK)
	{
		CURL *curl_easy = curl_easy_init();
		size_t query_length = strlen(query);
		int names_num = 0;
		int values_num = 0;
		for (int i = 0, j = 0; j < query_length + 1; j++)
		{
			if (query[j] == '=')
			{
				if(names_num != values_num || i == j){valid = 0; break;}
				int name_length;
				char *name = curl_easy_unescape(curl_easy, query + i, j - i, &name_length);
				strncpy(source_url, name, name_length);
				source_url[name_length] = '\0';
				http_request_add_query_param_name(request, source_url);
				source_url += name_length + 1;
				i = j + 1;
				curl_free(name);
				names_num++;
			}
			else if (query[j] == '&' || query[j] == '\0')
			{
				if(values_num != names_num - 1){valid = 0; break;}
				int value_length;
				char *value = curl_easy_unescape(curl_easy, query + i, j - i, &value_length);
				strncpy(source_url, value, value_length);
				source_url[value_length] = '\0';
				request->query_params[request->query_params_num - 1].value = source_url;
				source_url += value_length + 1;
				i = j + 1;
				curl_free(value);
				values_num++;
			}
		}
		curl_easy_cleanup(curl_easy);
	}
	curl_url_cleanup(curl);
	curl_free(scheme);
	curl_free(host);
	curl_free(path);
	curl_free(query);
	return valid ? 0 : -1;
}

int on_version(llhttp_t *parser, const char *start, size_t length)
{
	http_request_t *request = (http_request_t *)pthread_getspecific(http_request_key);
	char* version = (char*)malloc(sizeof(char) * strlen("HTTP/?.?") + 8);
	sprintf(version, "HTTP/%d.%d", parser->http_major, parser->http_minor);
	request->version = version;
	return 0;
}

int http_request_add_header_name(http_request_t *request, char *name)
{
	if (request->headers_num >= request->_headers_capacity)
	{
		request->_headers_capacity *= HEADERS_MULTIPLICATION_FACTOR;
		request->headers = (header_line_t*)realloc(request->headers, request->_headers_capacity);
	}
	request->headers[request->headers_num].name = name;
	request->headers_num++;
	return 0;
}

int on_header_field(llhttp_t *parser, const char *start, size_t length)
{
	http_request_t *request = (http_request_t *)pthread_getspecific(http_request_key);
	char *header_name = request->_source + (start - request->_origin_addr);
	http_request_add_header_name(request, header_name);
	header_name[length] = '\0';
	return 0;
}

int on_header_value(llhttp_t *parser, const char *start, size_t length)
{
	http_request_t *request = (http_request_t *)pthread_getspecific(http_request_key);
	char *header_value = request->_source + (start - request->_origin_addr);
	request->headers[request->headers_num - 1].value = header_value;
	header_value[length] = '\0';
	if (request->host == NULL && strcmp(request->headers[request->headers_num - 1].name, "Host") == 0)
	{
		request->host = header_value;
		char buffer[length + 8] = "";

		CURLUcode curl_valid;
		CURLU *curl = curl_url();
		if (strstr(header_value, "://") == NULL) strcpy(buffer, "http://");
		strcat(buffer, header_value);
		curl_valid = curl_url_set(curl, CURLUPART_URL, buffer, 0);
    curl_url_cleanup(curl);
		if (curl_valid != CURLUE_OK) {
			return -1;
		};
	}
	return 0;
}

int on_body(llhttp_t *parser, const char *start, size_t length)
{
	http_request_t *request = (http_request_t *)pthread_getspecific(http_request_key);
	char *payload = request->_source + (start - request->_origin_addr);
	request->payload = payload;
	payload[length] = '\0';
	return 0;
}

http_request_t *http_request_decode(const char *request_str)
{
	if(request_str == NULL || strlen(request_str) == 0)
		return NULL;

	llhttp_t parser;
	llhttp_settings_t settings;

	llhttp_settings_init(&settings);

	settings.on_method = on_method;
	settings.on_url = on_url;
	settings.on_version = on_version;
	settings.on_header_field = on_header_field;
	settings.on_header_value = on_header_value;
	settings.on_body = on_body;

	llhttp_init(&parser, HTTP_REQUEST, &settings);

	http_request_t *request = (http_request_t*)malloc(sizeof(http_request_t));
	http_request_init(request, request_str);

	pthread_setspecific(http_request_key, request);

	int request_len = strlen(request_str);

	enum llhttp_errno err = llhttp_execute(&parser, request_str, request_len);
	pthread_setspecific(http_request_key, NULL);
	
	if ((err != HPE_OK && err != HPE_INVALID_METHOD) || 
	    (err == HPE_INVALID_METHOD && request->headers_num == 0))
	{
		http_request_destroy(request);
		return NULL;
	}
	if(err == HPE_INVALID_METHOD && request->headers_num > 0){
		const char* last_header = request->headers[request->headers_num - 1].value;
		request->payload = last_header + strlen(last_header) + 4;
	}

	if(request->host == NULL)
	{
		request->host = request->path - 1;
	}

	if(request->payload==NULL)
	request->payload = request->method + strlen(request->method);

	return request;
}