import requests
import json

provinceNameMap = {
    "heilongjiang": "黑龙江",
    "jilin": "吉林",
    "liaoning": "辽宁",
    "hebei": "河北",
    "beijing": "北京",
    "neimenggu": "内蒙古",
    "tianjin": "天津",
    "henan": "河南",
    "shandong": "山东",
    "shanxi": "山西",
    "jiangsu": "江苏",
    "anhui": "安徽",
    "hubei": "湖北",
    "zhejiang": "浙江",
    "hunan": "湖南",
    "jiangxi": "江西",
    "fujian": "福建",
    "shaanxi": "陕西",
    "ningxia": "宁夏",
    "gansu": "甘肃",
    "chongqing": "重庆",
    "sichuan": "四川",
    "guizhou": "贵州",
    "yunnan": "云南",
    "guangxi": "广西",
    "guangdong": "广东",
    "taiwan": "台湾",
    "hainan": "海南",
    "qinghai": "青海",
    "xinjiang": "新疆",
    "xizang": "西藏",
    "shanghai": "上海",
    "xianggang": "香港",
    "aomen": "澳门",
    "nanhaizhudao": "南海诸岛",
}

class Controller:
    def __init__(self, ip="0.0.0.0", port=80) -> None:
        self.ip = ip
        self.port = port

    def start(self):
        while True:
            type = input("type(i=insert, q=queryAll, r=remove, m=modify): ")
            if type == "i":
                provinceId = input("provinceId: ")
                self.insert(provinceId, provinceNameMap[provinceId], input("cityeName: "), input("name: "), input("describe: "))
            elif type == "q":
                self.queryAll()
            elif type == "r":
                self.remove(input("id: "))
            elif type == "m":
                id = input("id: ")
                provinceId = input("provinceId: ")
                self.modify(id, provinceId, provinceNameMap[provinceId], input("cityeName: "), input("name: "), input("describe: "))


    def insert(self, provinceId, provinceName, cityeName, name, describe):
        headers = {"Content-Type": "application/json;charset=utf8"}
        url = "http://" + self.ip + ":" + str(self.port) + "/insert"
        data = {
            "type":"insertMap",
            "provinceId": provinceId,
            "provinceName": provinceName,
            "cityeName": cityeName,
            "name": name,
            "describe": describe
        }
        res = requests.post(url=url, headers=headers, data=json.dumps(data)).text
        print(res)

    def queryAll(self):
        headers = {"Content-Type": "application/json;charset=utf8"}
        url = "http://" + self.ip + ":" + str(self.port) + "/queryAll"
        data = {
            "type":"queryAllMap",
        }
        res = requests.post(url=url, headers=headers, data=json.dumps(data)).text
        print(res)

    def remove(self, id):
        headers = {"Content-Type": "application/json;charset=utf8"}
        url = "http://" + self.ip + ":" + str(self.port) + "/remove"
        data = {
            "type":"removeMap",
            "id": id
        }
        res = requests.post(url=url, headers=headers, data=json.dumps(data)).text
        print(res)

    def modify(self, id, provinceId, provinceName, cityeName, name, describe):
        headers = {"Content-Type": "application/json;charset=utf8"}
        url = "http://" + self.ip + ":" + str(self.port) + "/modify"
        data = {
            "type":"modifyMap",
            "id": id,
            "provinceId": provinceId,
            "provinceName": provinceName,
            "cityeName": cityeName,
            "name": name,
            "describe": describe
        }
        res = requests.post(url=url, headers=headers, data=json.dumps(data)).text
        print(res)


if __name__ == "__main__":
    controller = Controller("127.0.0.1", 80)

    controller.start()
