#!/usr/bin/env python3
# -*- coding:utf-8 -*-

'''
tcファイルから単体テストプログラムを生成する。

使用方法；
python3 create_ut_prog.py <tcfile> [-o <outdir>] [-j <jsonfile>] [-c <clasname>]
                                   [--debug][--log]

<tcfile>         : TCファイル
[-o <outdir>]    : 出力ディレクトリ
                   指定しない場合はカレントディレクトリに出力する。
[-j <jsonfile>]  : JSONファイル
                   ファイル名を変えてコピーするだけで解析には使用しない。
[-c <classname>] : テストクラス名
                   指定しない場合はファイル名をクラス名とする。
[--debug]        : デバッグオプション
                   TCファイルで指定したエリア、ゾーン、シーン、コンテント、ステート
                   の名称が存在するか、Google Test上で毎回ASSERTでチェックするように
                   .cppファイルを出力する。TCファイルのデバッグに使用する。
[--log]        : ログ出力オプション
                   ログ出力に必要なロジックを入れて.cppと.hppファイルを出力する。


使用例１: 直接tcファイルから単体テストプログラムを生成する。

$ python3 create_it_prog.py example.tc
$ ls
exampel.hpp  example.cpp

使用例２: 出力ディレクトリを指定する。

$ python3 create_it_prog.py example.tc -o ut
$ ls ut
exampel.hpp  example.cpp

使用例３: JSONファイルを指定して一緒にコピーする。

$ python3 create_it_prog.py example.tc -o ut -j RBAModel.json
$ ls tool_test
exampel.hpp  example.cpp  example.json

使用例４: クラス名を指定して、JSONファイルを指定して一緒にコピーする。

$ python3 create_it_prog.py example.tc -o ut -j BAModel.json -c Foo
$ ls tool_test
Foo.hpp  Foo.cpp  Foo.json
$ less Foo.cpp
...
Foo::Foo() {}
Foo::~Foo() {}
...
  // 0012  C,on,FM,NORMAL
  result_ = arb_->execute(u8"FM/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=xx"));
  // 0013  Assert,A,Base,FM
  EXPECT_EQ(u8"FM",getAllocated("line=xx", u8"Base"));
...


使用例５: デバッグオプションを使用する。

$ python3 create_it_prog.py example.tc -o ut -j BAModel.json -c Foo --debug
$ ls tool_test
Foo.hpp  Foo.cpp  Foo.json
$ less Foo.cpp
...
Foo::Foo() {}
Foo::~Foo() {}
...
  // 0012  C,on,FM,NORMAL
  result_ = arb_->execute(u8"FM/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=xx"));
  // 0013  Assert,A,Base,FM
  EXPECT_EQ(u8"FM",getAllocated("line=xx", u8"Base"));
...
  // 0012  C,on,FM,NORMAL
  ASSERT_TRUE(isEnableContext(u8"FM/NORMAL"));
  result_ = arb_->execute(u8"FM/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=xx"));
  // 0013  Assert,A,Base,FM
  ASSERT_TRUE(isEnableAllocatable("line=xx", u8"Base"));
  ASSERT_TRUE(isEnableContext("line=xx", u8"FM"));
  EXPECT_EQ(u8"FM",getAllocated("line=xx", u8"Base"));


'''

import sys
import os.path
import re
import shutil

Output_Path = '.'               # 出力ディレクトリ
Context_Continue = False        # 表示要求コンテキストのcontinueフラグ
Before_Continue_Reqest = ''     # 直前にcontinueされた要求コンテキストのon,offフラグ
Debug_Flag = False              # デバッグフラグ（モデルをASSERTでチェックする）
Log_Flag = False                # ログフラグ（ログ出力処理を入れる）

