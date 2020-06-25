#!/bin/bash

# Linux用　jsonファイル　生成スクリプト
# arbitrator/rba/unittestディレクトリ内のmodelディレクトリのモデルファイルを元に
# RBAModel.jsonファイルを生成し、modelディレクトリと同一階層のtemplate-genディレクトリにコピーする。
# 使い方
# cd arbitrator/rba/unittest/script/JSONGenerator
# ./generate_json.sh

# 2019/04/10現在、JSONGeneratorに不具合があり、jsonを生成できないモデルがあるため、
# JSONGeneratorがエラーを出したプロジェクトは"ErrorProjectList.txt"にリストするように対応

# 2019/12/2 
# rbaユニットテスト項目が多く、Linux上で実施すると落ちる可能性があるため、Windows上で実施してください。
workingDir="temp_JSONGenerator"
inputDir="model"
outputDir="template-gen"
outputFileName="RBAModel.json"
errorListFileName="ErrorProjectList.txt"
unittestDirPath="../.."

mkdir -p $workingDir

for test_projectDirPath in `find $unittestDirPath -type d -name '*_test_project'`
do
    for inputDirPath in `find $test_projectDirPath -type d -name $inputDir`
    do
        projectDirPath=${inputDirPath%/$inputDir}
        # 対象のプロジェクト名を出力
        echo "${projectDirPath##*/}"

        # 日本語を含むパスは2019/04/10現在、JSONGeneratorに渡せないため
        # modelディレクトリを作業ディレクトリにコピー
        rm -rf $workingDir/*
        cp -pR $inputDirPath/* $workingDir

        # 作業ディレクトリにjsonファイルを生成
        java -cp ./ -jar JSONGenerator.jar "./$workingDir" "./$workingDir"

        # modelディレクトリと同一階層のtemplate-genディレクトリにコピー
        # jsonファイルが生成されていなければErrorProjectList.txtに出力
        if [ -e $workingDir/$outputFileName ]
        then
            cp $workingDir/$outputFileName $projectDirPath/$outputDir/$outputFileName
        else
            echo $projectDirPath >> $errorListFileName
        fi

    done
done