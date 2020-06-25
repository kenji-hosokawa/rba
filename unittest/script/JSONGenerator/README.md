### ビルド方法
1. RBAToolを起動。または、Xtendをインストールしたeclipseを起動　https://gihyo.jp/dev/serial/01/engineer_toolbox/0023
2. git clone https://scm.dndev.net/sn03/stash/scm/ha/rba_tools.git
3. パースペクティブをJavaにする
4. File->Import->General->Existing Projects into Workspace->Next
5. Select root directoryを2.のrba_toolsにし、Finish
6. AutoBuildが始まるので、eclipse右下のProcess表示が消えるまで待つ
7. rba.tool.editor.endpoint->xtend-gen->rba.tool.editor.endpoint->ServerLauncher.javaを右クリック
8. Run As->1 Java Applicationをクリック
9. rba.tool.editor.endpoint->script->TemplateGenerator.groovyを最新のものに置き換える
9. rba.tool.editor.endpoint->template->RBAModel.jsontemplateを最新のものに置き換える
9. rba.tool.editor.endpointを右クリック
10. Export->Java->Runnable JAR file->Next
11. Launch confingurationを`ServerLauncher - rba.tool.editor.endpoint`にする
12. Export destination を`任意のフォルダ\JSONGenerator.jar`にする
13. Library handling を`Copy required libraries into a sub-folder next to the generated JAR`にする
14. Finish。`JAR export finished with warnings. See details for additional information.`というwarningが出るが、今はスルーしておく。
15. `JSONGenerator_lib`と`JSONGenerator.jar`が12.で指定したフォルダに出力されている

### 実行環境準備
1. `JSONGenerator_lib`と`JSONGenerator.jar`と同じディレクトリに、rba.tool.editor.endpoint->libをコピーして持ってくる
2. `JSONGenerator_lib`と`JSONGenerator.jar`と同じディレクトリに、rba.tool.editor.endpoint->scriptをコピーして持ってくる
3. `JSONGenerator_lib`と`JSONGenerator.jar`と同じディレクトリに、rba.tool.editor.endpoint->templateをコピーして持ってくる

### usage
- If some errors occur, RBAModel.json is not generated (exit code 1).
````
java -cp ./ -jar JSONGenerator.jar "[path to model directory]" "[path to output directory]"
````
### example
- RBAModel.json file is generated in directory same as JSONGenerator.jar
````
java -cp ./ -jar JSONGenerator.jar "./model"
````
- RBAModel.json file is generated in ~/ directory
````
java -cp ./ -jar JSONGenerator.jar "./model" "~/"
````
