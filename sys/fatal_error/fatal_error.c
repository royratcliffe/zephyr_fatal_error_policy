#include <zephyr/arch/cpu.h>
#include <zephyr/fatal.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <sys/fatal_error.h>

LOG_MODULE_REGISTER(fatal_error, CONFIG_SYS_FATAL_ERROR_LOG_LEVEL);

extern void sys_arch_reboot(int type);

void k_sys_fatal_error_handler(unsigned int reason, const z_arch_esf_t *esf) {
  ARG_UNUSED(reason);
  ARG_UNUSED(esf);

  STRUCT_SECTION_FOREACH(sys_fatal_error, each) { (each->handler)(); }

  LOG_PANIC();

  if (IS_ENABLED(CONFIG_RESET_ON_FATAL_ERROR)) {
    LOG_ERR("Resetting system");
    sys_arch_reboot(0);
  } else {
    LOG_ERR("Halting system");
    for (;;) {
    }
  }

  CODE_UNREACHABLE;
}
