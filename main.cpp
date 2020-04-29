#include<pybind11/pybind11.h>
#include <string>
#include <thread>
#include <cpr/cpr.h>
#include <iostream>
#include <vector>
#include <list>
#include <pybind11/stl.h>

using namespace std;
using namespace cpr;
namespace py = pybind11;

mutex _mutex;

void _get(string type, vector <string> urls, bool isDebug, vector <cpr::Response> &responseList, Header headers, int timeOut,
     bool verifySsl) {
    vector <cpr::Response> res;
    auto threadId = this_thread::get_id();
    int n = 0;
    Session session;
    if (type == "session") {
        session.SetHeader(headers);
        session.SetVerifySsl(verifySsl);
        session.SetTimeout(timeOut);
    }
    for (const auto &url:urls) {
        Response r;
        if (type == "get") {
            r = Get(Url{url}, VerifySsl() = verifySsl, headers, Timeout{timeOut});
        } else if (type == "session") {
            session.SetUrl(url);
            r = session.Get();
        }
        if (isDebug) {
            cout << "DEBUG threadId = " << threadId << " status_code = " << r.status_code << " n = " << ++n << endl;
        }
        res.push_back(move(r));
    }
    lock_guard <mutex> lock(_mutex);
    for (auto &i : res) {
        responseList.push_back(move(i));
    }
}


vector <Response> run(string type, vector <string> urls, py::dict head_dict, int nthread = 5, bool isDebug = false, int timeOut = 3000,
    bool verifySsl = true) {
    cpr::Header headers;
    vector <cpr::Response> responseList;
    for (auto item : head_dict) {
        headers.insert({string(py::str(item.first)), string(py::str(item.second))});
    }


    if (urls.empty())
        return responseList;
    if (urls.size() <= nthread) {
        nthread = urls.size();
    }

    // 分配任务数据
    vector <vector<string>> ThreadUrls(nthread);
    while (!urls.empty()) {
        for (int i = 0; i < nthread; i++) {
            if (urls.empty()) {
                break;
            }
            ThreadUrls[i].push_back(urls.back());
            urls.pop_back();
        }
    }

    //创建线程池
    vector <thread> threadPoll;
    for (int i = 0; i < nthread; i++) {
        thread t(_get, type, ThreadUrls[i], isDebug, ref(responseList), headers, timeOut, verifySsl);
        threadPoll.push_back(move(t));
    }

    //运行线程
    for (int i = 0; i < nthread; i++) {
        threadPoll[i].join();
    }
    return responseList;
}


PYBIND11_MODULE(fast_requetst_cpp, m) {
    m.doc() = "pybind11 fast_requetst module";
    m.def("run", run);
    py::class_<cpr::Response> response(m, "response");
        response.def(py::init<>())
        .def_readwrite("status_code", &Response::status_code)
        .def_readwrite("text", &Response::text)
        .def_readwrite("header", &Response::header)
        .def_readwrite("Url", &Response::url)
        .def_readwrite("elapsed", &Response::elapsed)
        .def_readwrite("cookies", &Response::cookies)
        .def_readwrite("error", &Response::error)
        .def("content",
                [](const Response& re) {
                 return py::bytes(re.text);
                }
        );
}