# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

zephyr_include_directories_ifdef(CONFIG_SYS_FATAL_ERROR ../../include)
zephyr_sources_ifdef(CONFIG_SYS_FATAL_ERROR fatal_error.c)
zephyr_linker_sources(SECTIONS sys_fatal_error.ld)
