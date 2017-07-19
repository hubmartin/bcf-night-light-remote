
#include <application.h>

bc_led_t led;
bc_button_t button;

void button_event_handler(bc_button_t *self, bc_button_event_t event, void *param)
{
	(void) self;
	(void) param;

	if (event == BC_BUTTON_EVENT_CLICK)
	{
          uint16_t event_counter = (uint16_t)event;
          bc_led_pulse(&led, 10);
          bc_radio_pub_push_button(&event_counter);
	}
  else if (event == BC_BUTTON_EVENT_HOLD)
  {
      bc_radio_enroll_to_gateway();
      bc_led_pulse(&led, 1000);
  }

}

void application_init(void)
{
	bc_radio_init();

	bc_led_init(&led, BC_GPIO_LED, false, false);

	bc_button_init(&button, BC_GPIO_BUTTON, BC_GPIO_PULL_DOWN, false);
	bc_button_set_hold_time(&button, 500);
	bc_button_set_event_handler(&button, button_event_handler, NULL);
}
