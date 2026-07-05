#include "webserver.h"

#include "esp_http_server.h"
#include "sensor_data.h"

static esp_err_t root_handler(httpd_req_t *req)
{
    char html[512];

    sprintf(html,
        "<html>"
        "<head>"
        "<meta http-equiv='refresh' content='2'>"
        "</head>"
        "<body>"
        "<h1>Haider's Room Temperature/Humidity</h1>"
        "<h2>Temperature : %.1f C</h2>"
        "<h2>Humidity : %.1f %%</h2>"
        "</body>"
        "</html>",
        g_temp,
        g_humid);

    httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN);

    return ESP_OK;
}

void start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_handle_t server = NULL;

    if(httpd_start(&server,&config)==ESP_OK)
    {
        httpd_uri_t uri = {

            .uri="/",

            .method=HTTP_GET,

            .handler=root_handler,

            .user_ctx=NULL

        };

        httpd_register_uri_handler(server,&uri);
    }
}
