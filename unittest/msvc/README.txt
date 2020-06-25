#
# VisualC++向け調停ロジック単体テスト環境の構築
#

1. 対象環境

　以下の環境で動作確認を行った。

 - Windows10
 - Visual Studio 2017

1. Google Testの取得
Cygwin等を使用して、Google Testの取得シェルスクリプトを実行する。

$ cd unittest
$ sh script/install_gt.sh

カレントディレクトリにgoogletestディレクトリが生成されていることを確認する。

2. Google Testのビルド

(1) ソリューションファイルを開く
取得したGoogle Testのソリューションファイルを確認する。

$ ls googletest/googletest/msvc/2010/*.sln
googletest/googletest/msvc/2010/gtest.sln
googletest/googletest/msvc/2010/gtest-md.sln

ファイルエクスプローラなどから、上記のgtest-md.slnを起動する。

(2) プロジェクト操作の再ターゲット
「プロジェクト操作の再ターゲット」ダイアログが表示されるので、各設定をデフォルトのままで
OKボタンを押す。

(3) ソリューションのビルドを実行する
エラーがなく終了することを確認する。

(4) Visual Studioを終了する

3. 単体テスト環境のビルドと実行

(1) 単体テストのソリューションを開く
単体テストのソリューションファイルは以下の通り。

unittest/msvc/rba_unittest/rba_unittest.sln

(2) 単体テストプログラムと調停ロジック本体をビルド
ソリューションのビルドで実行される。

(3) 単体テスト実行

「デバッグの開始」
もしくは
「デバッグなし開始」
で実行する。

　単体テストを実行すると、Visual Studioのコンソールが起動し、Google Testの形式で
単体テスト情報が表示される。

以上
