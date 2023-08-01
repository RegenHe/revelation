#include <hv/hv.h>
#include <hv/HttpServer.h>

#include "sqlOperator.h"

class MapHttpServer
{
public:
    MapHttpServer(int port, std::string host);

    void registerMsg();

    int query(HttpRequest* req, HttpResponse* resp);
    int queryAll(HttpRequest* req, HttpResponse* resp);
    int insert(HttpRequest* req, HttpResponse* resp);
    int remove(HttpRequest* req, HttpResponse* resp);
    int modify(HttpRequest* req, HttpResponse* resp);

    void start();
    void stop();

private:
    int m_port;
    hv::HttpService m_router;
    http_server_t m_server;

    SqliteOperator m_operator;

private:
    static int response_status(HttpResponse* resp, int code = 200, const char* message = NULL) {
        if (message == NULL) message = http_status_str((enum http_status)code);
        resp->Set("code", code);
        resp->Set("message", message);
        return code;
    }
    static int response_status(const HttpResponseWriterPtr& writer, int code = 200, const char* message = NULL) {
        response_status(writer->response.get(), code, message);
        writer->End();
        return code;
    }
    static int response_status(const HttpContextPtr& ctx, int code = 200, const char* message = NULL) {
        response_status(ctx->response.get(), code, message);
        ctx->send();
        return code;
    }
};