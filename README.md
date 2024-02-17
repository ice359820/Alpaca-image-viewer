# Alpaca-image-viewer

以Qt寫的圖片檢視器
* 使用滑鼠滾輪放大縮小
* 壓著滑鼠左鍵移動圖片
* 按壓滑鼠中鍵重設縮放
* 快捷鍵```f```全螢幕
* ```Ctrl+o```選擇檔案
* ```Ctrl+w```關閉視窗
## dependency
Linux依賴套件：
```
libqt6widgets6 libqt6gui6 libqt6core6 libqt6dbus6 libicu70
```
## 下載
從release下載pre-built binaries
* Windows下載7z
* Linux下載tar.gz
## 使用
* 賦予檔案可執行權限
* 點擊AlpacaImageViewer。或以command line使用
```
./AlpacaImageViewer 圖片檔名
```
## Unfinished:
* 快捷鍵說明, about
* 接受拖放
* 方向鍵切換工作目錄內的圖片
* 開啟檔案dialog中，更完整的mimetype過濾
## Build
* 準備一個Qt帳號，下載Qt online installer
* 開啟Qt online installer 或 Qt maintance tool
### Linux
* 下載選擇Qt6->Desktop gcc 64-bit、Sources、Additional Libraries
* 在Qt Creaotr編譯。或在專案資料夾中開啟terminal執行以下命令
```
cmake -DCMAKE_PREFIX_PATH=你的Qt安裝目錄/版本/gcc_64 -S $PWD -B $PWD/build
cd build
cmake --build $PWD --target all
```
### Windows
* 下載選擇Qt6->MinGW 64、Sources、Additional Libraries
* 在Qt Creaotr編譯
* 找出編譯完成的AlpacaImageViewer.exe
* 在Qt安裝目錄\版本\mingw\bin中找出windeployqt6.exe
* 在AlpacaImageViewer.exe所在的目錄下開啟PowerShell輸入：
```
路徑到\windeployqt.exe AlpacaImageViewer.exe
```
