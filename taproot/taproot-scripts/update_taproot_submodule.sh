#!/bin/bash
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

if [[ "$#" -ne 3 ]]; then
    echo "usage: update_taproot_submodule.sh ./path-to-project-dir gitlab-project-id branch-to-target"
    exit 1
fi

ARUW_MCB_PROJECT_PATH=$1
GITLAB_PROJECT_ID=$2
BRANCH_TO_TARGET=$3
UPDATE_SUBMODULE_BRANCH="update-submodule"

git fetch
git checkout $BRANCH_TO_TARGET
git pull
git submodule foreach git checkout $BRANCH_TO_TARGET
git checkout $UPDATE_SUBMODULE_BRANCH
git reset --hard origin/$BRANCH_TO_TARGET

cd $ARUW_MCB_PROJECT_PATH
rm -rf taproot
lbuild build >/dev/null
cd -

if [[ "$(git status | grep -c "nothing to commit")" != 1 ]]; then
    echo "Files have changed..."
    git status
    git add --all
    git commit -m "Update taproot submodule"
    (git push -f &>/dev/null) || (git push --set-upstream origin $UPDATE_SUBMODULE_BRANCH)

    # The description of our new MR, we want to remove the branch after the MR has
    # been closed
    BODY="{
        \"id\": $GITLAB_PROJECT_ID,
        \"source_branch\": \"$UPDATE_SUBMODULE_BRANCH\",
        \"target_branch\": \"$BRANCH_TO_TARGET\",
        \"remove_source_branch\": false,
        \"title\": \"CI Submodule Update\"
    }"

    API4_MR_URL="https://gitlab.com/api/v4/projects/$GITLAB_PROJECT_ID/merge_requests"
    LISTMR=`curl --silent "$API4_MR_URL?state=opened" --header "PRIVATE-TOKEN: $PRIVATE_TOKEN"`
    COUNTBRANCHES=`echo $LISTMR | grep -o "\"source_branch\":\"$UPDATE_SUBMODULE_BRANCH\"" | wc -l`

    if [[ $COUNTBRANCHES -eq "0" ]]; then
        curl -X POST "$API4_MR_URL" \
            --header "PRIVATE-TOKEN: $PRIVATE_TOKEN" \
            --header "Content-Type: application/json" \
            --data "$BODY" >/dev/null
        echo "Opened submodule update MR"
    else
        echo "MR already opened, changes pushed"
    fi
else
    echo "No updates, no MR opened"
fi
