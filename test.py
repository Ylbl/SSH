import json


class SimpleConfig:
    """极简JSON配置读取器"""

    def __init__(self, filepath: str):
        self._data = {}
        self.filepath = filepath
        self.load()

    def load(self):
        """加载/重载配置文件"""
        try:
            with open(self.filepath, 'r', encoding='utf-8') as f:
                self._data = json.load(f)
        except FileNotFoundError:
            raise Exception(f"配置文件不存在: {self.filepath}")
        except json.JSONDecodeError as e:
            raise Exception(f"JSON解析失败: {str(e)}")

    def get(self, key: str, default=None):
        """获取配置值"""
        return self._data.get(key, default)

    def __getattr__(self, name: str):
        """通过点符号访问配置"""
        if name in self._data:
            return self._data[name]
        raise AttributeError(f"配置项不存在: {name}")

c=SimpleConfig("C:\\Users\\Public\\Documents\\SSH\\img_js\\1742674693.json")
if __name__=='__main__':
    print(c.get("date"))