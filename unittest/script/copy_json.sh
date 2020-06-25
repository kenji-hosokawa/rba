#!/bin/bash

# Linux用　jsonファイル　コピースクリプト
# xxx_test_project以下のtemplate-genディレクトリのjsonファイルを
# xxx_testの対応するjsonにコピーする。

# 使い方
# cd arbitrator/rba/unittest/script
# ./copy_json.sh

inputDir="template-gen"
inputFileName="RBAModel.json"
errorListFileName="ErrorProjectList_copy.txt"
unittestDirPath="../"

for test_projectDirPath in `find $unittestDirPath -type d -name '*_test_project'`
do
    outputDirPath=${test_projectDirPath%_project}

    for inputDirPath in `find $test_projectDirPath -type d -name $inputDir`
    do
        projectDirPath=${inputDirPath%/$inputDir}
        # 対象のプロジェクト名を出力
        #echo "${projectDirPath##*/}"

        # プロジェクトディレクトリ以下のtcファイルを検索
        tcFilePath=`find $projectDirPath -type f -name '*.tc'`
        tcFileName="${tcFilePath##*/}"

        # tcファイルが存在すればそのファイル名を出力名に使う
        if [ "${tcFileName##*.}" = "tc" ]
        then
            outputFileName="${tcFileName%.*}.json"
        else
        # tcファイルが存在しなければプロジェクト名を出力名に使う
            outputFileName="${projectDirPath##*/}.json"
            #"()-"は"_"に、"→"は"To"に変換する
            outputFileName="${outputFileName//(/_}"
            outputFileName="${outputFileName//)/_}"
            outputFileName="${outputFileName//-/_}"
            outputFileName="${outputFileName//→/To}"
        fi

        # xxx_testディレクトリにコピーする
        # 同一名のjsonファイルがなければ名前決め失敗のエラーとしてErrorProjectList.txtに出力する
        if [ -e $outputDirPath/$outputFileName ]
        then
            cp $inputDirPath/$inputFileName $outputDirPath/$outputFileName
        else
            echo $projectDirPath >> $errorListFileName
        fi
    done
done
