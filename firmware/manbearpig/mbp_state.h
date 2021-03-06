/*****************************************************************************
 * (C) Copyright 2017 AND!XOR LLC (http://andnxor.com/).
 *
 * PROPRIETARY AND CONFIDENTIAL UNTIL AUGUST 1ST, 2017 then,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contributors:
 * 	@andnxor
 * 	@zappbrandnxor
 * 	@hyr0n1
 * 	@andrewnriley
 * 	@lacosteaef
 * 	@bitstr3m
 *****************************************************************************/
#ifndef MBP_BADGE_STATE_H_
#define MBP_BADGE_STATE_H_

typedef struct {
	uint8_t canary;
	char name[SETTING_NAME_LENGTH];
	bool airplane_mode_enabled;
	bool tilt_enabled;
	botnet_state_t botnet_state;
	bool game_exit_pop_up;
	bool game_led_sound;
	uint16_t chip8_fg_color;
	uint16_t chip8_bg_color;
	uint16_t unlock_state;
	bool master_badge;
	char pw_scruffy[9];
	char pw_root[9];
	bool c2_unlock;
	bool c2_points;
	bool c2_level;
	uint16_t wall_current_spot;
	char wall_messages[5][16];
} badge_state_t;

extern void mbp_state_wall_show();
extern void mbp_state_wall_put(char *msg);

extern bool mbp_state_load();
extern void mbp_state_new();
extern void mbp_state_save();

extern void mbp_state_pw_scruffy_set(char *pw);
extern void mbp_state_pw_scruffy_get(char *pw);
extern void mbp_state_pw_root_set(char *pw);
extern void mbp_state_pw_root_get(char *pw);

extern botnet_state_t *mbp_state_botnet_state_get();
extern void mbp_state_name_get(char *name);
extern void mbp_state_name_set(char *name);
extern bool mbp_state_game_exit_pop_up_get();
extern void mbp_state_game_exit_pop_up_set(bool b);
extern bool mbp_state_game_led_sound_get();
extern void mbp_state_game_led_sound_set(bool b);

//Activation state
extern bool mbp_state_activated_get();
extern void mbp_state_activated_set(bool activated);

//Get and set the airplane mode setting
extern bool mbp_state_airplane_mode_get();
extern void mbp_state_airplane_mode_set(bool enabled);

//C2 getters/setters
extern bool mbp_state_c2_level_get();
extern void mbp_state_c2_level_set(bool);
extern bool mbp_state_c2_points_get();
extern void mbp_state_c2_points_set(bool);
extern bool mbp_state_c2_unlock_get();
extern void mbp_state_c2_unlock_set(bool);

extern uint16_t mbp_state_chip8_fg_color_get();
extern void mbp_state_chip8_fg_color_set(uint16_t c);
extern uint16_t mbp_state_chip8_bg_color_get();
extern void mbp_state_chip8_bg_color_set(uint16_t c);

//Get and set master badge mode
extern bool mbp_state_master_get();
extern void mbp_state_master_set(bool master);

//Get and set tilt state
extern bool mbp_state_tilt_get();
extern void mbp_state_tilt_set(bool tilt_state);

//Get and set unlocked state
extern uint16_t mbp_state_unlock_get();
extern void mbp_state_unlock_set(uint16_t unlock_state);

#endif /* MBP_BADGE_STATE_H_ */
