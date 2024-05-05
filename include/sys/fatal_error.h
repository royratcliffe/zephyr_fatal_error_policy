/*
 * Copyright (c) 2024 Roy Ratcliffe
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef SYS_FATAL_ERROR_H__
#define SYS_FATAL_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>

struct sys_fatal_error {
  void (*handler)();
};

#define SYS_FATAL_ERROR_DEFINE(_name)                                          \
  static const STRUCT_SECTION_ITERABLE(sys_fatal_error,                        \
                                       _CONCAT(sys_fatal_error_, _name))

#ifdef __cplusplus
}
#endif

#endif /* SYS_FATAL_ERROR_H__ */
