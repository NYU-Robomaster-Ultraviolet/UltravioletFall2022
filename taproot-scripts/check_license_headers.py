#!/usr/bin/python3
#
# Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
#
# This file is part of Taproot.
#
# Taproot is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Taproot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Taproot.  If not, see <https://www.gnu.org/licenses/>.

import argparse
from os.path import splitext
import sys
import os
import glob

CPP_LICENSED_SOURCE_FILE_EXTENSIONS = ['.cpp', '.hpp', '.h', '.hpp.in', '.cpp.in']
def getCppLicenseHeader(project_name):
    return f'/*\n\
 *\n\
 *\n\
 * This file is part of {project_name}.\n\
 *\n\
 * {project_name} is free software: you can redistribute it and/or modify\n\
 * it under the terms of the GNU General Public License as published by\n\
 * the Free Software Foundation, either version 3 of the License, or\n\
 * (at your option) any later version.\n\
 *\n\
 * {project_name} is distributed in the hope that it will be useful,\n\
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
 * GNU General Public License for more details.\n\
 *\n\
 * You should have received a copy of the GNU General Public License\n\
 * along with {project_name}.  If not, see <https://www.gnu.org/licenses/>.\n\
 */\n'

SCRIPT_LICENSED_SOURCE_FILE_EXTENSIONS = ['.lb', '.py', '.sh', '.yml', '.py.in']
def getScriptLicenseHeader(project_name):
    return f'#\n\
#\n\
# This file is part of {project_name}.\n\
#\n\
# {project_name} is free software: you can redistribute it and/or modify\n\
# it under the terms of the GNU General Public License as published by\n\
# the Free Software Foundation, either version 3 of the License, or\n\
# (at your option) any later version.\n\
#\n\
# {project_name} is distributed in the hope that it will be useful,\n\
# but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
# GNU General Public License for more details.\n\
#\n\
# You should have received a copy of the GNU General Public License\n\
# along with {project_name}.  If not, see <https://www.gnu.org/licenses/>.\n'
COPYRIGHT = "Copyright (c)"
SHEBANG = "!"

def find_files_to_check(ignored_files):
    file_types_to_check = CPP_LICENSED_SOURCE_FILE_EXTENSIONS + SCRIPT_LICENSED_SOURCE_FILE_EXTENSIONS

    files_to_check = []
    for file_type in file_types_to_check:
        files_to_check.extend([os.path.normpath(path) for path in glob.glob('./**/*{}'.format(file_type), recursive=True)])

    files_to_ignore = []
    for file_glob in ignored_files:
        files_to_ignore.extend([os.path.normpath(path) for path in glob.glob(file_glob, recursive=True)])

    def excluded(file):
        return file in files_to_ignore

    return list(filter(lambda p: not excluded(p), files_to_check))

def is_licensed_source_file(file, file_extensions):
    _, file_extension = splitext(file)
    return file_extension in file_extensions

def file_has_valid_license_header(file, expected_header, copyright_line, author):
    with open(file, 'r') as file_to_check:
        license_lines = expected_header.splitlines()
        num_lines = len(license_lines)
        license_lines_to_check = file_to_check.read().splitlines()
        # shebang lines may appear at the top of the file; skip over these
        offset = 0
        while SHEBANG in license_lines_to_check[offset]:
            offset += 1
        # accomodate for one blank line after shebang lines, if any
        if offset != 0:
            offset += 1
        # check before copyright line
        if license_lines_to_check[offset:offset + copyright_line] != license_lines[0:copyright_line]:
            return False
        # check after copyright line
        if license_lines_to_check[offset + copyright_line + 1:offset + num_lines] != license_lines[copyright_line + 1:]:
            return False
        # check copyright line
        if COPYRIGHT not in license_lines_to_check[offset + copyright_line] or author not in license_lines_to_check[offset + copyright_line]:
            return False
    return True

def add_license_to_file(file, header):
    print("Adding license to {0}".format(file))
    with open(file, 'r+') as file_to_check:
        content = file_to_check.read()
        file_to_check.seek(0, 0)
        file_to_check.write(header.rstrip('\r\n') + '\n' + content)

def parse_args():
    arg = argparse.ArgumentParser(
        description="Checks that all files in the repository that require it\
            have a valid header file (using the GNU-GPL license header). It\
            is expected that you run this script at the root of whatever\
            directory you want to check license headers in. License headers\
            will be checked recursively in all directories aside from the\
            ignored directories passed in to the script.")
    arg.add_argument(
        '-p', '--project-name',
        type=str,
        required=True,
        help="Name of the the project that will be listed in all license headers")
    arg.add_argument(
        '-o', '--project-owner',
        type=str,
        required=True,
        help="Name of the project owner")
    arg.add_argument(
        '-u', '--update',
        action='store_true',
        default=False)
    arg.add_argument(
        '-i', '--ignored',
        type=str,
        nargs="*",
        default=[],
        help='Files/directories to ignore, in glob format (when using glob format\
            it is usually necessary to quote arguments to avoid the shell expanding the glob.')
    return arg.parse_args()

def main():
    args = parse_args()

    files_to_check = find_files_to_check(args.ignored)

    cppLicenseHeader = getCppLicenseHeader(args.project_name)
    scriptLicenseHeader = getScriptLicenseHeader(args.project_name)

    result = False
    for file in files_to_check:
        if is_licensed_source_file(file, CPP_LICENSED_SOURCE_FILE_EXTENSIONS):
            if not file_has_valid_license_header(file, cppLicenseHeader, 1, args.project_owner):
                result = True
                print("{0} does not contain a license header".format(file))
                if args.update:
                    add_license_to_file(file, cppLicenseHeader)
        elif is_licensed_source_file(file, SCRIPT_LICENSED_SOURCE_FILE_EXTENSIONS):
            if not file_has_valid_license_header(file, scriptLicenseHeader, 0, args.project_owner):
                result = True
                print("{0} does not contain a license header".format(file))
                if args.update:
                    add_license_to_file(file, scriptLicenseHeader)

    sys.exit(result)

if __name__ == '__main__':
    main()
