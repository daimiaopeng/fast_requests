# fast_requests

## 介绍

这可能是最快的http请求库，暂支持get方法

## 要求
windows平台和python3.7.2

## 使用

下载`fast_requetst_cpp.pyd`、`fast_requests.py`、`libcurl-d.dll`、`zlibd1.dll`四个文件，在项目中导入`fast_requests.py`

```
api:

def get(urls, headers, nTjread=5):
    return list(fast_requetst_cpp.get(urls, headers, nTjread))
    
urls 请求的网址列表
headers 请求头
nTjread 线程数（看自己设备配置，一般设20就差不多了）
返回 Response 对象列表

Response 对象

Response.text 正文text文本
Response.status_code 状态码
Response.header 
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
for i in fast_requests.get(urls, headers,10):
    print(i.text)
```
## 原理

