USB_VID = 0x303A
USB_PID = 0x8114
USB_PRODUCT = "Bee-Motion-S3"
USB_MANUFACTURER = "Smart Bee Designs"

IDF_TARGET = esp32s3

CIRCUITPY_ESP_FLASH_MODE = dio
CIRCUITPY_ESP_FLASH_FREQ = 80m
CIRCUITPY_ESP_FLASH_SIZE = 8MB


FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_NeoPixel
CIRCUITPY_ESP32_CAMERA = 0
