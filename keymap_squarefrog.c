#include <util/delay.h>
#include "bootloader.h"
#include "keymap_common.h"
#include "action_layer.h"
#include "print.h"
#include "ergodox.h"

void show_layer_led(uint32_t layer)
{
    ergodox_led_all_off();

    switch (layer) {
        case 1 << 1:
            ergodox_right_led_1_on();
            break;
        case 1 << 2:
            ergodox_right_led_2_on();
            break;
        case 1 << 3:
            ergodox_right_led_3_on();
            break;
        case 1 << 4:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }
}

void hook_layer_change(uint32_t layer_state)
{
    switch (layer_state) {
        case 1:
            show_layer_led(default_layer_state);
            break;
        default:
            show_layer_led(layer_state);
            break;
    }
    xprintf("Layer changed: %032lb\n", layer_state);
    xprintf("STORED Default layer set: %032lb\n", default_layer_state);
}

void hook_default_layer_change(uint32_t layer_state)
{
    show_layer_led(default_layer_state);
    xprintf("Default layer set: %032lb\n", layer_state);
}

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * This is my current layout which serves dual purpose. The default layer is a standard QWERTY
     * layout with easy access to brackets, when coding for Objective-C. There is also a layout
     * that is geared more towards gaming so most of the more important keys reside on the left
     * hand. Additionally, there is a helper layout which provides Vim-like access to arrow keys.
     *
     * Layer 0: The basic keyboard, geared towards an OS X compliant layout.
     * Layer 1: Similar to L1, except using a Colemak layout
     * Layer 2: Arrow keys, function keys, helper functions for Xcode, Photoshop etc.
     * Layer 3: Gaming specific layout, for use in Windows.
     *
     * Keymap 0: Default Qwerty Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  Esc   |   1  |   2  |   3  |   4  |   5  |  ~   |           |  -   |   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  Tab   |   Q  |   W  |   E  |   R  |   Y  |  [   |           |  ]   |   Y  |   U  |   I  |   O  |   P  |   \    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------| +L1  |           |      |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LCtrl| LAlt | LGui | Vol- | Vol+ |                                       |   "  |   :  | RGui | RAlt | RCtrl |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |CpsLck| Del  |       | PgUp | PgDn |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | LAlt |       | RAlt |      |      |
     *                                 | BkSp | ~L2  |------|       |------| Enter| Space|
     *                                 |      |      | LGui |       | RGui |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(
        // left hand
        ESC,   1,   2,   3,    4,   5,   GRV,
        TAB,   Q,   W,   E,    R,   T,   LBRC,
        LCTL,  A,   S,   D,    F,   G,
        LSFT,  Z,   X,   C,    V,   B,   FN1,
        LCTL, LALT,LGUI, VOLD, VOLU,
                                      CAPS, DEL,
                                            LALT,
                                 BSPC,FN12, LGUI,
        // right hand
           MINS,  6,   7,    8,   9,   0,   EQL,
           RBRC,  Y,   U,    I,   O,   P,   BSLS,
                  H,   J,    K,   L,  SCLN, QUOT,
           NO,    N,   M,   COMM, DOT, SLSH, RSFT,
                       FN22,FN23, RGUI,RALT, RCTL,
        PGUP,PGDN,
        RALT,
        RGUI, ENT, SPC
    ),

    /*
     * Keymap 1: Default Colemak Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  Esc   |   1  |   2  |   3  |   4  |   5  |  ~   |           |  -   |   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  Tab   |   Q  |   W  |   F  |   P  |   G  |  [   |           |  ]   |   J  |   L  |   U  |   Y  |   ;  |   \    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LCtrl  |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |   '    |
     * |--------+------+------+------+------+------| +L3  |           | -L0  |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |   /  | RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LCtrl| LAlt | LGui | Vol- | Vol+ |                                       |   "  |   :  | RGui | RAlt | RCtrl |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |CpsLck| Del  |       | PgUp | PgDn |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | LAlt |       | RAlt |      |      |
     *                                 | BkSp | ~L2  |------|       |------| Enter| Space|
     *                                 |      |      | LGui |       | RGui |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(
        // left hand
        ESC,   1,   2,   3,    4,   5,   GRV,
        TAB,   Q,   W,   F,    P,   G,   LBRC,
        LCTL,  A,   R,   S,    T,   D,
        LSFT,  Z,   X,   C,    V,   B,   FN3,
        LCTL, LALT,LGUI, VOLD, VOLU,
                                      CAPS, DEL,
                                            LALT,
                                 BSPC,FN12, LGUI,
        // right hand
           MINS,  6,   7,    8,   9,   0,   EQL,
           RBRC,  J,   L,    U,   Y,  SCLN, BSLS,
                  H,   N,    E,   I,   O,   QUOT,
           FN0,   K,   M,   COMM, DOT, SLSH, RSFT,
                       FN22,FN23, RGUI,RALT, RCTL,
        PGUP,PGDN,
        RALT,
        RGUI, ENT, SPC
    ),
    /*
     * Layer 2: Helper functions
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | Teensy |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      | FN25 |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | CapsLk |      |      |      |      | FN26 |------|           |------| Left | Down |  Up  | Right|      |        |
     * |--------+------+------+------+------+------| +L3  |           | -L1  |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      | Mute |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      | Play |  RW  |  FF  |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(
        // left hand
        FN31, F1,  F2,  F3,  F4,  F5,  F11,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        CAPS,TRNS,TRNS,TRNS,TRNS,FN26,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, FN3,
        TRNS,TRNS,MPLY,MRWD,MFFD,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F12, F6,  F7,  F8,  F9,  F10, TRNS,
             TRNS,TRNS,FN25,TRNS,TRNS,TRNS,TRNS,
                  LEFT,DOWN,UP,  RGHT,TRNS,TRNS,
             FN1, TRNS,MUTE,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    /*
     * Keymap 3: Gaming Layer (Windows)
     * Notes:
     *   - Left shift is a toggle. Hold for normal shift, double tap to hold down until tapped again
     *   - FN20: Shadow play - save last X minutes
     *   - FN21: Shadow play - toggle recording
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  Esc   |   1  |   2  |   3  |   4  |   5  | FN20 |           |  -   |   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |  Tab   |   Q  |   W  |   E  |   R  |   T  | FN21 |           |  ]   |   Y  |   U  |   I  |   O  |   P  |   \    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------| FN28 |           |  L0  |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |  (~) |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | LCtrl| LAlt | LGui |      |      |                                       |      |      | RAlt | RGui | RCtrl |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  gg  |  F12 |       | PgUp | PgDn |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       | RAlt |      |      |
     *                                 | Space| Enter|------|       |------| Enter| BkSp |
     *                                 |      |      |  ~L1 |       | RGui |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(
        // left hand
        ESC,   1,   2,   3,   4,   5,  FN20,
        TAB,   Q,   W,   E,   R,   T,  FN21,
        LCTL,  A,   S,   D,   F,   G,
        FN27,  Z,   X,   C,   V,   B,  NO,
        LCTL,LALT,LGUI, NO,  NO,
                                       FN24,F12,
                                            NO,
                                  SPC, ENT,FN11,
        // right hand
           MINS,  6,   7,    8,   9,   0,   EQL,
           RBRC,  Y,   U,    I,   O,   P,   BSLS,
                  H,   J,    K,   L,  SCLN, QUOT,
           FN0,   N,   M,  COMM, DOT, SLSH, RSFT,
                       NO,   NO, RALT,RGUI, RCTL,
        PGUP,PGDN,
        RALT,
        RGUI, ENT, BSPC
    ),

    /*
     * Layer X: Template
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */
    /*
    KEYMAP(
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    */
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

