
#include <gtest/gtest.h>

#include "http.h"

TEST(HTTP, valid_request_with_no_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
				"Content-Length: 26\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_STREQ(request->host, "");
    EXPECT_EQ(request->headers_num, 1);
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.1");
    EXPECT_STREQ(request->payload, "my really beutiful payload");
    http_request_destroy(request);
}

TEST(HTTP, valid_request_with_two_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->host, "www.somehost.com"); 
    EXPECT_STREQ(request->headers[0].name, "Host");
    EXPECT_STREQ(request->headers[1].name, "Lang");
    EXPECT_STREQ(request->headers[0].value, "www.somehost.com");
    EXPECT_STREQ(request->headers[1].value, "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.1");
    EXPECT_STREQ(request->payload, "my really beutiful payload");   
    http_request_destroy(request);
}


TEST(HTTP, valid_request_HTTP_1_0) {
    char request_str[2048] =
        "POST http://www.somehost.com/somedir/page HTTP/1.0\r\n"
        "Accept-Language: en\r\n"
				"Content-Length: 26\r\n"
        "\r\n"
				"my really beutiful payload";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->headers[0].name, "Accept-Language");
    EXPECT_STREQ(request->headers[0].value, "en");
    EXPECT_STREQ(request->headers[1].name, "Content-Length");
    EXPECT_STREQ(request->headers[1].value, "26");
    EXPECT_STREQ(request->method, "POST");
    EXPECT_STREQ(request->host, "www.somehost.com");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.0");
    EXPECT_STREQ(request->payload, "my really beutiful payload");   
    http_request_destroy(request);
}



TEST(HTTP, valid_request_HTTP_1_0_with_query) {
    char request_str[2048] =
        "GET http://www.somehost.com/somedir/page?p=1&q=7 HTTP/1.0\r\n"
        "Lang: eng\r\n"
        "\r\n";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    
    EXPECT_EQ(request->query_params_num, 2);
    EXPECT_STREQ(request->query_params[0].name,  "p");
    EXPECT_STREQ(request->query_params[1].name,  "q");
    EXPECT_STREQ(request->query_params[0].value, "1");
    EXPECT_STREQ(request->query_params[1].value, "7");
    
    EXPECT_EQ(request->headers_num, 1);
    EXPECT_STREQ(request->headers[0].name, "Lang");
    EXPECT_STREQ(request->headers[0].value, "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->host, "www.somehost.com");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.0");
    EXPECT_STREQ(request->payload, "");   
    http_request_destroy(request);
}



TEST(HTTP, valid_request_HTTP_1_1_with_query) {
    char request_str[2048] =
        "GET /somedir/page?ppp=123&qqq=789 HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);

    EXPECT_EQ(request->query_params_num, 2);
    EXPECT_STREQ(request->query_params[0].name,  "ppp");
    EXPECT_STREQ(request->query_params[1].name,  "qqq");
    EXPECT_STREQ(request->query_params[0].value, "123");
    EXPECT_STREQ(request->query_params[1].value, "789");
    
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->headers[0].name, "Host");
    EXPECT_STREQ(request->headers[0].value, "www.somehost.com");
    EXPECT_STREQ(request->headers[1].name, "Lang");
    EXPECT_STREQ(request->headers[1].value, "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->host, "www.somehost.com");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.1");
    EXPECT_STREQ(request->payload, "my really beutiful payload");   
    http_request_destroy(request);
}


TEST(HTTP, invalid_request_missing_version1) {
    char request_str[2048] =
        "GET /somedir/page\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_version2) {
    char request_str[2048] =
        "GET /somedir/page \r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_version3) {
    char request_str[2048] =
        "GET /somedir/page  \r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_url1) {
    char request_str[2048] =
        "GET HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_url2) {
    char request_str[2048] =
        "GET  HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_url3) {
    char request_str[2048] =
        "GET   HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_method1) {
    char request_str[2048] =
        "/url/myurl HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_missing_method2) {
    char request_str[2048] =
        " /url/myurl HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_missing_method3) {
    char request_str[2048] =
        "  /url/myurl HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_empty) {
		char request_str[2048] = "\0";
		http_request_t* request = http_request_decode(request_str);
		ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, valid_request_no_payload) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->host, "www.somehost.com"); 
    EXPECT_STREQ(request->headers[0].name, "Host");
    EXPECT_STREQ(request->headers[1].name, "Lang");
    EXPECT_STREQ(request->headers[0].value, "www.somehost.com");
    EXPECT_STREQ(request->headers[1].value, "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.1");
    EXPECT_STREQ(request->payload, "");   
    http_request_destroy(request);
}

TEST(HTTP, invalid_request_no_method) {
    char request_str[2048] =
        "/somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_path) {
    char request_str[2048] =
        "GET HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_version) {
    char request_str[2048] =
        "GET /somedir/page\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_space_after_method) {
    char request_str[2048] =
        "GET/somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_space_before_http_version) {
    char request_str[2048] =
        "GET /somedir/pageHTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_colon_in_header) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_crlf_before_payload) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_weird_query) {
    char request_str[2048] =
        "GET /somedir/page?a&b HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_weird_query2) {
    char request_str[2048] =
        "GET /somedir/page?a=1&b HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_weird_query3) {
    char request_str[2048] =
        "GET /somedir/page?a&b=2 HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_no_weird_query4) {
    char request_str[2048] =
        "GET /somedir/page?a=&b=2 HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_weird_query5) {
    char request_str[2048] =
        "GET /somedir/page?a=1&b= HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_weird_query6) {
    char request_str[2048] =
        "GET /somedir/page?=1 HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_value_for_header) {
    char request_str[2048] =
        "GET /somedir/page?a=1 HTTP/1.1\r\n"
        "Host: \r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_value_for_header2) {
    char request_str[2048] =
        "GET /somedir/page?a=1 HTTP/1.1\r\n"
        "Host:\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_value_for_header3) {
    char request_str[2048] =
        "GET /somedir/page?=1 HTTP/1.1\r\n"
        "Host\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, lorem_ipsum){
    char lorem_ipsum_str[2048] = 
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
        "sed do eiusmod tempor incididunt ut labore et dolore magna "
        "aliqua. Ut enim ad minim veniam, quis nostrud exercitation "
        "ullamco laboris nisi ut aliquip ex ea commodo consequat. "
        "Duis aute irure dolor in reprehenderit in voluptate velit "
        "esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "
        "occaecat cupidatat non proident, sunt in culpa qui officia "
        "deserunt mollit anim id est laborum."
    ;
    http_request_t* request = http_request_decode(lorem_ipsum_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}