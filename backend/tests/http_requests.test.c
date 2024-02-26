
#include <gtest/gtest.h>

#include "http.h"

TEST(HTTP, valid_request_with_no_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_STREQ(request->host, "");
    EXPECT_EQ(request->headers_num, 0);
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
    EXPECT_STREQ(request->host, ""); 
    EXPECT_STREQ(request->header_names[0], "Host");
    EXPECT_STREQ(request->header_names[1], "Lang");
    EXPECT_STREQ(request->header_values[0], "www.somehost.com");
    EXPECT_STREQ(request->header_values[1], "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.1");
    EXPECT_STREQ(request->payload, "my really beutiful payload");   
    http_request_destroy(request);
}


TEST(HTTP, valid_request_HTTP_1_0) {
    char request_str[2048] =
        "GET http://www.somehost.com/somedir/page HTTP/1.0\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 1);
    EXPECT_STREQ(request->header_names[0], "Lang");
    EXPECT_STREQ(request->header_values[0], "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->host, "http://www.somehost.com");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.0");
    EXPECT_STREQ(request->payload, "my really beutiful payload");   
    http_request_destroy(request);
}



TEST(HTTP, valid_request_HTTP_1_0_with_query) {
    char request_str[2048] =
        "GET http://www.somehost.com/somedir/page?p=1&q=7 HTTP/1.0\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    
    EXPECT_EQ(request->query_params_num, 2);
    EXPECT_STREQ(request->query_param_names[0],  "p");
    EXPECT_STREQ(request->query_param_names[1],  "q");
    EXPECT_STREQ(request->query_param_values[0], "1");
    EXPECT_STREQ(request->query_param_values[1], "7");
    
    EXPECT_EQ(request->headers_num, 1);
    EXPECT_STREQ(request->header_names[0], "Lang");
    EXPECT_STREQ(request->header_values[0], "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->host, "http://www.somehost.com");
    EXPECT_STREQ(request->path, "somedir/page");
    EXPECT_STREQ(request->version, "HTTP/1.0");
    EXPECT_STREQ(request->payload, "my really beutiful payload");   
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
    EXPECT_STREQ(request->query_param_names[0],  "ppp");
    EXPECT_STREQ(request->query_param_names[1],  "qqq");
    EXPECT_STREQ(request->query_param_values[0], "123");
    EXPECT_STREQ(request->query_param_values[1], "789");
    
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->header_names[0], "Host");
    EXPECT_STREQ(request->header_values[0], "www.somehost.com");
    EXPECT_STREQ(request->header_names[1], "Lang");
    EXPECT_STREQ(request->header_values[1], "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->host, "");
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

TEST(HTTP, invalid_request_non_spaced_headers) {
    char request_str[2048] =
        "GET  /url/myurl HTTP/1.1\r\n"
        "Host:www.somehost.com\r\n"
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
        "\r\n";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->host, ""); 
    EXPECT_STREQ(request->header_names[0], "Host");
    EXPECT_STREQ(request->header_names[1], "Lang");
    EXPECT_STREQ(request->header_values[0], "www.somehost.com");
    EXPECT_STREQ(request->header_values[1], "eng");
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

TEST(HTTP, invalid_request_no_host) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
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

TEST(HTTP, invalid_request_no_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_newline_after_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
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

TEST(HTTP, invalid_request_no_space_after_colon_in_header) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host:www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_no_crlf_after_header) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng"
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

TEST(HTTP, invalid_request_no_ending_null_character) {
    char request_str[2048] =
        "GET /somedir/page HTTP/1.1\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}