enum macro_id {
    GOOD_GAME,
};

/*
 * Fn action definition - 32 Fn can be defined at most
 */
const uint16_t PROGMEM fn_actions[] = {
    // Layer shifting
    [0] = ACTION_DEFAULT_LAYER_SET(0),             // Switch to Layer 0
    [1] = ACTION_DEFAULT_LAYER_SET(1),             // Switch to Layer 1
    [2] = ACTION_DEFAULT_LAYER_SET(2),             // Switch to Layer 2
    [3] = ACTION_DEFAULT_LAYER_SET(3),             // Switch to Layer 3

    // Layer toggling
    [12] = ACTION_LAYER_MOMENTARY(2),              // Push Layer 2

    // Short modifier shortcuts
    [20] = ACTION_MODS_KEY(MOD_LALT, KC_F10),      // Shadow play: save last X minutes
    [21] = ACTION_MODS_KEY(MOD_LALT, KC_F9),       // Shadow play: toggle manual recording
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_QUOT),     // Shift+' - "
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_SCLN),     // Shift+; - :
    [24] = ACTION_MACRO(GOOD_GAME),                // Macro: say `gg`
    [25] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_U), // Test class: ctrl+alt+cmd+u
    [26] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_G), // Test class again: ctrl+alt+cmd+g
    [27] = ACTION_MODS_TAP_TOGGLE(MOD_LSFT),       // Toggle left shift
    [28] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),     // Shift+` = ~

    // Teensy
    [31] = ACTION_FUNCTION(TEENSY_KEY),            // Teensy key
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case GOOD_GAME:
            return (record->event.pressed ?
                    MACRO( I(100), T(T), T(G), T(G), T(ENT), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}

/*
 * User defined action function
 */
void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

