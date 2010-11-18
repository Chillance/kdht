/*
 * kdht.h
 */

 #ifdef __cplusplus
 extern "C" {
 #endif

#pragma once

#define KDHT_PROTO	1
#define KDHT_ID_LEN	20

typedef enum {
	KDHT_SEARCH,	/* On search completion (d: char *name). */
	KDHT_MSG_RECV,	/* On message receive (d: KDHT_contact *peer). */
} kdht_event;

typedef char	kdht_id[KDHT_ID_LEN];
extern int	kdht_ip_len;

typedef struct {
	kdht_id	id;
	int	last;
	int	rtt;
	char	*ip;
	int	port;
} kdht_contact;

typedef void kdht_callback(kdht_event evt, char *buf, int size, void *d);

typedef enum {
	KDHT_DEAD,
	KDHT_ALIVE,
	KDHT_ACTIVE,
} kdht_info;

void	  kdht_init(kdht_callback func, int encryption, int debug);
kdht_info kdht_status();
	  /* Requests a peer listing from a rendezvous server. You can join a DHT
	   * this way. 'server' can be an IPv4/6 address or a DNS-resolvable name.
	   * The server cannot be blocked by a NAT device. */
void      kdht_rendezvous(const char *server);
	  /* Adds the given peers to the routing table. This is another way to
	   * join a DHT. */
void	  kdht_bootstrap(kdht_contact **peers, int nr_peers);
void	  kdht_search(const char *name, kdht_id *name_id /* 0 */);
void	  kdht_insert(const char *name, kdht_id *name_id /* 0 */, char *buf, int size);
void	  kdht_sendmsg(kdht_contact *peer, char *buf, int size, kdht_id *msg_id /* 0 */);
	  /* The output file may be used and replicated on rendezvous servers. */
void	  kdht_save(const char *ofile);
void	  kdht_load(const char *ifile);
void	  kdht_pause();
void	  kdht_shutdown();

 #ifdef __cplusplus
 }
 #endif

