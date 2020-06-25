# 調停ロジック単体テスト環境のビルド

## 1. 概要

調停ロジックの単体テスト環境と、単体テストプログラムのビルド手順について述べる。

### 1-1. 調停ロジックのディレクトリ構成とライブラリ

調停ロジックのディレクトリ構成と、単体テスト対象である調停ロジック本体のライブラリファイルを以下に示す。

|パス|内容|
|:---|:---|
| rba/include/ | ヘッダファイルディレクトリ  |
| rba/lib/ | ライブラリディレクトリ |
| rba/lib/librba.a | 調停ロジック本体の静的ライブラリ<br>単体テスト環境では使用しない。 |
| rba/lib/__librba.so__ | 調停ロジック本体の共有ライブラリ<br>Linux環境で使用する。 |
| rba/lib/__rba.dll__ | 調停ロジック本体のDLLファイル<br>Windows環境で使用する。 |
| rba/__unittest__/ | 単体テスト環境ディレクトリ |

### 1-2. 単体テスト環境のファイル、ディレクトリ構成

単体テスト環境のファイル構成を以下に示す。

|パス|内容|
|:---|:---|
| __rba/unittest/logic_test/__ | __制約式の単体テスト__ |
| rba/unittest/logic_test/<_testname_>.cpp | 単体テストプログラム本体  |
| rba/unittest/logic_test/<_testname_>.hpp | 単体テストプログラムヘッダファイル  |
| rba/unittest/logic_test/<_testname_>.json | 単体テストプログラムで使用するJSONファイル  |
| __rba/unittest/api_test/__ | __API単体テスト__<br>APIの機能を対象とした単体テスト |
| rba/unittest/api_test/<_testname_>.cpp | 単体テストプログラム本体  |
| rba/unittest/api_test/<_testname_>.hpp | 単体テストプログラムヘッダファイル  |
| rba/unittest/api_test/<_testname_>.json | 単体テストプログラムで使用するJSONファイル  |
| __rba/unittest/script/__ | __スクリプト__ |
| rba/unittest/script/__install_gt.sh__ | Goole Test自動インストールスクリプト |
| rba/unittest/script/__gtbuild.bat__ | Windows環境向けGoogle Testビルドバッチファイル |
| rba/unittest/script/__make_ut.bat__ | Windows環境向け単体テスト生成バッチファイル |
| rba/unittest/CMakeLists.txt | CMake設定ファイル |
| rba/unittest/__unittest_rba__ | Linux版単体テスト実行ファイル<br>単体テストビルドで生成される。 |
| rba/unittest/unittest_rba.exe | Windows版単体テスト実行ファイル<br>単体テストビルドで生成される。 |
| rba/unittest/__exec_unittest.bat__  | Windows版単体テスト実行バッチファイル |

## 2. 単体テストプログラムのビルドと実行

### 2-1. Linux環境

Linux環境における、単体テストのビルドと実行方法を示す。

#### 2-1-1. 開発環境

以下の環境で動作確認を行なっている。

* OS
  - Ubuntu 16.04
  - Ubuntu 18.04
  - Windows Subsystem for Linux (Ubuntu 16.04.5 LTS)
* 開発環境
  - g++ 5.4.0
  - make 4.1
  - CMake 3.5.1
  - Git 2.7.4（Google Testのダウンロードで使用）

#### 2-1-2. Google Testのインストール

Google Testのインストール手順を以下に示す。

```
$ cd rba/unittest
$ sh script/install_gt.sh
```
もしくは
```
$ cd rba/unittest
$ git clone -b release-1.8.1 https://github.com/google/googletest.git
$ cd googletest/googletest
$ cmake .
$ make
```

#### 2-1-3. 単体テストプログラムのビルド

単体テストプログラムのビルド手順を以下に示す。

```
$ cd rba/unittest
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ls -F ../unittest_rba
unittest_rba*
```
ビルドに成功すると、実行ファイル **unittest_rba** が生成される。

#### 2-1-4. 単体テストプログラムの実行

単体テストプログラムの実行手順を以下に示す。

```
$ cd rba/unittest
$ ./unittest_rba
```

### 2-2. Windows

Windows環境における、単体テストのビルドと実行方法を示す。

#### 2-2-1. 開発環境

以下の環境で動作確認を行なっている。

* OS
  - Microsoft Windows 7 Professional 64bit版
  - Microsoft Windows 10 Pro 64bit版
* 開発環境
  - Visual Studio Professional 2017
    - C++によるデスクトップ開発
      - 「CMakeのVisual C++ツール」を含む
  - Git 2.18.0（Google Testのダウンロードで使用）

#### 2-2-2. Google Testのインストール

「開発者コマンドプロンプト」を起動し、
調停ロジックの単体テスト環境のディレクトリに移動し、以下のようにバッチファイルを実行する

```
> cd rba¥unittest
> script¥install_gt.bat
```

#### 2-2-3. 単体テストプログラムのビルド

「開発者コマンドプロンプト」を起動し、単体テスト生成バッチファイルを実行する。

```
> cd rba¥unittest
> script¥make_ut.bat
> dir *.exe
unittest_rba.exe
```

ビルドに成功すると、実行ファイル ```unittest_rba.exe```が生成される。

#### 2-1-4. 単体テストプログラムの実行

コマンドプロンプトを起動し、調停ロジック単体テスト環境のディレクトリに移動して、実行用バッチファイルを実行する。
```
> run_ut.bat
```

``run_ut.bat``は、パスに調停ロジックライブラリのディレクトリを加え、``unittest_rba.exe``を呼び出している。``run_ut.bat``の内容は以下の通り。

```
ECHO OFF
set PATH=..¥lib;%PATH%
unittest_rba.exe
```

別途用意した調停ロジックライブラリで単体テストを実行する場合は、以下のように``unittest_rba.exe``とテスト対象の調停ロジックライブラリ``rba.dll``を同じディレクトリにセットし、単体テストプログラムを実行する。

```
$ dir /w
rba.dll   unittest_rba.exe
$ unittest_rba.exe
```

以上
