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
#ifndef UTIL_UTIL_BLE_H_
#define UTIL_UTIL_BLE_H_

#define COMPANY_ID							0x049E		/** AND!XOR LLC :-) **/
#define COMPANY_ID_CPV						0x0C97
#define COMPANY_ID_DC503					0x0503
#define COMPANY_ID_DC801					0x0801		/** DC801?? **/
#define COMPANY_ID_QUEERCON					0x04D3

typedef struct {
	ble_gap_addr_t address;
	char name[SETTING_NAME_LENGTH];
	uint16_t company_id;
	uint16_t device_id;
	uint32_t last_seen;
	uint8_t level;
	int8_t rssi;
	bool said_hello;
	uint8_t avatar;
} ble_badge_t;

#define BADGE_DB_SIZE						32
typedef struct {
	ble_badge_t badges[BADGE_DB_SIZE];
	volatile uint16_t badge_count;
} ble_badge_db_t;

extern void util_ble_advertising_start();
extern void util_ble_avatar_update();
extern ble_badge_db_t *util_ble_badge_db_get();
extern uint32_t util_ble_connect(ble_gap_addr_t *p_address);
extern uint32_t util_ble_disconnect();
extern void util_ble_c2_set(master_c2_t *p_c2);
extern void util_ble_init();
extern void util_ble_level_set(uint8_t level);
extern void util_ble_name_get(char *name);
extern void util_ble_name_set(char *name);
extern uint32_t util_ble_nus_send(char *p_string, uint16_t length);
extern void util_ble_off();
extern void util_ble_on();
extern void util_ble_scan_start();

#endif /* UTIL_UTIL_BLE_H_ */
