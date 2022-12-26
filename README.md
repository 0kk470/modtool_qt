# modtool_qt

这是一个用于将《群侠传启动》相关mod上传至Steam创意工坊的工具。

在QtCreator打开项目后使用qmake直接编译即可。

### Build for Windows

* 该工具使用了```QWebEngineView```， ```QT5```的```MinGW```编译依赖库不支持```QWebEngineView``` ，请使用```MSVC```进行编译。

* 构建生成exe后，cmd命令行调用下列指令完成部署。
```bat
qwindeploy [exe生成路径]
```

[Release Package下载](https://github.com/0kk470/modtool_qt/releases/tag/modtool)

