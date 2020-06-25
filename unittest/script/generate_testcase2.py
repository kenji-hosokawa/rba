#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import sys
import os.path
import re

HEADER_TEMPLATE_FILE = 'template/Test_Header_template.hpp'
BODY_TEMPLATE_FILE = 'template/Test_Body_template.cpp'
TEST_CASE_BODY_TEMPLATE_FILE = 'template/Test_TestCaseBody_template.cpp'
TEST_ITEM_REQ_ON_TEMPLATE_FILE = 'template/Test_TestItemReqOn_template.cpp'
TEST_ITEM_REQ_OFF_TEMPLATE_FILE = 'template/Test_TestItemReqOff_template.cpp'
TEST_ITEM_SCENE_ON_TEMPLATE_FILE = 'template/Test_TestItemSceneOn_template.cpp'
TEST_ITEM_SCENE_OFF_TEMPLATE_FILE = 'template/Test_TestItemSceneOff_template.cpp'
TEST_ITEM_EXECUTE_TEMPLATE_FILE = 'template/Test_TestItemExecute_template.cpp'
TEST_ITEM_ASSERT_VISIBLE_TEMPLATE_FILE \
    = 'template/Test_TestItemAssertVisible_template.cpp'
TEST_ITEM_ASSERT_INVISIBLE_TEMPLATE_FILE \
    = 'template/Test_TestItemAssertInvisible_template.cpp'
TEST_ITEM_ASSERT_CANCEL_TRUE_TEMPLATE_FILE \
    = 'template/Test_TestItemAssertCancelTrue_template.cpp'
TEST_ITEM_ASSERT_CANCEL_FALSE_TEMPLATE_FILE \
    = 'template/Test_TestItemAssertCancelFalse_template.cpp'

TEMPLATE_GUARDNAME = '<GUARDNAME>'
TEMPLATE_FILENAME = '<FILENAME>'
TEMPLATE_TEST_SUITE_NAME = '<TEST_SUITE_NAME>'
TEMPLATE_TEST_CASE_NAME = '<TEST_CASE_NAME>'
TEMPLATE_HEADER_FILENAME = '<HEADER_FILENAME>'
TEMPLATE_GENERATE_FUNC_NAME = '<GENERATE_FUNC_NAME>'
TEMPLATE_INPUT_PARAMS = '<INPUT_PARAMS>'
TEMPLATE_JSONPATH = '<JSONPATH>'

TEMPLATE_GENERATED_FUNC_BODY = '<GENERATE_FUNC_BODY>'
TEMPLATE_TEST_CASE_BODY = '<TEST_CASE_BODY>'
TEMPLATE_TEST_ITEM_BODY = '<TEST_ITEM_BODY>'

FileName_str = ''
GuardName_str = ''
TestSuiteName_str = ''
TestCaseName_str = ''
HeaderFileName_str = ''
GenerateFuncName_str = ''
InputParams_str = ''
JsonPath_str = ''

def replace_template_string(line):
    if FileName_str:
        line = line.replace(TEMPLATE_FILENAME, FileName_str)
    if GuardName_str:
        line = line.replace(TEMPLATE_GUARDNAME, GuardName_str)
    if TestSuiteName_str:
        line = line.replace(TEMPLATE_TEST_SUITE_NAME, TestSuiteName_str)
    if TestCaseName_str:
        line = line.replace(TEMPLATE_TEST_CASE_NAME, TestCaseName_str)
    if HeaderFileName_str:
        line = line.replace(TEMPLATE_HEADER_FILENAME, HeaderFileName_str)
    if GenerateFuncName_str:
        line = line.replace(TEMPLATE_GENERATE_FUNC_NAME, GenerateFuncName_str)
    if InputParams_str:
        line = line.replace(TEMPLATE_INPUT_PARAMS, InputParams_str)
    if JsonPath_str:
        line = line.replace(TEMPLATE_JSONPATH, JsonPath_str)
        
    return line


def create_hpp(testsuuite_name, out_hppfile):
    global FileName_str
    global GuardName_str
    global TestSuiteName_str
    
    FileName_str = os.path.basename(out_hppfile)
    GuardName_str = FileName_str.replace('.', '_').upper()
    TestSuiteName_str = testsuite_name
    
    buf = []
    with open(HEADER_TEMPLATE_FILE, 'r') as f:
        buf = f.readlines()

    with open(out_hppfile, 'w') as f:
        for line in buf:
            line = replace_template_string(line)
            f.write(line)


