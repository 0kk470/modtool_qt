# modtool_qt
modtool for jynew

使用QtCreator打开项目直接编译即可

### Build for Windows

* 该工具使用了```QWebEngineView```， ```QT5```的```MinGW```编译依赖库不支持```QWebEngineView``` ，请使用```MSVC```进行编译。

* 构建生成exe后，cmd命令行调用下列指令完成部署。
```bat
qwindeploy [exe生成路径]
```


