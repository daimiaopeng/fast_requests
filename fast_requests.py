import fast_requetst_cpp
import json


# class Fast_requests:
#     def __init__(self):
#         pass

def get(urls, header, nTjread=5):
    return list(fast_requetst_cpp.get(urls, header, nTjread))

# class Fast_requests:
#     def __init__(self):
#         pass
# get(['https://dyn.ithome.com/api/user/gui?suid=c84107a3ca24e887', 'https://dyn.ithome.com/api/user/gui?suid=57bd9f36ef07d283', 'https://dyn.ithome.com/api/user/gui?suid=93c565edbbd750d0'])
