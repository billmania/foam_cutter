#!/usr/bin/env python3

"""
This script controlled the R stepper driver to enable/disable and
spin a stepper motor on 29 Aug 2024.

Bill's bench supply providing 3.3 VDC to EN+, DIR+, and PUL+
to stepper driver R.

board power supply providing 5.0 VDC to Rasp Pi.

board power supply providing 24.0 VDC to stepper driver.
"""

import RPi.GPIO as GPIO
from time import sleep

#
# GPIO pin numbers
#
ENABLE_PIN = 4
DIR_PIN = 24
PULSE_PIN = 25

ENABLE = GPIO.HIGH
DISABLE = GPIO.LOW
CW = GPIO.HIGH
CCW = GPIO.LOW

NANOSEC = 0.000000001
MICROSEC = 0.000001
MILLISEC = 0.001

GPIO.setmode(GPIO.BCM)
GPIO.setup(ENABLE_PIN, GPIO.OUT)
GPIO.setup(DIR_PIN, GPIO.OUT)
GPIO.setup(PULSE_PIN, GPIO.OUT)

steps = 10000
pulse_length = 10 * MICROSEC
pulse_space = MICROSEC

GPIO.output(ENABLE_PIN, ENABLE)

for dir in [CW, CCW]:
    GPIO.output(DIR_PIN, dir)

    steps = 10000
    while steps > 0:
        steps -= 1

        GPIO.output(PULSE_PIN, GPIO.LOW)
        sleep(pulse_length)
        GPIO.output(PULSE_PIN, GPIO.HIGH)
        sleep(pulse_space)

GPIO.output(ENABLE_PIN, DISABLE)
GPIO.cleanup()