def write_hpp(class_name):
    '''
    テストプログラムヘッダのファイル出力
    '''
    class_hpp = class_name+'.hpp'
    class_hpp_path = os.path.join(Output_Path, class_hpp)
    class_hpp_cap = class_hpp.replace('.', '_').upper()
    if Log_Flag == True:
        log_hpp = '''
#ifdef RBA_USE_LOG
  std::unique_ptr<RBALogManager> logm_;
#endif'''
    else:
        log_hpp = ''
    with open(class_hpp_path, 'w') as f:
        f.write('''// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * {file}
 */

#ifndef {cap}
#define {cap}

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "{cls}.json"

namespace {{

using namespace rba;

class {cls} : public ::testing::Test
{{
protected:
  {cls}();
  virtual ~{cls}();
  virtual void SetUp();
  virtual void TearDown();
  bool isSuccess(const std::string& msg);
  bool isSatisfiedConstraints(const std::string& msg);
  bool isTrue(const std::string& msg, bool res);
  std::string getAllocated(const std::string& msg,
                           const std::string& allocName);
  bool isCanceled(const std::string& msg,
                  const std::string& contentName);
  bool isActive(const std::string& msg,
                const std::string& sceneName);
  int32_t getProperty(const std::string& msg,
                      const std::string& sceneName,
                      const std::string& propertyName);
  bool isEnableAllocatable(const std::string& msg,
                           const std::string& allocName);
  bool isEnableContext(const std::string& msg,
                       const std::string& contextName);
  bool isEnableScene(const std::string& msg,
                     const std::string& sceneName);
  bool isAttenuated(const std::string& msg,
                    const std::string& zoneName);

protected:
  rba::RBAModel* model_=nullptr;
  rba::RBAArbitrator* arb_=nullptr;
  std::unique_ptr<RBAResult> result_=nullptr;{log}
}};

}}
#endif
'''.format(file=class_hpp, cap=class_hpp_cap, cls=class_name, log=log_hpp))


