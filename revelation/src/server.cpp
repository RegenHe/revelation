#include "server.h"

#include <hv/hv.h>
#include <hv/HttpServer.h>

MapHttpServer::MapHttpServer(int port, std::string host)
{
	std::cout << "server: " << host << ':' << port << std::endl;

	std::string path("./map.db");
	m_operator.openDB(path);
	m_operator.createTab("create table t_user(id integer primary key autoincrement, provinceId integer, provinceName string,cityeName string, name string, describe string); ");

	registerMsg();

	m_server.service = &m_router;
	m_server.port = port;
	strcpy(m_server.host, host.c_str());
}

void MapHttpServer::registerMsg()
{
	m_router.Static("/", "./html");

	m_router.GET("/html/index.html", [](HttpRequest* req, HttpResponse* resp) {
		return resp->File("html/index.html");
	});


	m_router.POST("/query", [this](HttpRequest* req, HttpResponse* resp) {
		return query(req, resp);
	});

	m_router.POST("/queryAll", [this](HttpRequest* req, HttpResponse* resp) {
		return queryAll(req, resp);
	});

	m_router.POST("/insert", [this](HttpRequest* req, HttpResponse* resp) {
		return insert(req, resp);
	});

	m_router.POST("/remove", [this](HttpRequest* req, HttpResponse* resp) {
		return remove(req, resp);
	});

	m_router.POST("/modify", [this](HttpRequest* req, HttpResponse* resp) {
		return modify(req, resp);
	});
}

int MapHttpServer::query(HttpRequest* req, HttpResponse* resp)
{
	std::string str = req->Body();

	nlohmann::json reqJson;
	try
	{
		reqJson = nlohmann::json::parse(str);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}
	resp->content_type = APPLICATION_JSON;

	std::cout << reqJson << std::endl;

	if (reqJson["type"] == "test")
	{
		resp->json["data"] = "test";

		return 200;
	}

	if (reqJson["type"] != "queryMap")
	{
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}

	std::string provinceId = reqJson["provinceId"];
	std::string sql = "select * from t_user where provinceId=\"" + provinceId + "\"; ";
	std::vector<sqlUser> all = m_operator.queryAll(sql);

	nlohmann::json data;
	for (const auto& p : all)
	{
		data.push_back(nlohmann::json{
			{"name", p.name},
			{"cityName", p.cityeName},
			{"provinceName", p.provinceName},
			{"describe", p.describe}
			});
	}

	resp->json["data"] = data;

	return 200;
}

int MapHttpServer::queryAll(HttpRequest* req, HttpResponse* resp)
{
	std::string str = req->Body();

	nlohmann::json reqJson;
	try
	{
		reqJson = nlohmann::json::parse(str);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}
	resp->content_type = APPLICATION_JSON;

	std::cout << reqJson << std::endl;

	if (reqJson["type"] != "queryAllMap")
	{
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}

	std::string sql = "select * from t_user; ";
	std::vector<sqlUser> all = m_operator.queryAll(sql);

	nlohmann::json data;
	for (const auto& p : all)
	{
		data.push_back(nlohmann::json{
			{"id", p.id},
			{"name", p.name},
			{"cityName", p.cityeName},
			{"provinceName", p.provinceName},
			{"describe", p.describe}
			});
	}

	resp->json["data"] = data;

	return 200;
}

int MapHttpServer::insert(HttpRequest* req, HttpResponse* resp)
{
	std::string str = req->Body();

	nlohmann::json reqJson;
	try
	{
		reqJson = nlohmann::json::parse(str);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}
	resp->content_type = APPLICATION_JSON;

	std::cout << reqJson << std::endl;

	if (reqJson["type"] != "insertMap")
	{
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}

	std::string provinceId = reqJson["provinceId"];
	std::string provinceName = reqJson["provinceName"];
	std::string cityeName = reqJson["cityeName"];
	std::string name = reqJson["name"];
	std::string describe = reqJson["describe"];

	std::string sql = "insert into t_user (provinceId,provinceName,cityeName,name,describe) values (\"" + provinceId + "\",\"" + 
		provinceName + "\",\"" + cityeName + "\",\"" + name + "\",\"" + describe + "\"); ";

	resp->json["code"] = m_operator.Insert(sql);

	return 200;
}

int MapHttpServer::remove(HttpRequest* req, HttpResponse* resp)
{
	std::string str = req->Body();

	nlohmann::json reqJson;
	try
	{
		reqJson = nlohmann::json::parse(str);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}
	resp->content_type = APPLICATION_JSON;

	std::cout << reqJson << std::endl;

	if (reqJson["type"] != "removeMap")
	{
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}

	int id = reqJson["id"];

	std::string sql = "delete from t_user where id=" + std::to_string(id) + "; ";
	resp->json["code"] = m_operator.Update(sql);

	return 200;
}

int MapHttpServer::modify(HttpRequest* req, HttpResponse* resp)
{
	std::string str = req->Body();

	nlohmann::json reqJson;
	try
	{
		reqJson = nlohmann::json::parse(str);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}
	resp->content_type = APPLICATION_JSON;

	std::cout << reqJson << std::endl;

	if (reqJson["type"] != "modifyMap")
	{
		return response_status(resp, HTTP_STATUS_BAD_REQUEST);
	}

	int modifyId = reqJson["id"];
	std::string provinceId = reqJson["provinceId"];
	std::string provinceName = reqJson["provinceName"];
	std::string cityeName = reqJson["cityeName"];
	std::string name = reqJson["name"];
	std::string describe = reqJson["describe"];

	std::string sql = "update t_user set provinceId=\"" + provinceId + "\", provinceName=\"" + provinceName + 
		"\", cityeName=\"" + cityeName + "\", name=\"" + name + "\", describe=\"" + describe + "\" where id=" + std::to_string(modifyId) + "; ";

	resp->json["code"] = m_operator.Update(sql);

	return 200;
}

void MapHttpServer::start()
{
	http_server_run(&m_server, 1);
}

void MapHttpServer::stop()
{

}
