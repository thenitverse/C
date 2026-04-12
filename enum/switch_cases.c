
#include <stdio.h>
typedef enum{
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_NOT_FOUND = 404,
    HTTP_TEAPOT = 418,
    HTTP_INTERNAL_SERVER_ERROR = 500
} http_error_code_t;

char *http_to_str(http_error_code_t code){
    switch (code){
    case HTTP_BAD_REQUEST:
       return "400 bad request";
        break;
    case HTTP_UNAUTHORIZED:
    return "401 unauthorized";
    break;
    case HTTP_NOT_FOUND:
    return "404 not found";
    break;
    case HTTP_TEAPOT:
    return "418 AM i a teapot!";
    break;
    case HTTP_INTERNAL_SERVER_ERROR:
    return "500 internal server error";
    break;
    default:
    return "unknown HTTP status code";


    }
}
#include <stdio.h>

int main() {
    printf("%s\n", http_to_str(HTTP_BAD_REQUEST));
    printf("%s\n", http_to_str(HTTP_UNAUTHORIZED));
    printf("%s\n", http_to_str(HTTP_NOT_FOUND));
    printf("%s\n", http_to_str(HTTP_TEAPOT));
    printf("%s\n", http_to_str(HTTP_INTERNAL_SERVER_ERROR));
    printf("%s\n", http_to_str((http_error_code_t)999));
    return 0;
}