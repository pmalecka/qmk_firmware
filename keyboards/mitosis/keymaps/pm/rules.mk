MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes

ifeq (${TAP_DANCE_ENABLE},yes)
SRC += tap_dance_extra.c
endif
