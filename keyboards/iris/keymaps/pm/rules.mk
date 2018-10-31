RGBLIGHT_ENABLE = no
BACKLIGHT_ENABLE = no
TAP_DANCE_ENABLE = yes
FORCE_NKRO = yes

ifeq (${FORCE_NKRO},yes)
OPT_DEFS += -DFORCE_NKRO
endif

ifeq (${TAP_DANCE_ENABLE},yes)
SRC += tap_dance_extra.c
endif
