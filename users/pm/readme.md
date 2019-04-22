# Overview

This is my personal userspace file inspired (bluntly copied) by Drashna.  Most of my code exists here, as it's heavily shared.

## Custom userspace handlers

Specifically QMK works by using customized handlers for everything. This allows for multiple levels of customization.

`matrix_scan` calls `matrix_scan_quantum`, which alls `matrix_scan_kb`, which calls `matrix_scan_user`. 
`process_record` calls a bunch of stuff, but eventually calls `process_record_kb` which calls `process_record_user`
The same goes for `matrix_init`, `layer_state_set`, `led_set`, and a few other functions.  

All (most) `_user` functions are handled here instead.  To allow keyboard specific configuration, I've created `_keymap` functions that can be called by the keymap.c files instead.

This allows for keyboard specific configuration while maintaining the ability to customize the board.

My [Ergodox EZ Keymap](https://github.com/qmk/qmk_firmware/blob/master/layouts/community/ergodox/drashna/keymap.c#L297) is a good example of this, as it uses the LEDs as modifier indicators.


## Custom Keycodes

Keycodes are defined in the drashna.h file and need to be included in the keymap.c files, so that they can be used there. 

A bunch of macros are present and are only included on boards that are not the Ergodox EZ or Orthodox, as they are not needed for those boards. 

Included is a custom macro for compiling my keyboards.  This includes the bootloader target (`:teensy`, `:avrdude`, or `:dfu`), and keeps RGBLIGHT, AUDIO and/or FAUXCLICKY enabled, if it previously was (regardless of the rules file).

This also includes a modified RESET keycode as well, that sets the underglow to red.

## Layer Indication

This uses the `layer_state_set_*` command to change the layer color, to indicate which layer it is on.  This includes the default keymap, as well.

Since this is done via userspace, it is the same between all systems. 

Additionally, there is a custom keycode to toggle layer indication. And all RGB keycodes disable layer indication by default, as well.  This way, I can leave special effects doing when I want.

Also. I use `rgblight_sethsv` since it works with animation modes (that support it).

## Secret Macros

With help from gitter and Colinta, this adds the ability to add hidden macros from other users.  

First, I have several files that are hidden/excluded from Git/GitHub.  These contain everything needed for the macros. To hide these files, open `.git/info/exclude` and add `secrets.c` and  `secrets.h` to that file, below the comments.

And this requires `KC_SECRET_1` through `KC_SECRET_5` to be defined in your `<name>.h` file to define the keycodes for the new macros. 


### .git/info/exclude

```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/users/pm2/secrets.c
/users/pm2/secrets.h
```

Then you can create these files:

### secrets.h

```c
static const char * const secrets[] = {
  "secret1",
  "secret2",
  "secret3",
  "secret4",
  "secret5"
};
```

Replacing the strings with the codes that you need.

### name.c

In the `<name>.c` file, you will want to add this to the top:

```c
__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}
```
