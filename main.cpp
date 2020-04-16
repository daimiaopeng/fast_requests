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


void requests_get(vector <string> urls, Header header, vector <cpr::Response> &responseList) {
    vector <cpr::Response> res;
    for (const auto &url:urls) {
        auto r = Get(Url{url}, header, VerifySsl() = false);
        res.push_back(move(r));
    }
    lock_guard <mutex> lock(_mutex);
    for (auto &i : res) {
        responseList.push_back(move(i));
    }
}

vector<Response> get(vector<string> urls,py::dict head_dict,int nthread = 5) {
    cpr::Header header;
    vector <cpr::Response> responseList;
    for (auto item : head_dict)
    {
        header.insert({ string(py::str(item.first)) ,string(py::str(item.second)) });
    }
	
       
    if (urls.empty())
        return responseList;
    if (urls.size() <= nthread) {
        nthread = urls.size();
    }

    // 分配任务数据
    vector<vector<string>> ThreadUrls(nthread);
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
    vector<thread> threadPoll;
    for (int i = 0; i < nthread; i++) {
        thread t(requests_get, ThreadUrls[i], header, ref(responseList));
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
    m.def("get", ::get);
    py::class_<cpr::Response>(m, "response")
        .def(py::init<>())
        .def_readwrite("status_code", &Response::status_code)
        .def_readwrite("text", &Response::text)
        .def_readwrite("header", &Response::header)
        .def_readwrite("Url", &Response::url)
        .def_readwrite("elapsed", &Response::elapsed)
        .def_readwrite("cookies", &Response::cookies)
        .def_readwrite("error", &Response::error);
}
