#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "/home/kianaz/Documents/ApPr/httplib.h"

// HTTP
httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");

// HTTPS
httplib::Client cli("https://cpp-httplib-server.yhirose.repl.co");

auto res = cli.Get("/hi");
res->status;
res->body;