def write_testcase_body(outf, inputfile):
    global TestCaseName_str
    global InputParams_str
    TestCaseName_str = 'Test_' + \
                       os.path.basename(inputfile).replace('.txt', '')

    # read input file
    input_buf = []
    with open(inputfile) as f:
        input_buf = f.readlines()

    # read test case body template
    body_buf = []
    with open(TEST_CASE_BODY_TEMPLATE_FILE) as f:
        body_buf = f.readlines()

    # read test item request On template
    reqOn_buf = []
    with open(TEST_ITEM_REQ_ON_TEMPLATE_FILE) as f:
        reqOn_buf = f.readlines()

    # read test item request Off template
    reqOff_buf = []
    with open(TEST_ITEM_REQ_OFF_TEMPLATE_FILE) as f:
        reqOff_buf = f.readlines()

    # read test item scene On template
    sceneOn_buf = []
    with open(TEST_ITEM_SCENE_ON_TEMPLATE_FILE) as f:
        sceneOn_buf = f.readlines()

    # read test item scene Off template
    sceneOff_buf = []
    with open(TEST_ITEM_SCENE_OFF_TEMPLATE_FILE) as f:
        sceneOff_buf = f.readlines()

    # read test item execute template
    exec_buf = []
    with open(TEST_ITEM_EXECUTE_TEMPLATE_FILE) as f:
        exec_buf = f.readlines()

    # read test item Assert Visible template
    astVis_buf = []
    with open(TEST_ITEM_ASSERT_VISIBLE_TEMPLATE_FILE) as f:
        astVis_buf = f.readlines()

    # read test item Assert Invisible template
    astInv_buf = []
    with open(TEST_ITEM_ASSERT_INVISIBLE_TEMPLATE_FILE) as f:
        astInv_buf = f.readlines()

    # read test item Asset Cancel True template
    astCancelTrue_buf = []
    with open(TEST_ITEM_ASSERT_CANCEL_TRUE_TEMPLATE_FILE) as f:
        astCancelTrue_buf = f.readlines()
    
    # read test item Asset Cancel False template
    astCancelFalse_buf = []
    with open(TEST_ITEM_ASSERT_CANCEL_FALSE_TEMPLATE_FILE) as f:
        astCancelFalse_buf = f.readlines()
    
    # write
    for line in body_buf:
        line = replace_template_string(line)
        if TEMPLATE_TEST_ITEM_BODY in line:
            for inpline in input_buf:
                buf = []
                params = inpline.strip().split(',')
                if params[0] == 'C':
                    if params[1] == 'ON':
                        buf = reqOn_buf
                    else:
                        buf = reqOff_buf                     
                elif params[0] == 'S':
                    if params[1] == 'ON':
                        buf = sceneOn_buf
                    else:
                        buf = sceneOff_buf
                elif params[0] == 'execute':
                    #buf = exec_buf
                    buf = ""
                elif params[0] == 'Assert':
                    if params[1] == 'A':
                        if params[-1] == 'NULL':
                            buf = astInv_buf
                        else:
                            buf = astVis_buf
                    elif params[1] == 'CANCEL':
                        if params[-1] == 'true':
                            buf = astCancelTrue_buf
                        else:
                            buf = astCancelFalse_buf
                else:
                    continue

                for ll in buf:
                    InputParams_str = '"'+'","'.join(params)+'"'
                    ll = replace_template_string(ll)
                    outf.write(ll)
                outf.write('\n')
        else:
            outf.write(line)


def create_cpp(model_name, testsuite_name, out_cpp_file, inputfiles):
    global FileName_str
    global HeaderFileName_str
    global GenerateFuncName_str
    global JsonPath_str

    FileName_str = testsuite_name + '.cpp'
    HeaderFileName_str = testsuite_name + '.hpp'
    GenerateFuncName_str = 'gen' + model_name
    JsonPath_str = 'gen/src/' + testsuite_name + '.json'

    # read cpp body template fule
    body_buf = []
    with open(BODY_TEMPLATE_FILE,'r') as f:
        body_buf = f.readlines()

    with open(out_cpp_file, 'w') as f:
        for line in body_buf:
            line = replace_template_string(line)
            # write testcase body
            if TEMPLATE_TEST_CASE_BODY in line:
                for fname in inputfiles:
                    write_testcase_body(f, fname)
            else:
                f.write(line)

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print('Usage: python3 %s <model_name> <output_dir> <inputfile> [<inputfile>...]' % sys.argv[0])
        exit()

    model_name = sys.argv[1]
    testsuite_name = 'Test'+model_name
    output_dir = sys.argv[2]
    inputfiles = sys.argv[3:]

    create_hpp(testsuite_name,
               os.path.join(output_dir, testsuite_name+'.hpp'))

    create_cpp(model_name, testsuite_name,
               os.path.join(output_dir, testsuite_name+'.cpp'),
               inputfiles)

# end of file
