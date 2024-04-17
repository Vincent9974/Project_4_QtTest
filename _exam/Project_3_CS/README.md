有client 和 server 两个窗口



server负责显示读到的数据(json)



client 窗口 config有save 和 load, 记得使用前选中Admin中的对应config



save 将账户密码封装为json然后保存到运行目录(默认为Debug目录下) 的config.json中



load从服务器读取config然后解包, 并显示到client窗口中.

