#!/usr/bin/python3
#
# Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
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
import sys

def parse_args():
    arg = argparse.ArgumentParser(
        description='Script that parses metrics from some file into a file that is\
            parsable by GitLab\'s metric parser')
    arg.add_argument(
        '-i', '--input-file',
        type=str,
        required=True,
        help='Input metric file containing info output from a call to \'scons size\'')
    arg.add_argument(
        '-o', '--output-file',
        type=str,
        required=True,
        help='Output file, formatting program size, data, and heap usage in a format\
            readable by GitLab\'s metric parser.')
    arg.add_argument(
        '--identifier',
        type=str,
        required=True,
        help='Identifier to separate out different build configurations, for example can be a target name')
    return arg.parse_args()

def main():
    args = parse_args()

    with open(args.input_file, 'r') as in_file:
        lines = in_file.readlines()
        with open(args.output_file, 'w') as out_file:
            for line in lines[-11:-2]:
                if 'Program:' in line:
                    words = line.split()
                    out_file.write(f'{args.identifier}_program_size [{words[1]}{words[2]},{words[3][1:]}]\n')
                if 'Data:' in line:
                    words = line.split()
                    out_file.write(f'{args.identifier}_data_usage [{words[1]}{words[2]},{words[3][1:]}]\n')
                if 'Heap:' in line:
                    words = line.split()
                    out_file.write(f'{args.identifier}_heap_usage [{words[1]}{words[2]},{round(100 - float(words[3][1:5]), 2)}%]\n')

if __name__ == '__main__':
    main()
