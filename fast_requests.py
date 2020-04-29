import fast_requetst_cpp


# timeOut 单位为毫秒
def get(urls, headers={}, nThread=5, isDebug=False, timeOut=3000, verifySsl=True):
    return fast_requetst_cpp.run("get", urls, headers, nThread, isDebug, timeOut, verifySsl)


def sessionGet(urls, headers={}, nThread=5, isDebug=False, timeOut=3000, verifySsl=True):
    return fast_requetst_cpp.run("session", urls, headers, nThread, isDebug, timeOut, verifySsl)
