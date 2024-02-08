# Alpaca-image-viewer

我的Qt試做品

## dependency
Linux版本請先安裝依賴套件
```
libqt6widgets6 libqt6gui6 libqt6core6 libqt6dbus6 libicu70
```
## 下載
從release下載pre-built binaries
* Windows下載7z
* Linux下載tar.gz
## 使用
* 直接點擊AlpacaImageViewer然後開啟檔案
* 或以command line使用
```
./AlpacaImageViewer 圖片檔名
```
* 使用滑鼠滾輪放大縮小
* 壓著滑鼠左鍵移動圖片
## Finished feature:
* 套用雙線性過濾
## Unfinished:
* 說明, about
* 視窗大小限制與調整
* 接受拖放
* 方向鍵切換工作目錄內的圖片
* 開啟檔案dialog中，更完整的mimetype過濾
## Build
* 準備一個Qt帳號，下載Qt online installer
* 開啟Qt online installer 或 Qt maintance tool
### Linux
* 下載選擇Qt6->Desktop gcc 64-bit、Sources、Additional Libraries
* 在Qt Creaotr直接編譯或在專案資料夾中開啟terminal執行以下命令
```
cmake -DCMAKE_PREFIX_PATH=你的Qt安裝目錄/版本/gcc_64 -S $PWD -B $PWD/build
cd build
cmake --build $PWD --target all
```
* 找出AlpacaImageViewer開啟它
