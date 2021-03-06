[English](#English)

## 介绍

这可能是最快的http请求库，暂支持get方法

## 要求

windows平台和python3.7.2

## 使用

### pip

`pip install requests-cpp`

### 手动导入项目

下载`fast_requetst_cpp.pyd`、`fast_requests.py`、`libcurl.dll`、`zlibd1.dll`四个文件，在项目中导入`fast_requests.py`

### 部分问题

如果text为空的话请设置verifySsl=False

## api

```python
#timeOut 单位为毫秒
get(urls, headers={}, nThread=5, isDebug=False, timeOut=3000, verifySsl=True)
    
sessionGet(urls, headers={}, nThread=5, isDebug=False, timeOut=3000, verifySsl=True)
    
#sessionGet和get的区别：sessionGet为每个线程持有一个session对象相当于requests的session，建议使用sessionGet速度更快
urls 请求的网址列表
headers 请求头
nThread 线程数（看自己设备配置，一般设20就差不多了）
isDebug 开启后会打印每个线程每个请求信息
timeOut 超时
verifySsl ssl验证
返回 Response 对象列表

Response 对象

Response.text 正文text文本
Response.status_code 状态码
Response.header 
Response.content() 二进制数据 
Response.Url url 
Response.elapsed 
Response.cookies 
Response.error 暂且用不了
```

示例代码：

```python
import fast_requests
urls = []
headers = {
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36"
}
for i in range(1, 200):
    urls.append("https://baidu.com")
for i in fast_requests.get(urls, headers, 20):
    print(i.text)
    
for i in fast_requests.sessionGet(urls, headers, 20):
    print(i.text)
```

## 原理

c++ : cpr  
python : pybind11

------

# English

## Introduction

This may be the fastest http request library, temporarily support get method

## Claim

windows platform and python 3.7.2

## Use

### pip

`pip install requests-cpp`

### Import project manually

Download four files `fast_requetst_cpp.pyd`, `fast_requests.py`, `libcurl.dll`, `zlibd1.dll`, and import `fast_requests.py` in the project

### Some questions

If text is empty, please set verifySsl=False

## api

```python
#timeOut in milliseconds
get(urls, headers={}, nThread=5, isDebug=False, timeOut=3000, verifySsl=True)
    
sessionGet(urls, headers={}, nThread=5, isDebug=False, timeOut=3000, verifySsl=True)
    
#sessionGet and get difference: sessionGet holds a session object for each thread equivalent to requests session, it is recommended to use sessionGet faster
urls list of requested URLs
headers request headers
nThread number of threads (see your own device configuration, generally set to 20 is almost the same)
After isDebug is turned on, it will print each thread and each request information
timeOut timeout
verifySsl ssl verification
Return a list of Response objects

Response object

Response.text body text text
Response.status_code status code
Response.header
Response.content() binary data
Response.Url url
Response.elapsed
Response.cookies
Response.error is temporarily unavailable
```

Sample code:

```python
import fast_requests
urls = []
headers = {
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 Safari/537.36"
}
for i in range(1, 200):
    urls.append("https://baidu.com")
for i in fast_requests.get(urls, headers, 20):
    print(i.text)
    
for i in fast_requests.sessionGet(urls, headers, 20):
    print(i.text)
```

## Principle

c++: cpr
python: pybind11
