#!/usr/bin/env python3

import sys
import urllib
import xml.etree.ElementTree as ET

def get_tests(elem):
    return int(elem.attrib['tests'])

def get_failures(elem):
    return int(elem.attrib['failures'])

def analyze_xml(filename):
    tree = ET.parse(filename)
    root = tree.getroot()
    all_test_num = get_tests(root)
    all_failure_num = get_failures(root)
    all_pass_num = all_test_num - all_failure_num
    print('all,%d,%d,%d' %
          (all_test_num, all_pass_num, all_failure_num))
    for testsuite in root:
        test_num = get_tests(testsuite)
        failure_num = get_failures(testsuite)
        pass_num = test_num - failure_num
        print('%s,%d,%d,%d' %
              (testsuite.attrib['name'], test_num, pass_num, failure_num))
            
if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: %s <xmlfile>' % sys.argv[0])
        exit()

    filename = sys.argv[1]

    print('"name","total","pass","failure"')
    analyze_xml(filename)

# end of file
