#!/usr/bin/env python3

"""
Raspberry Pi 4B, A4988 stepper driver, Kysan 1124090 stepper motor.
"""

import RPi.GPIO as GPIO
from time import sleep

PULSE_DURATION_US = 100

STEP_PIN = 22
DIR_PIN = 29
MS3_PIN = 18
MS2_PIN = 16
MS1_PIN = 13

PULSE_DURATION_S = PULSE_DURATION_US / 1000000.0

RESOLUTION = {
    'full': (GPIO.LOW, GPIO.LOW, GPIO.LOW),
    'half': (GPIO.HIGH, GPIO.LOW, GPIO.LOW),
    'quarter': (GPIO.LOW, GPIO.HIGH, GPIO.LOW),
    'eighth': (GPIO.HIGH, GPIO.HIGH, GPIO.LOW),
    'sixteenth': (GPIO.HIGH, GPIO.HIGH, GPIO.HIGH)
}


def step(step_pin, dir_pin, dir, steps_per_s, steps, resolution):
    s_per_step = 1.0 / steps_per_s
    inter_pulse_s = s_per_step - PULSE_DURATION_S

    dir_value = GPIO.HIGH if dir == 'CW' else GPIO.LOW
    GPIO.output(dir_pin, dir_value)

    GPIO.output((MS1_PIN, MS2_PIN, MS3_PIN), resolution)

    while steps > 0:
        GPIO.output(step_pin, GPIO.HIGH)
        sleep(PULSE_DURATION_S)
        GPIO.output(step_pin, GPIO.LOW)
        sleep(inter_pulse_s)
        steps = steps - 1


def setup(step_pin, dir_pin, ms1_pin, ms2_pin, ms3_pin):
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(step_pin, GPIO.OUT)
    GPIO.setup(dir_pin, GPIO.OUT)
    GPIO.setup(ms1_pin, GPIO.OUT)
    GPIO.setup(ms2_pin, GPIO.OUT)
    GPIO.setup(ms3_pin, GPIO.OUT)
    GPIO.output(dir_pin, GPIO.HIGH)

    GPIO.output((ms1_pin, ms2_pin, ms3_pin), RESOLUTION['full'])


print(
    f'STEP_PIN: {STEP_PIN}'
    f', DIR_PIN: {DIR_PIN}'
    f', PULSE_DURATION_US: {PULSE_DURATION_US}'
)

setup(STEP_PIN, DIR_PIN, MS1_PIN, MS2_PIN, MS3_PIN)
step(STEP_PIN, DIR_PIN, 'CW', 200, 1000, RESOLUTION['full'])
sleep(2.0)
step(STEP_PIN, DIR_PIN, 'CW', 200, 1000, RESOLUTION['sixteenth'])

GPIO.cleanup()
