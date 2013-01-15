/*
 *
 *  neard - Near Field Communication manager
 *
 *  Copyright (C) 2012  Intel Corporation. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#define SNEP_VERSION		0x10
#define SNEP_MAJOR(version) (((version) >> 4) & 0xf)
#define SNEP_MINOR(version) ((version) & 0xf)

#define SNEP_MSG_SIZE			0x06
#define SNEP_ACCEPTABLE_LENGTH		1024
#define SNEP_ACC_LENGTH_SIZE		4

/* Request codes */
#define SNEP_REQ_CONTINUE 0x00
#define SNEP_REQ_GET      0x01
#define SNEP_REQ_PUT      0x02
#define SNEP_REQ_REJECT   0x7f

/* Response codes */
#define SNEP_RESP_CONTINUE  0x80
#define SNEP_RESP_SUCCESS   0x81
#define SNEP_RESP_NOT_FOUND 0xc0
#define SNEP_RESP_EXCESS    0xc1
#define SNEP_RESP_BAD_REQ   0xc2
#define SNEP_RESP_NOT_IMPL  0xe0
#define SNEP_RESP_VERSION   0xe1
#define SNEP_RESP_REJECT    0xff

#define SNEP_REQ_PUT_HEADER_LENGTH	6
#define SNEP_REQ_GET_HEADER_LENGTH	10
/* Default SNEP Resp message header length: Version + code + len */
#define SNEP_RESP_HEADER_LENGTH		(1 + 1 + 4)


/* TODO: Right now it is dummy, need to get correct value
 * from lower layers */
#define SNEP_REQ_MAX_FRAGMENT_LENGTH 128

typedef near_bool_t (*near_server_io) (int client_fd, void *snep_data);

struct p2p_snep_data {
	uint8_t *nfc_data;
	uint32_t nfc_data_length;
	uint32_t nfc_data_current_length;
	uint8_t *nfc_data_ptr;
	uint32_t adapter_idx;
	uint32_t target_idx;
	gboolean respond_continue;
	near_tag_io_cb cb;
	struct p2p_snep_put_req_data *req;
};

near_bool_t snep_core_read(int client_fd,
				uint32_t adapter_idx, uint32_t target_idx,
				near_tag_io_cb cb,
				near_server_io req_get,
				near_server_io req_put);

int snep_core_push(int fd, uint32_t adapter_idx, uint32_t target_idx,
						struct near_ndef_message *ndef,
						near_device_io_cb cb);

void snep_core_close(int client_fd, int err);

void snep_core_response_noinfo(int client_fd, uint8_t response);
void snep_core_response_with_info(int client_fd, uint8_t response,
						uint8_t *data, int length);
void snep_core_parse_handover_record(int client_fd, uint8_t *ndef,
						uint32_t nfc_data_length);
int snep_init(void);
void snep_exit(void);

int snep_validation_init(void);
void snep_validation_exit(void);
