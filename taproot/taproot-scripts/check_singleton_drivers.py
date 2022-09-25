#!/usr/bin/env python3
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
import os
import sys

SOURCE_FILE_EXTENSIONS = ['.cpp', '.hpp', '.h']

def parse_args():
    arg = argparse.ArgumentParser(
        description='Script that validates the singleton driver is only used in a few very\
            specific files. Instead of using the singleton driver directly, it is expected\
            that the user passes around pointer/references to the singleton driver to enable\
            unit testing.')
    arg.add_argument(
        'singleton_driver_name',
        type=str,
        help='The name of the function that provides direct access to the singleton driver instance')
    arg.add_argument(
        '-p', '--project-directory',
        type=str,
        required=True,
        help='The directory to search through when checking for the singleton driver instance name')
    arg.add_argument(
        '-w', '--whitelisted-files',
        nargs='*',
        type=str,
        required=False,
        default=[],
        help='Any files to whitelist, relative to the passed in project directory (specified\
            via -p flag) your current directory')
    return arg.parse_args()

def is_source_file_to_check(file, ignored_files):
    if file in ignored_files:
        return False

    _, file_extension = os.path.splitext(file)
    return file_extension in SOURCE_FILE_EXTENSIONS

def check_file(file, string_to_check):
    '''
    Checks if 'file' contains 'string_to_check' and returns true if it does.
    '''
    with open(file, 'r') as file_to_check:
        if string_to_check in file_to_check.read():
            print(f'{file} contains the function call {string_to_check}')
            return True
    return False

def main():
    args = parse_args()

    # Add on the project_path to all files in files_to_whitelist
    files_to_whitelist = [ os.path.join(args.project_directory, f) for f in args.whitelisted_files ]

    # Find all files in the project_directory
    files_to_search = [ os.path.join(dp, f) for dp, dn, filenames in os.walk(args.project_directory) for f in filenames ]

    # Iterate through all files, checking for the 'string_to_check'
    result = 0
    for file in files_to_search:
        if is_source_file_to_check(file, files_to_whitelist):
            result = check_file(file, args.singleton_driver_name) or result

    sys.exit(result)

if __name__ == '__main__':
    main()
