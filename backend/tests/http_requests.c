
#include <gtest/gtest.h>

#include "http.h"

TEST(HTTP, valid_request_with_no_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/3.3\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 0);
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->url, "/somedir/page");
    EXPECT_STREQ(request->version, "HTTP/3.3");
    EXPECT_STREQ(request->payload, "my really beutiful payload");
    http_request_destroy(request);
}

TEST(HTTP, valid_request_with_two_headers) {
    char request_str[2048] =
        "GET /somedir/page HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_NE(request, (http_request_t*)NULL);
    EXPECT_EQ(request->headers_num, 2);
    EXPECT_STREQ(request->header_names[0], "Host");
    EXPECT_STREQ(request->header_names[1], "Lang");
    EXPECT_STREQ(request->header_values[0], "www.somehost.com");
    EXPECT_STREQ(request->header_values[1], "eng");
    EXPECT_STREQ(request->method, "GET");
    EXPECT_STREQ(request->url, "/somedir/page");
    EXPECT_STREQ(request->version, "HTTP/3.3");
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
        "GET HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_url2) {
    char request_str[2048] =
        "GET  HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_url3) {
    char request_str[2048] =
        "GET   HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}


TEST(HTTP, invalid_request_missing_method1) {
    char request_str[2048] =
        "/url/myurl HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_missing_method2) {
    char request_str[2048] =
        " /url/myurl HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_missing_method3) {
    char request_str[2048] =
        "  /url/myurl HTTP/3.3\r\n"
        "Host: www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}

TEST(HTTP, invalid_request_non_spaced_headers) {
    char request_str[2048] =
        "GET  /url/myurl HTTP/3.3\r\n"
        "Host:www.somehost.com\r\n"
        "Lang: eng\r\n"
        "\r\n"
        "my really beutiful payload\0";

    http_request_t* request = http_request_decode(request_str);
    ASSERT_EQ(request, (http_request_t*)NULL);
}