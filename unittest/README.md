# 調停ロジック単体テスト環境（内部向けドキュメント）

## 1. 概要

本ドキュメントは、調停ロジク単体テスト環境について述べる。

## 2. ディレクトリ構成

単体テスト環境のディレクトリ構成を示す。<br>
（「納品」が"○”のものは、外部提供の対象とする）

### 2-1. unittest/

単体テスト環境のファイル、ディレクトリ構成を以下に示す。

|パス|内容|納品|
|:---|:---|:--:|
| __CMakeLists.txt__ | 単体テスト環境のCMake設定ファイル | __○__ |
| __main.cpp__ | 単体テストメインプログラム | __○__ |
| __script/__ | スクリプト | __○__ |
| api_test_project/ |  API単体テストモデル | - |
| internal_test_project/ | 内部単体テストモデル | - |
| log/ | 単体テストの実行で出力されるログ | - |
| logic_test_project/ | 制約式の単体モデル | - |
| __logic_test/__ | 制約式の単体テスト | __○__ |
| __api_test/__ | API単体テスト | __○__ |
| internal_test/ | 内部単体テスト | - |
| config_test/ | 設定単体テスト | - |
| google_test/ | Google Testディレクトリ<br>`script/install_gt.shで`インストールされる。 | - |

それぞれディレクトリ下の構成は以下の通り。

### 2-2. unittesrt/script/

* 単体テスト環境で使用するスクリプトを提供する
* 内部向けには、src/以下のテストプログラ単体テストの実行で出力されるログム生成スクリプトなどで構成
* シェルスクリプトとPythonスクリプトで構成

|パス|内容|納品|
|:---|:---|:--:|
| __script/__ | スクリプト格納用ディレクトリ | __○__ |
| __script/install_gt.sh__ | Google Testインストーラ | __○__ |
| __script/gtbuild.bat__ | Windows環境向けGoogle Testビルドバッチファイル | __○__ |
| __script/make_ut.bat__ | Windows環境向け単体テスト生成バッチファイル | __○__ |
| script/create_ut_prog.py | tcファイルから単体テストプログラムを生成する。 | - |

### 2-3. unittest/nnn_test_project/rba.tool.simulator.junit.test

* ツールのリポジトリからJUnitの単体テスト環境のみを取り出したもの
* 制約式の評価の正当性を確認することを目的とする
* テスト項目ごとに、モデル、テストスクリプトが用意されている
* テストスクリプトは要求と調停結果の期待値で構成される
* JUnitの単体テスト環境から取り出した後、テストケースを変更したものはこのディレクトリの外へ移動させている

|パス|内容|納品|
|:---|:---|:--:|
| nnn_test_project/rba.tool.simulator.junit.test/ | テストモデル格納ディレクトリ | - |

#### rba.tool.simulator.junit.test/以下のディレクトリとファイル

|パス|内容|納品|
|:---|:---|:--:|
| <_org-testname_>/ | テストモデルディレクトリ | - |
| <_org-testname_>/_xxx_.txt | 単体テストスクリプト<br>（複数化） | - |
| <_org-testname_>/template-gen/RBAModel.json | JSONファイル | - |

### 2-4. unittest/nnn_test_project/

* <_nnn_>_test/に使用しているテストモデル

|パス|内容|納品|
|:---|:---|:--:|
| <_nnn_>_test_project/ | 追加テストモデル格納ディレクトリ | - |
| <_nnn_>_test_project/<<_nnn_>_test/のJSONファイル名>/ | 生成するJSONファイルごとに作成 | - |
| <_nnn_>_test_project/<<_nnn_>_test/のJSONファイル名>/_xxx_.txt | 単体テストスクリプト<br>_xxx_は任意の文字列。（複数化） | - |
| <_nnn_>_test_project/<<_nnn_>_test/のJSONファイル名>/model/all.rba | 単体テストで使用するモデル定義ファイル | - |
| <_nnn_>_test_project/<<_nnn_>_test/のJSONファイル名>/template-gen/RBAModel.json | JSONファイル | - |
| <_nnn_>_test_project/<<_nnn_>_test/のJSONファイル名>/test/rev_1/testcase/_xxx_.tc | 単体テストスクリプト<br>_xxx_は任意の文字列。 | - |

