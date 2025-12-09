#靶机后台
from socket import * #网络相关模块
#套接字准备
main = socket()
#绑定号码
main.bind(("0.0.0.0",8888))
#IP地址 0.0.0.0：默认本机IP
#PORT 端口号 [1024-65535]
#开始监听
main.listen()
#转接给分套接字
s , addr = main.accept()
print(addr)#看一看地址