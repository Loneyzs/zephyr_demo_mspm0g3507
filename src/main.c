#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 获取设备树中 led0 别名的信息 */
#define LED0_NODE DT_ALIAS(led0)

/* 初始化 GPIO 结构体 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;

	/* 检查设备驱动是否就绪 */
	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	/* 配置 GPIO 引脚为输出，并根据 DTS 初始化电平 */
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		/* 翻转 LED 电平 */
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		/* 延时 500 毫秒 (0.5s) */
		k_msleep(500);
	}

	return 0;
}