※ "_nnn_"は英数字

### 2-5. unittest/logic_test/

* テストモデルから生成されたプログラム一式が対象
  - テストモデルは``logic_test_project``が対象
* ``unittest_rba``あるいは``unittest_rba.exe``で実行される単体テスト

|パス|内容|納品|
|:---|:---|:--:|
| __logic_test/__ | 単体テストプログラムディレクトリ | __○__ |
| __logic_test/<_testname_>.cpp__ | 単体テストプログラム本体 | __○__ |
| __logic_test/<_testname_>.hpp__ | 単体テストプログラムヘッダファイル | __○__ |
| __logic_test/<_testname_>.json__ | <_testname_>で使用するJSONファイル<br>（任意） | __○__ |
| __logic_test/<_testname_>_xxx.json__ | <_testname_>で使用するJSONファイル<br>（任意、複数可） | __○__ |

### 2-6. unittest/api_test/

* API機能の単体テストプログラム一式を格納
  - rba/src/以下のヘッダファイルを参照する単体テストを除く
* テスト項目はチケット番号ごととする
  - <_name_>はテスト内容を示す、アルファベットと数字、アンダーバーで構成された文字列とする
  - 複数の種類の<_name_>を用意して、１つのチケットで複数の単体テストプログラムの提供も可とする
* ``unittest_rba``あるいは``unittest_rba.exe``で実行される単体テスト

|パス|内容|納品|
|:---|:---|:--:|
| __api_test/__ | 拡張単体テストプログラムディレクトリ | __○__ |
| __api_test/HA<_nnn_>_<_name_>.cpp__ | 単体テストプログラム本体<br> | __○__ |
| __api_test/HA<_nnn_>_<_name_>.hpp__ | 単体テストプログラムヘッダファイル | __○__ |
| __api_test/HA<_nnn_>_<_name_>.json__ | 使用するJSONファイル<br>（任意） | __○__ |
| __api_test/HA<_nnn_>_<_name_>_xxx.json__ | 使用するJSONファイル<br>（任意、複数可） | __○__ |

### 2-7. unittest/internal_test/

* ツール向け機能の単体テストプログラム一式を格納
  - rba/src/以下のヘッダファイルを参照する単体テストが対象
* テスト項目はチケット番号ごととする
  - <_name_>はテスト内容を示す、アルファベットと数字、アンダーバーで構成された文字列とする
  - 複数の種類の<_name_>を用意して、１つのチケットで複数の単体テストプログラムの提供も可とする
* ``unittest_rba``あるいは``unittest_rba.exe``で実行される単体テスト
  - ただし、このディレクトリは納品物には含まれないため、納品物版では実行されない

|パス|内容|納品|
|:---|:---|:--:|
| __internal_test/__ | 内部単体テストディレクトリ | __○__ |
| __internal_test/HA<_nnn_>_<_name_>.cpp__ | 単体テストプログラム本体<br> | __○__ |
| __internal_test/HA<_nnn_>_<_name_>.hpp__ | 単体テストプログラムヘッダファイル | __○__ |
| __internal_test/HA<_nnn_>_<_name_>.json__ | 使用するJSONファイル<br>（任意） | __○__ |
| __internal_test/HA<_nnn_>_<_name_>_xxx.json__ | 使用するJSONファイル<br>（任意、複数可） | __○__ |
| __internal_test/HA<_nnn_>_<_name_>.log__ | ログ出力の期待値<br>（任意） | __○__ |


### 2-8. unittest/config_test/

* コンパイルスイッチ等で定義される動作の単体テスト
* テスト項目はチケット番号ごととする
  - <_name_>はテスト内容を示す、アルファベットと数字、アンダーバーで構成された文字列とする
* 単体テストの実行プログラムは、それぞれのテスト項目ごとに生成される

