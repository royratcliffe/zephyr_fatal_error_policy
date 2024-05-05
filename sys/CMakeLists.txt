# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

add_subdirectory_ifdef(CONFIG_SYS_FATAL_ERROR fatal_error)
zephyr_include_directories_ifdef(CONFIG_SYS_FATAL_ERROR include)
