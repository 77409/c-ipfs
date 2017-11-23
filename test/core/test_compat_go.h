#include "stdio.h"

#include "libp2p/utils/logger.h"
#include "ipfs/core/daemon.h"
#include "ipfs/core/swarm.h"

// forward declarations
int ipfs_swarm_connect(struct IpfsNode* local_node, const char* address);


int test_compat_go_join_swarm() {
	int retVal = 0;
	char* ipfs_path1 = "/tmp/ipfs_1";
	char* config_file1 = "config.test1.wo_journal";
	pthread_t daemon_thread;
	struct FSRepo* fs_repo = NULL;

	// Here is the connection information for the GO version:
	char* remote_string = "/ip4/10.211.55.2/tcp/4001/ipfs/QmacSE6bCZiAu7nrYkhPATaSoL2q9BszkKzbX6fCiXuBGA";

	// build repo
	if (!drop_build_open_repo(ipfs_path1, &fs_repo, config_file1)) {
		ipfs_repo_fsrepo_free(fs_repo);
		libp2p_logger_error("test_api", "Unable to drop and build repository at %s\n", ipfs_path1);
		goto exit;
	}
	ipfs_repo_fsrepo_free(fs_repo);
	// start daemon
	pthread_create(&daemon_thread, NULL, test_daemon_start, (void*)ipfs_path1);
	sleep(3);

	// try to connect to a remote swarm
	struct IpfsNode *local_node = NULL;
	ipfs_node_offline_new(ipfs_path1, &local_node);
	ipfs_swarm_connect(local_node, remote_string);

	retVal = 1;
	exit:
	ipfs_daemon_stop();
	pthread_join(daemon_thread, NULL);
	return retVal;
}