|パス|内容|納品|
|:---|:---|:--:|
| config_test/ | 独立系単体テストプログラム | - |
| config_test/HA<_nnn_>_<_name_>/ | テストデータディレクトリ<br>チケットごとに作成<br>HA<nnn>はチケット番号、<_name_>はテストの内容を示す文字列とする | - |
| config_test/HA<_nnn_>_<_name_>/README.md | テストの説明ドキュメント | - |
| config_test/HA<_nnn_>_<_name_>/* | （その他のファイルは各単体テストごとに異なる） | - |

### 2-9. unittest/log/

* 単体テスト実行時に出力されるログファイルが格納される
* rba_tool用のログ出力を確認しているテストの数だけ生成される
* テストでログのデグレが起きた時はWinMergeなどでinternal_test内のlogファイルと比較し、相違を確認できる

|パス|内容|納品|
|:---|:---|:--:|
| log/ | 単体テストの実行で出力されるログディレクトリ | - |
| log/HA<_nnn_>_<_name_>.log/ | 対応するテストのcppファイルと同一の名称となる | - |

## 3. 単体テストプログラムの生成

注）本機能はまだ未実装である。

### 3-1. 手順

単体テストプログラム(src/)はリポジトリで管理しているが、テストモデルから`script/create_ut.sh`を実行して生成する。

単体テストプログラムの生成手順を以下に示す。
```
cd unittest
sh script/create_ut.sh
ls src
（単体テストプログラムファイルが表示）
```

### 3-2. テストモデルの構成

テストモデルは、以下の３つのディレクトリ下に単体テスト項目ごとに保存されている。

* __api_test_project/__ （APIテストのテストモデル）
* __internal_test_project/__ （内部テストモデル）
* __logic_test_project/__ （制約式テストモデル）

単体テストプログラムの生成時、テストモデル名はそのままC++クラス名として使用している。そのため、テストモデル名はC++クラス名で使用できる文字列である必要がある。
マイナスや空白、マルチバイト文字などは使用できない。
rba.tool.simulator.junit.testで提供されるテストモデル名は、一部でC++クラス名で使用できない文字を使用している。それらの文字列を以下のルールで変換している。

|元の文字|変換後|
|:--|:--|
| "__(__"または"__)__" | "_"（アンダーバー） |
| "__-__"（ハイフン） | "_"（アンダーバー）  |
| "__→__" | "__to__" |

### 3-3. 単体テストスクリプトのフォーマット

単体テストスクリプトのフォーマットは以下の通りとする

#### (1) 期待値比較

##### アロケータブルと割り当てコンテンツ

形式：__Assert__,__A__,<_allocatable_>,<_content_>

<_allocatable_> : アロケータブル名<br><_content_> : コンテンツ名<br>
コンテンツ名が"NULL"の場合は割り当てなし

##### アッテネートの状態

形式：__Assert__,__ATTENUATE__,<_zone_>,__true__|__false__

<_zone_> : ゾーン名<br>
__true__=アッテネートが有効<br>__false__=アッテネートが無効

##### 表示要求のキャンセル状態

形式：__Assert__,__CANCEL__,<_content_>,<_state_>,__true__|__false__

<_content_> : コンテンツ名<br><_state_> : ステート名<br>
__true__=キャンセルされている<br>__false__=キャンセルされていない

##### シーンの状態とプロパティ

形式：__Assert__,__S__,<_scene_>,__on__|__off__[,<_property_>:<_value_>]...

<_scene_> : シーン名<br><_property_> : プロパティ名<br><_value_> : プロパティ値（整数値）

#### (2) 表示要求

##### コンテンツとステートを指定して表示要求をセット

形式：__C__,__ON__|__OFF__,<_content_>,<_state_>

__ON__=表示要求<br>__OFF__=表示取り下げ要求<br><_content_> : コンテンツ名<br><_state_> : ステート名

##### シーン要求をセット

形式：__S__,__ON__|__OFF__,<_scnene_>

__ON__=シーン要求<br>__OFF__=シーン取り下げ要求<br><_scene_> : シーン名

#### (3) 調停実行

形式：__execute__

以上
