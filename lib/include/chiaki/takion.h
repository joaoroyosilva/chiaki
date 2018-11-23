/*
 * This file is part of Chiaki.
 *
 * Chiaki is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chiaki is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chiaki.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CHIAKI_TAKION_H
#define CHIAKI_TAKION_H

#include "common.h"
#include "thread.h"
#include "log.h"

#include <netinet/in.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef void (*ChiakiTakionDataCallback)(uint8_t *buf, size_t buf_size, void *user);


typedef struct chiaki_takion_connect_info_t
{
	ChiakiLog *log;
	struct sockaddr *sa;
	socklen_t sa_len;
	ChiakiTakionDataCallback data_cb;
	void *data_cb_user;
} ChiakiTakionConnectInfo;


typedef struct chiaki_takion_t
{
	ChiakiLog *log;
	ChiakiTakionDataCallback data_cb;
	void *data_cb_user;
	int sock;
	ChiakiThread thread;
	int stop_pipe[2];
	struct timeval recv_timeout;
	int send_retries;
	uint32_t tag_local;
	uint32_t tag_remote;
	uint32_t seq_num_local;
} ChiakiTakion;


CHIAKI_EXPORT ChiakiErrorCode chiaki_takion_connect(ChiakiTakion *takion, ChiakiTakionConnectInfo *info);
CHIAKI_EXPORT void chiaki_takion_close(ChiakiTakion *takion);
CHIAKI_EXPORT ChiakiErrorCode chiaki_takion_send_raw(ChiakiTakion *takion, uint8_t *buf, size_t buf_size);
CHIAKI_EXPORT ChiakiErrorCode chiaki_send_message_data(ChiakiTakion *takion, uint8_t *buf, size_t buf_size);

#ifdef __cplusplus
}
#endif

#endif // CHIAKI_TAKION_H
