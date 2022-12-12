# Is Led Still working?

How to ensure that the LED is still working?

The are few possibilities to check it. But if you have an ADC available on the same pin as the
LED is connected, you may take advantage of the GPIO internal RDS_on resistance and calculate
the threshold on which the LED is currently emitting light or not.
