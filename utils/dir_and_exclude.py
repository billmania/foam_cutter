#!/usr/bin/env python3

"""
Build the dir and exclude arguments for the hal_pi_gpio module.
Provide the collection of hal_pi_gpio pin names.

https://www.linuxcnc.org/docs/stable/html/drivers/hal_pi_gpio.html

Note: In the calculation of the individual pin’s mask value its GPIO
numbers are used, the value being derived as 2^(GPIO number - 2),
whereas in the naming of the HAL pins it is the Raspberry Pi header
pin numbers.

"""

GPIO_TO_PIN = {
    2: 3,
    3: 5,
    4: 7,
    5: 29,
    6: 31,
    7: 26,
    8: 24,
    9: 21,
    10: 19,
    11: 23,
    12: 32,
    13: 33,
    14: 8,
    15: 10,
    16: 36,
    17: 11,
    18: 12,
    19: 35,
    20: 38,
    21: 40,
    22: 15,
    23: 16,
    24: 18,
    25: 22,
    26: 37,
    27: 13
}


def get_hal_setup(gpio_outputs: list[int]):
    """
    gpio_outputs is a list of integers, which comprise the set
    of GPIO numbers (not board pin numbers)  which are to be used
    as outputs.
    The output of get_hal_setup includes three parts:
        1. the dir mask
        2. the exclude mask
        3. the list of hal_pi_gpio pin names
    """

    valid_GPIO = set(GPIO_TO_PIN.keys())
    print(f'GPIO outputs: {gpio_outputs}')

    #
    # First, make a set of the gpio_outputs and confirm they're
    # valid GPIO numbers.
    #
    gpio_set = set(gpio_outputs)
    not_gpio = gpio_set - valid_GPIO
    if (len(not_gpio) > 0):
        print(f'{not_gpio} are not valid GPIO numbers')
        return

    #
    # Calculate the dir and exclude mask for the set of GPIO outputs.
    #
    dir_sum = 0
    for output in gpio_set:
        dir_sum += (2 ** (output - 2))

    exclude_sum = 0
    for exclude in (valid_GPIO - gpio_set):
        exclude_sum += (2 ** (exclude - 2))

    print(f'dir={hex(dir_sum).upper()} exclude={hex(exclude_sum).upper()}')

    #
    # Generate the collection of hal_pi_gpio output pin names.
    #
    for gpio in gpio_set:
        print(f'hal_pi_gpio.pin-{GPIO_TO_PIN[gpio]:02d}-out # GPIO {gpio}')


get_hal_setup([17, 22, 23])
get_hal_setup([4, 24, 28])
get_hal_setup([4, 24, 24])
get_hal_setup([27, 4, 24])
