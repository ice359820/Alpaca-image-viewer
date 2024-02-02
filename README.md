# Alpaca-image-viewer

我的Qt試做品

## Finished feature:
* 顯示圖片和動圖
* 套用雙線性過濾

## Unfinished:
* help->shortcut, about
* 視窗大小限制與調整
* 接受拖放
* 方向鍵切換工作目錄內的圖片
* 開啟檔案dialog中，更完整的mimetype過濾

## Build
### 有Qt帳號者
* 開啟Qt online installer 或 Qt maintance tool
* 安裝Qt6->Desktop gcc 64-bit、Sources、Additional Libraries
* 在IDE直接編譯或在專案資料夾中執行以下命令
```
cmake -DCMAKE_PREFIX_PATH=你的Qt安裝目錄/版本/gcc_64 -S $PWD -B $PWD/build
cd build
make
```
