#/bin/sh

# このシェルスクリプトは調停FW評価報告書のV1シートに使用するcsvデータを生成するためのものである
# unittestの実行ファイルtest_rbaをビルドしたあと、このシェルスクリプトを実行すると
# テスト結果のcsvファイルが生成される

XMLFILE=result.xml

CSVFILE=./run_log.csv

./test_rba --gtest_output=xml:$XMLFILE

python3 script/gtest_parse.py $XMLFILE > $CSVFILE