def create_cpp_header(test_class_name):
    '''
    テストプログラム本体の先頭コードを生成
    '''
    setup_str = ''
    if Log_Flag == False:
        setup_str = '''
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);'''
        teardown_str = ''
        header_str = ''
    else:
        setup_str = '''
#ifdef RBA_USE_LOG
  std::unique_ptr<stub::StubLogCollector>
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/{cls}.log",
                                                       LOGPATH"/{cls}.log",
                                                       true);
  // カバレッジログの設定
  logm_ = std::make_unique<rba::RBALogManager>();
  logm_->addCoverageLogCollector(collector.get());
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_, logm_.get());
  for (auto constraint : model_->getConstraints()) {{
    dynamic_cast<RBAConstraintImpl*>(constraint)->createHierarchy();
  }}
  for (auto postConstraint : model_->getPostConstraints()) {{
    dynamic_cast<RBAPostConstraintImpl*>(postConstraint)->createHierarchy();
  }}
  for (auto rule : dynamic_cast<RBAModelImpl*>(model_)->getRules()) {{
    rule->createHierarchy();
  }}
  logm_->removeCoverageLogCollector(collector.get());
  // ログの設定
  RBALogManager::init(4);  // 全ログ出力
  RBALogManager::setEnable(RBALogManager::TYPE_ALL_CONSTRAINTS, true);
  RBALogManager::setEnable(RBALogManager::TYPE_REQUEST, true);
  RBALogManager::setEnable(RBALogManager::TYPE_PREVIOUS_RESULT, true);
  RBALogManager::setEnable(RBALogManager::TYPE_ARBITRATE, true);
  RBALogManager::setEnable(RBALogManager::TYPE_CANCEL_REQUEST, true);
  RBALogManager::setEnable(RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS, true);
  RBALogManager::setEnable(RBALogManager::TYPE_RUN_RULE, true);
  RBALogManager::setEnable(RBALogManager::TYPE_RESULT, true);
  RBALogManager::setEnable(RBALogManager::TYPE_SAVE_LOG, true);
#else
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
#endif'''.format(cls=test_class_name)
        teardown_str = '''
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif'''
        header_str = '''
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAPostConstraintImpl.hpp"
#include "RBARuleImpl.hpp"'''

    return u'''// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * {cls}.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "{cls}.hpp"{header}


namespace {{

using namespace rba;

{cls}::{cls}() {{}}
{cls}::~{cls}() {{}}

void {cls}::SetUp()
{{{setup}
}}

void {cls}::TearDown()
{{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;{teardown}
}}

bool {cls}::isSuccess(const std::string& msg)
{{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}}

bool {cls}::isSatisfiedConstraints(const std::string& msg)
{{
  return result_->satisfiesConstraints();
}}

bool {cls}::isTrue(const std::string& msg, bool res)
{{
  return res;
}}

std::string {cls}::getAllocated(const std::string& msg,
                                const std::string& allocName)
{{
  const RBAArea* area = model_->findArea(allocName);
  std::string contentName;
  if(area) {{
    if(result_->isVisible(area)) {{
      const RBAViewContentState* allocState = result_->getContentState(area);
      if(allocState) {{
        contentName = allocState->getOwner()->getName();
      }}
    }}
  }}
  else {{
    const RBAZone* zone = model_->findZone(allocName);
    if(result_->isSounding(zone)) {{
      const RBASoundContentState* allocState = result_->getContentState(zone);
      if(allocState) {{
        contentName = allocState->getOwner()->getName();
      }}
    }}
  }}
  return contentName;
}}

bool {cls}::isCanceled(const std::string& msg,
                       const std::string& contentName)
{{
  const RBAViewContent* viewContent = model_->findViewContent(contentName);
  if(viewContent) {{
    // ビューの場合
    for(const RBAViewContentState* state : viewContent->getContentStates()) {{
      if(result_->isCancel(state)) {{
        return true;
      }}
    }}
  }}
  else {{
    // サウンドの場合
    const RBASoundContent* soundContent = model_->findSoundContent(contentName);
    for(const RBASoundContentState* state : soundContent->getContentStates()) {{
      if(result_->isCancel(state)) {{
        return true;
      }}
    }}
  }}

  return false;
}}

bool {cls}::isActive(const std::string& msg, const std::string& sceneName)
{{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {{
    return false;
  }}

  return result_->isActive(scene);
}}

int32_t {cls}::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {{
    return -9999;
  }}

  return result_->getSceneProperty(scene, propertyName);
}}

bool {cls}::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {{
    return true;
  }}
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}}

bool {cls}::isEnableContext(const std::string& msg,
                            const std::string& contextName)
{{
  // コンテントチェック
  std::string contentName
     = RBAViewContentState::getContentNameByContext(contextName);
  const RBAViewContent* viewContent = model_->findViewContent(contentName);
  if(viewContent) {{
    std::string stateName
      = RBAViewContentState::getContentStateNameByContext(contextName);
    if(stateName.empty()) {{
      return true;
    }}
    const RBAViewContentState* state = model_->findViewContentState(contextName);
    return state != nullptr;
  }}
  else {{
    const RBASoundContent* soundContent = model_->findSoundContent(contentName);
    if(soundContent == nullptr) {{
      return false;
    }}
    std::string stateName
      = RBASoundContentState::getContentStateNameByContext(contextName);
    if(stateName.empty()) {{
      return true;
    }}
    const RBASoundContentState* state = model_->findSoundContentState(contextName);
    return state != nullptr;
  }}
}}

bool {cls}::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}}

bool {cls}::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}}

'''.format(header=header_str, setup=setup_str, teardown=teardown_str, cls=test_class_name)

def create_testcase_start(line_num, test_class_name, line):
    '''
    テストケースの先頭コードを生成
    '''
    global Context_Continue
    Context_Continue = False
    global Before_Continue_Reqest
    Before_Continue_Reqest = ''
    label_str = re.sub(r' .*$', '', line.replace('#start ', ''))
    if label_str.isdigit():
        num = int(label_str)
        label_str = 'Test_%02d' % (num)
    return_str = '// %04d  %s\n' % (line_num, line) + '''TEST_F(%s, %s)
{
  std::list<std::string> contexts;
''' % (test_class_name, label_str)
    if Log_Flag:
        return_str = return_str + '''#ifdef RBA_USE_LOG
  std::unique_ptr < stub::StubLogCollector >
  collector = std::make_unique<stub::StubLogCollector>(JSONPATH"/{test_class_name}_{num}.log",
                                                       LOGPATH"/{test_class_name}_{num}.log",
                                                       true);
  logm_->addCoverageLogCollector(collector.get());
#endif
'''.format(test_class_name=test_class_name, num=label_str)
    return return_str

