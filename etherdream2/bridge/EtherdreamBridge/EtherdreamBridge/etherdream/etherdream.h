#ifndef ETHERDREAM_H
#define ETHERDREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "protocol.h"
    
#define _POSIX_C_SOURCE 199309L
#define _DARWIN_C_SOURCE 1
    
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
    
#ifdef __MACH__
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

struct etherdream_point {
	int16_t x;
	int16_t y;
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t i;
	uint16_t u1;
	uint16_t u2;
};

    
#define BUFFER_POINTS_PER_FRAME 16000
#define BUFFER_NFRAMES          2
#define MAX_LATE_ACKS		64
#define MIN_SEND_POINTS		40
#define DEFAULT_TIMEOUT		2000000
#define DEBUG_THRESHOLD_POINTS	800

    
    struct etherdream_conn {
        int dc_sock;
        char dc_read_buf[1024];
        int dc_read_buf_size;
        struct dac_response resp;
        long long dc_last_ack_time;
        
        struct {
            struct queue_command queue;
            struct data_command_header header;
            struct dac_point data[1000];
        } __attribute__((packed)) dc_local_buffer;
        
        int dc_begin_sent;
        int ackbuf[MAX_LATE_ACKS];
        int ackbuf_prod;
        int ackbuf_cons;
        int unacked_points;
        int pending_meta_acks;
    };
    
    struct buffer_item {
        struct dac_point data[BUFFER_POINTS_PER_FRAME];
        int points;
        int pps;
        int repeatcount;
        int idx;
    };
    
    enum dac_state {
        ST_DISCONNECTED,
        ST_READY,
        ST_RUNNING,
        ST_BROKEN,
        ST_SHUTDOWN
    };
    
    struct etherdream {
        pthread_mutex_t mutex;
        pthread_cond_t loop_cond;
        
        struct buffer_item buffer[BUFFER_NFRAMES];
        int frame_buffer_read;
        int frame_buffer_fullness;
        int bounce_count;
        
        pthread_t workerthread;
        
        struct in_addr addr;
        struct etherdream_conn conn;
        unsigned long dac_id;
        int sw_revision;
        char mac_address[6];
        char version[32];
        
        enum dac_state state;
        
        struct etherdream * next;
    };
    
struct etherdream;

/* etherdream_lib_start()
 *
 * Initialize the Ether Dream library and start a background thread to listen
 * for DAC broadcasts. This should be called exactly once at program startup.
 *
 * Returns 0 on success, -1 on failure.
 */
int etherdream_lib_start(void);
int etherdream_lib_discover(void);

/* etherdream_dac_count()
 *
 * Return the number of detected DACs since etherdream_lib_start() was called.
 * Ether Dream DACs broadcast once per second, so calling code should wait a
 * little over a second after etherdream_lib_start() to ensure that all DACs
 * on the network are seen.
 */ 
int etherdream_dac_count(void);

/* etherdream_get(idx)
 *
 * Return the i'th detected DAC. This function accepts either an integer index
 * (0-based) or an ID value as returned by etherdream_get_id(). Returns NULL
 * if the requested DAC is not available.
 */
struct etherdream *etherdream_get(unsigned long idx);
struct etherdream* etherdream_ip(const char* ip);

/* etherdream_get_id(d)
 *
 * Return the ID value (equal to the second half of the MAC address, when
 * represented in hex) of the given Ether Dream. Does not require that a
 * connection to d has been established.
 */
unsigned long etherdream_get_id(struct etherdream *d);

/* etherdream_connect(d)
 *
 * Open a connection to d. This must be called before most other etherdream_
 * functions can be used.
 */
int etherdream_connect(struct etherdream *d);

/* etherdream_is_ready(d)
 *
 * Return 1 if the local buffer for d can accept more frames, 0 if not, -1 on
 * error (if the connection to d has not been opened or has failed).
 */
int etherdream_is_ready(struct etherdream *d);

/* etherdream_wait_for_ready(d)
 *
 * Block the invoking thread until more data can be written to d. Returns 0 on
 * success, -1 if the connection to d is not open or has failed.
 */
int etherdream_wait_for_ready(struct etherdream *d);

/* etherdream_write(d, pts, npts, pps, repeatcount)
 *
 * Write a "frame" consisting of pts (length npts) to d.
 *
 * If repeatcount is -1, pts will be sent to the laser repeatedly until new
 * data is received or until etherdream_stop is called. Otherwise, the points
 * will be sent repeatedly at most npts times, and then the stream will
 * automatically stop. pps specifies the output rate (30000 is a common value).
 * repeatcount must not be 0.
 *
 * The Ether Dream uses a continuous streaming protocol, so if new frames are
 * continuously sent, frame boundaries are not visible; however, to reduce
 * overhead, frames should be reasonably large (at least 50-100 points).
 */
int etherdream_write(struct etherdream *d, const struct etherdream_point *pts,
                     int npts, int pps, int repeatcount);

/* etherdream_stop(d)
 *
 * Stop output from d as soon as the current frame is finished.
 */
int etherdream_stop(struct etherdream *d);

/* etherdream_disconnect(d)
 *
 * Close the TCP connection to d.
 */
void etherdream_disconnect(struct etherdream *d);

#ifdef __cplusplus
} // extern "c"
#endif

#endif // ETHERDREAM_H
