#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <sys/fatal_error.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U) / 4U

/*!
 * \brief Calibrates a PWM channel.
 * Calibrate \e after checking for PWM ready.
 * Applies 50% duty cycle as the period during calibration.
 * \param[in] spec Devicetree PWM specification.
 * \returns Maximum calibrated period.
 */
uint32_t pwm_calibrate_max_period(const struct pwm_dt_spec *spec,
                                  uint32_t min_period, uint32_t max_period) {
  while (pwm_set_dt(spec, max_period, max_period >> 1U)) {
    max_period /= 2U;
    if (max_period < 4U * min_period)
      return 0U;
  }
  return max_period;
}

int main(void) {
  uint32_t max_period;
  int rc;

  if (!pwm_is_ready_dt(&pwm_led0)) {
    printk("Error: PWM device %s is not ready\n", pwm_led0.dev->name);
    return 0;
  }

  /* Determine the maximum period for the PWM driver.
   */
  max_period = pwm_calibrate_max_period(&pwm_led0, MIN_PERIOD, MAX_PERIOD);

  rc = pwm_set_dt(&pwm_led0, max_period, max_period / 2U);
  if (rc) {
    printk("Error %d: failed to set pulse width\n", rc);
    return 0;
  }

  k_sleep(K_SECONDS(2));
  k_oops();

  return 0;
}

void pwm_led0_off_fatal_error() {
  pwm_set_dt(&pwm_led0, 0, 0);
  LOG_INF("Switched off %s", pwm_led0.dev->name);
}

SYS_FATAL_ERROR_DEFINE(pwm_led0_off) = {.handler = pwm_led0_off_fatal_error};
