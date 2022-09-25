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

import platform

def generate(env, **kw):
    def _get_hosted_target_name_for_current_platform():
        os_type = platform.system()
        try:
            return {
                "Windows": "hosted-windows",
                "Darwin": "hosted-darwin",
                "Linux": "hosted-linux",
            }[os_type]
        except KeyError:
            raise ValueError(f"Unknown host OS {os_type}")

    def get_sim_modm_instance_path(env):
        return f"taproot/sim-modm/{_get_hosted_target_name_for_current_platform()}/modm"

    env.AddMethod(get_sim_modm_instance_path, "GetSimModmInstancePath")

def exists(env):
	return True
