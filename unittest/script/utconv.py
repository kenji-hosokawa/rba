#/usr/bin/env python3

import sys
import re

def conv(lines):
    flagFactory = False
    for line in lines:
        line = line.rstrip()
        if '#include "Test' in line:
            print('#include "RBAModelFactory.hpp"')
            print('#include "RBAAreaImpl.hpp"')
            print('#include "RBAContentImpl.hpp"')
            print(line)
        elif re.match(r'^int gen', line):
            flagFactory = True
            line = line.replace('RBAModel* model', '').replace('int ', 'RBAModel* ')
            print(line)
        elif 'return 0' in line:
            line = line.replace('return 0', 'return model')
            print(line)
        elif '{' in line and flagFactory:
            print(line)
            print('        RBAModelFactory f;')
            print('        RBAModel* model = f.createModel();')
            flagFactory = False
        elif 'model = new rba::RBAModel();' in line:
            continue
        elif re.match(r'  gen.*\(model\);', line):
            line = line.replace('model', '').replace('gen', 'model = gen')
            print(line)
        elif 'model->' in line:
            line = line.replace('model->', 'f.');
            print(line)
        else:
            print(line)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python3 %s <filename>' % sys.argv[0])
        exit()

    filename = sys.argv[1]
    lines = []
    with open(filename) as f:
        lines = f.readlines()
        conv(lines)
    
# end of file