def create_cmd_context(line_num, line):
    '''
    コンテキスト要求のコードを生成
    '''
    global Context_Continue
    global Before_Continue_Reqest
    msg = 'line=%d' % (line_num)
    params = line.split(',')
    request = 'false'
    if params[1] == 'on':
        request = 'true'
    context = params[2]
    if len(params) > 3:
        context += '/' + params[3]
    buf = '  // %04d  %s\n' % (line_num, line)

    if Debug_Flag:
        buf += '  ASSERT_TRUE(isEnableContext("%s", u8"%s"));\n' \
            % (msg, context)

    if request and len(params) == 5 and params[-1] == 'continue':
        Context_Continue = True
        if Before_Continue_Reqest != '' and Before_Continue_Reqest != request:
            print("ERROR:",line_num, u"onとoffを同時要求することはできない")
            buf += u'  生成時にエラーが発生しています;\n'
        Before_Continue_Reqest = request
        buf += '  contexts.push_back(u8"%s");\n' % (context)
    else:
        if Context_Continue:
            if Before_Continue_Reqest != '' and Before_Continue_Reqest != request:
                print("ERROR:",line_num, u"onとoffを同時要求することはできない")
                buf += u'  生成時にエラーが発生しています;\n'
            buf += '  contexts.push_back(u8"%s");\n' % (context)
            buf += '  result_ = arb_->execute(contexts, %s);\n' % (request)
            buf += '  contexts.clear();\n'
            Context_Continue = False
            Before_Continue_Reqest = ''
        else:
            buf += '  result_ = arb_->execute(u8"%s", %s);\n' \
                % (context, request)
        buf += '  EXPECT_TRUE(isSuccess("%s"));\n' % (msg)
        buf += '  EXPECT_TRUE(isSatisfiedConstraints("%s"));\n' % (msg)

    return buf

def get_properties(params):
    '''
    プロパティの取り出し
    '''
    props = []
    key = ""
    for idx, param in enumerate(params):
        if (idx%2) == 0:
            key = param
        else:
            value = param
            props.append((key, int(value)))
    return props

def createe_cmd_scene_set(line_num, line):
    '''
    シーンセットのコードを生成
    '''
    buf = '  // %04d  %s\n' % (line_num, line)
    msg = 'line=%d' % (line_num)
    params = line.split(',')
    request = 'false'
    if params[2] == 'on':
        request = 'true'
    scene = params[3]
    buf += '  {\n'
    # プロパティの取得
    props = []
    if len(params) > 4:
        props = get_properties(params[4:])
    buf += '    std::list<std::pair<std::string, std::int32_t>> props;\n'
    if props:
        for p in props:
            buf += '    props.push_back(std::make_pair(u8"%s", %d));\n' \
                % (p[0], p[1])
    buf += '''    bool res = arb_->setScene(u8"%s", %s, props);
    EXPECT_TRUE(isTrue("%s", res));
  }
''' % (scene, request, msg)

    return buf

def create_cmd_scene(line_num, line):
    '''
    シーン要求のコードを生成
    '''
    msg = 'line=%d' % (line_num)
    params = line.split(',')
    request = 'false'
    if params[1] == 'on':
        request = 'true'
    
    scene = params[2]
    props = []
    buf = '  // %04d  %s\n' % (line_num, line)
    if len(params) >= 4:
        props = get_properties(params[3:])
        buf += '''  {{
    std::list<std::pair<std::string, std::int32_t>> props;
'''.format(line=line)
        if Debug_Flag:
            buf += '    ASSERT_TRUE(isEnableScene("%s", u8"%s"));\n' % (msg, scene)
        if props:
            for p in props:
                buf += '    props.push_back(std::make_pair(u8"%s", %d));\n'\
                    % (p)
        if request == 'true':
            buf += '''    result_ = arb_->execute(u8"%s", props);
    EXPECT_TRUE(isSuccess("%s"));
  }
''' % (scene, msg)
        else:
            buf += '''    bool res = arb_->setScene(u8"%s", false, props);
    EXPECT_TRUE(isTrue("%s", res));
    result_ = arb_->execute();
    EXPECT_TRUE(isSuccess("%s"));
  }
''' % (scene, msg, msg)
    else:
       buf += '''  result_ = arb_->execute(u8"%s", %s);
  EXPECT_TRUE(isSuccess("%s"));
''' % (scene, request, msg)
    return buf

