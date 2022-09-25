#! /usr/bin/python3
#
# Copyright (c) 2022 Advanced Robotics at the University of Washington <robomstr@uw.edu>
#
# This file is part of taproot-scripts.
#
# taproot-scripts is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# taproot-scripts is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with taproot-scripts.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import xml.etree.ElementTree
import re

def parse_args():
    arg = argparse.ArgumentParser(
        description='Script that increments or decrements all line number references\
        in a cobertura.xml file. This is required if coverage results are to prove\
        useful in the case where some automated process has prepended some lines to\
        the start of all files.')
    arg.add_argument(
        '--in-file',
        required=False,
        default='cobertura.xml',
        help='input cobertura file')
    arg.add_argument(
        '--out-file',
        required=False,
        default='cobertura-modified.xml',
        help='output cobertura file')
    arg.add_argument(
        '--shift-lines',
        required=True,
        type=int,
        help='number of lines to shift the all files by in the cobertura.xml file')
    arg.add_argument(
        '--package-names',
        required=True,
        help='cobertura package to apply line offsets to, a regex string')
    return arg.parse_args()

def main():
    args = parse_args()

    tree = xml.etree.ElementTree.parse(args.in_file)
    packages_root = tree.getroot()[1]

    package_name_matcher = re.compile(args.package_names)

    for package in packages_root:
        name = package.attrib['name']

        name_matches = package_name_matcher.match(name) is not None

        if name_matches:
            for line_number in package.iter('line'):
                line_number.set('number', str(int(line_number.get('number')) + args.shift_lines))
    
    tree.write(args.out_file)

if __name__ == '__main__':
    main()
