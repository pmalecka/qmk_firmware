SRC += pm.c \
       process_records.c

ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tap_dances.c
endif

EXTRAFLAGS += -flto

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += rgb_stuff.c
  ifeq ($(strip $(RGBLIGHT_NOEEPROM)), yes)
    OPT_DEFS += -DRGBLIGHT_NOEEPROM
  endif
endif

ifdef CONSOLE_ENABLE
  ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
    OPT_DEFS += -DKEYLOGGER_ENABLE
  endif
endif

ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
    OPT_DEFS += -DMAKE_BOOTLOADER
endif
