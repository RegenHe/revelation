import requests
import json
 
headers = {"Content-Type": "application/json;charset=utf8"}
url = "http://127.0.0.1:8080/insert"
data = {
    "type":"insertMap",
    "provinceId": "jiangsu",
    "provinceName": "江苏",
    "cityeName": "南京",
    "name": "贺雨",
    "describe": "测试一下"
}
 

res = requests.post(url=url, headers=headers, data=json.dumps(data)).text

print(res)