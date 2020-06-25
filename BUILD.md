# 調停FWのビルド

## 1. 概要

調停FWのビルド手順について述べる。

## 2. 調停FWのディレクトリ構成とライブラリ

調停FWのディレクトリ構成と、ビルドによって生成されるライブラリファイルを以下に示す。

|パス|内容|
|:---|:---|
| rba/include/ | ヘッダファイルディレクトリ  |
| rba/src/ | ソースファイルディレクトリ(*1) |
| rba/lib/ | ライブラリディレクトリ |
| rba/lib/librba.a | 調停FW本体の静的ライブラリ<br>（Linux環境で生成される） |
| rba/lib/librba.so | 調停FW本体の共有ライブラリ<br>（Linux環境で生成される） |
| rba/lib/rba.dll | 調停FW本体のDLLファイル<br>（Windows環境で生成される） |
| rba/unittest/ | 単体テスト環境ディレクトリ |
| rba/doc/ | ドキュメントディレクトリ |
| rba/CMakeLists.txt | CMake設定ファイル |
| rba/script/ | スクリプトファイルディレクトリ |
| rba/script/make_dll_x64.bat | DLL生成バッチファイル |

(*1) ビルド時は、``rba/src/``下のサブディレクトリを含む拡張子が``.cpp``のすべてのファイルをソースファイルとして扱う。サブディレクトリの階層は、ファイルシステムの制約内で制限はない。

## 3. ビルド手順

### 3-1. Linux環境

Linux環境におけるビルド手順を示す。

#### 3-1-1. 開発環境

以下の環境で動作確認を行なっている。

* OS
  - Ubuntu 16.04
  - Ubuntu 18.04
  - Windows Subsystem for Linux (Ubuntu 16.04.5 LTS)
* 開発環境
  - g++ 5.4.0
  - make 4.1
  - CMake 3.5.1

#### 3-1-2. 調停FWライブラリのビルド

調停FWライブラリのビルド手順を以下に示す。

```
$ cd rba
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ls -F ../lib
librba.a    librba.so
```
ビルドに成功すると、ライブラリファイル **librba.a**, **librba.so** が生成される。

### 3-2. Windows環境

Windows環境におけるビルド手順を示す。

#### 3-2-1. 開発環境

以下の環境で動作確認を行なっている。

* OS
  - Microsoft Windows 7 Professional 64bit版
  - Microsoft Windows 10 Pro 64bit版
* 開発環境
  - Visual Studio Professional 2017
    - C++によるデスクトップ開発
      - 「CMakeのVisual C++ツール」を含む

#### 3-2-2. 調停FWライブラリのビルド

「開発者コマンドプロンプト for VS 2017」を起動し、DLL生成バッチファイルを実行する。

```
> cd rba
> script¥make_dll_x64.bat
> dir lib /w
[.]       [..]      rba.dll   rba.exp   rba.lib
```

ビルドに成功すると、DLLライブラリ ```rba.dll```が生成される。


以上