def create_cmd_assert_alloc(content, line_num, alloc):
    '''
    アロケーションのアサーションコードを生成
    '''
    msg = 'line=%d' % (line_num)
    buf = ''
    if Debug_Flag:
        buf += '  ASSERT_TRUE(isEnableAllocatable("%s", u8"%s"));\n' \
            % (msg, alloc)
    if content:
        if Debug_Flag:
            buf += '  ASSERT_TRUE(isEnableContext("%s", u8"%s"));\n' \
                % (msg, content)
        buf += '  EXPECT_EQ(u8"%s",getAllocated("%s", u8"%s"));\n' \
            % (content, msg, alloc)
    else:
        buf += '  EXPECT_EQ(u8"",getAllocated("%s", u8"%s"));\n'  % (msg, alloc)

    return buf

def create_cmd_assert_cancel(line_num, content, cancel_flag):
    '''
    コンテントキャンセルのアサーションコードを生成
    '''
    msg = 'line=%d' % (line_num)
    buf = ''
    if Debug_Flag:
        buf += '  ASSERT_TRUE(isEnableContext("%s", u8"%s"));\n' \
            % (msg, content)
    if cancel_flag:
        buf += '  EXPECT_TRUE(isCanceled("%s", u8"%s"));\n' % (msg, content)
    else:
        buf += '  EXPECT_FALSE(isCanceled("%s", u8"%s"));\n' % (msg, content)

    return buf

def create_cmd_assert_scene(line_num, scene, active_flag, key, value):
    '''
    シーンのアサーションコードを生成
    '''
    msg = 'line=%d' % (line_num)
    buf = ''
    if Debug_Flag:
        buf += '  ASSERT_TRUE(isEnableScene("%s", u8"%s"));\n' % (msg, scene)
    if active_flag:
        buf += '  EXPECT_TRUE(isActive("%s", u8"%s"));\n' % (msg, scene)
    else:
        buf += '  EXPECT_FALSE(isActive("%s", u8"%s"));\n' % (msg, scene)
    if key:
        buf += '  EXPECT_EQ(%d, getProperty("%s", u8"%s", u8"%s"));\n' \
            % (value, msg, scene, key)
    
    return buf

def create_cmd_assert_attenuated(line_num, alloc, flag):
    '''
    Attenuatedアサーションコードを生成
    '''
    msg = 'line=%d' % (line_num)
    buf = ''
    if Debug_Flag:
        buf += '  ASSERT_TRUE(isEnableAllocatable("%s", u8"%s"));\n' \
            % (msg, alloc)
    if flag:
        buf += '  EXPECT_TRUE(isAttenuated("%s", u8"%s"));\n' % (msg, alloc)
    else:
        buf += '  EXPECT_FALSE(isAttenuated("%s", u8"%s"));\n' % (msg, alloc)

    return buf

def create_cmd_assert(line_num, line):
    '''
    アサーションのコードを生成
    '''
    buf = '  // %04d  %s\n' % (line_num, line)
    params = line.split(',')
    assert_type = params[1]
    if assert_type == 'A':
        alloc = params[2]
        content = ''
        if len(params) > 3:
            content = params[3]
        buf += create_cmd_assert_alloc(content, line_num, alloc)
        if len(params) > 4 and content:
            if ':' in params[4]:
                attr, flag = params[4].split(':')
                if attr == 'attenuated':
                    buf += create_cmd_assert_attenuated(line_num, alloc,
                                                        flag=='true')
    elif assert_type == 'C':
        content = params[3]
        cancel_flag = False
        if params[4] == 'true':
            cancel_flag = True
        buf += create_cmd_assert_cancel(line_num, content, cancel_flag)
    elif assert_type == 'S':
        scene = params[2]
        active_flag = False
        if params[3] == 'on':
            active_flag = True

        if len(params) > 4:
            props = get_properties(params[4:])
            for p in props:
                buf += create_cmd_assert_scene(line_num,
                                               scene, active_flag, p[0], p[1])
        else:
            buf += create_cmd_assert_scene(line_num, scene, active_flag,None,None)
    else:
        print('ERROR: %04d  %s' % (line_num, line))

    return buf

