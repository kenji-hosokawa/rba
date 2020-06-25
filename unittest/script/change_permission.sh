#!/bin/sh

# 指定ディレクトリ配下のファイルの権限を一度に変更する
find ./gen -type f -exec chmod 664 {} +
find ./testmodel -type f -exec chmod 664 {} +