def create_testcases(test_class_name, tc_filepath):
    buf = ''
    start_flag = False
    line_num = 0
    with open(tc_filepath, 'r') as f:
        for line in f.readlines():
            line_num += 1
            line = line.rstrip()
            params = line.split(',')
            cmd = params[0]
            sub_cmd = ''
            if len(params) > 1:
                sub_cmd = params[1]
            
            if '#start' in cmd:
                if start_flag:
                    if Log_Flag:
                        buf += '''#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
'''
                    buf += '}\n\n'
                start_flag = True
                buf += create_testcase_start(line_num, test_class_name, line)
            elif 'CL' == cmd:
                buf += '  // %04d  CL\n  arb_->clearArbitration();\n' \
                    % (line_num)
                if Log_Flag:
                    buf += '''#ifdef RBA_USE_LOG
  RBALogManager::init(4);
#endif
'''
            elif 'C' == cmd:
                buf += create_cmd_context(line_num, line)
            elif 'SET' == cmd:
                print('ERROR:', tc_filepath, line_num, u"現時点SETは未対応")
                # buf += createe_cmd_scene_set(line_num, line)
            elif 'Allocate' == cmd:
                print('ERROR:', tc_filepath, line_num, u"現時点Allocateは未対応")
            elif 'S' == cmd:
                buf += create_cmd_scene(line_num, line)
            elif 'Assert' == cmd:
                buf += create_cmd_assert(line_num, line)
            elif re.match(r'^#', line):
                buf += '// %04d  %s\n' % (line_num, line)
            elif not line:
                continue
            else:
                print('ERROR:', tc_filepath, line_num, line)
    
    if start_flag:
        if Log_Flag:
            buf += '''#ifdef RBA_USE_LOG
  logm_->removeCoverageLogCollector(collector.get());
  collector->log(result_->getLog());
#endif
'''
        buf += '}\n\n'

    return buf

def write_cpp(test_class_name, tc_filepath):
    '''
    テストプログラム本体のファイル出力
    '''
    test_class_cpp = test_class_name + '.cpp'
    test_class_cpp_path = os.path.join(Output_Path, test_class_cpp)
    with open(test_class_cpp_path, 'w') as fout:
        fout.write(create_cpp_header(test_class_name))
        fout.write(create_testcases(test_class_name, tc_filepath))
        fout.write('}\n')

def parse_option():
    '''
    コマンド引数のパース
    tcフィアルのパスを返す。
    -oオプションがあるときは、Output_Pathをセットする。
    '''
    global Output_Path
    global Debug_Flag
    global Log_Flag
    tc_path = ''
    json_path = ''
    class_name = ''
    outdir_flag = False
    json_flag = False
    class_flag = False
    for arg in sys.argv:
        if outdir_flag:
            outdir_flag = False
            Output_Path = arg
        elif json_flag:
            json_flag = False
            json_path = arg
        elif class_flag:
            class_flag = False
            class_name = arg
        elif arg == '-o':
            outdir_flag = True
        elif arg == '-j':
            json_flag = True
        elif arg == '-c':
            class_flag = True
        elif arg == '--debug':
            Debug_Flag = True
        elif arg == '--log':
            Log_Flag = True
        else:
            tc_path = arg
    return tc_path, json_path, class_name

def copy_jsonfile(test_class_name, json_path):
    out_json_path = os.path.join(Output_Path, test_class_name+'.json')
    shutil.copyfile(json_path, out_json_path)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python3 %s <tcfile> [-o <outdir>] [-j <jsonfile>] [-c <clasname>] [--debug][--log]' \
              % (sys.argv[0]))
        exit()

    tc_path, json_path, test_class_name = parse_option()
    if not os.path.exists(tc_path):
        print('%s: No such file or directory' % (tc_path))
        exit()

    if json_path and not os.path.exists(json_path):
        print('%s: No such file or directory' % (json_path))
        exit()

    tc_filename = os.path.basename(tc_path)
    if not test_class_name:
        test_class_name = re.sub(r'\..*$', '', tc_filename)
    write_hpp(test_class_name)
    write_cpp(test_class_name, tc_path)
    if json_path:
        copy_jsonfile(test_class_name, json_path)
    
# end of file
