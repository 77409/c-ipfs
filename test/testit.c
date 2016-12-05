#include "cid/test_cid.h"
#include "cmd/ipfs/test_init.h"
#include "flatfs/test_flatfs.h"
#include "merkledag/test_merkledag.h"
#include "node/test_node.h"
#include "repo/test_repo_bootstrap_peers.h"
#include "repo/test_repo_config.h"
#include "repo/test_repo_fsrepo.h"
#include "repo/test_repo_identity.h"
#include "storage/test_ds_helper.h"
#include "storage/test_datastore.h"
#include "storage/test_blocks.h"
 		 
int testit(const char* name, int (*func)(void)) {
	printf("Testing %s...\n", name);
	int retVal = func();
	if (retVal)
		printf("%s success!\n", name);
	else
		printf("** Uh oh! %s failed.**\n", name);
	return retVal == 0;
}

const char* names[] = {
		"test_cid_new_free",
		"test_cid_cast_multihash",
		"test_cid_cast_non_multihash",
		//"test_init_new_installation",
		"test_repo_config_new",
		"test_repo_config_init",
		"test_repo_config_write",
		"test_repo_config_identity_new",
		"test_repo_config_identity_private_key",
		"test_get_init_command",
		"test_repo_fsrepo_open_config",
		"test_flatfs_get_directory",
		"test_flatfs_get_filename",
		"test_flatfs_get_full_filename",
		"test_ds_key_from_binary",
		"test_blocks_new",
		"test_repo_bootstrap_peers_init",
		"test_ipfs_datastore_put",
		"test_node",
		"test_merkledag_add_data"
};

int (*funcs[])(void) = {
		test_cid_new_free,
		test_cid_cast_multihash,
		test_cid_cast_non_multihash,
		//test_init_new_installation,
		test_repo_config_new,
		test_repo_config_init,
		test_repo_config_write,
		test_repo_config_identity_new,
		test_repo_config_identity_private_key,
		test_get_init_command,
		test_repo_fsrepo_open_config,
		test_flatfs_get_directory,
		test_flatfs_get_filename,
		test_flatfs_get_full_filename,
		test_ds_key_from_binary,
		test_blocks_new,
		test_repo_bootstrap_peers_init,
		test_ipfs_datastore_put,
		test_node,
		test_merkledag_add_data
};

/**
 * run 1 test or run all
 */
int main(int argc, char** argv) {
	int counter = 0;
	int tests_ran = 0;
	char* test_wanted;
	int only_one = 0;
	if(argc > 1) {
		only_one = 1;
		if (argv[1][0] == '\'') { // some shells put quotes around arguments
			argv[1][strlen(argv[1])-1] = 0;
			test_wanted = &(argv[1][1]);
		}
		else
			test_wanted = argv[1];
	}
	int array_length = sizeof(funcs) / sizeof(funcs[0]);
	for (int i = 0; i < array_length; i++) {
		if (only_one && strcmp(names[i], test_wanted) == 0) {
			tests_ran++;
			counter += testit(names[i], funcs[i]);
		}
		else
			if (!only_one) {
				tests_ran++;
				counter += testit(names[i], funcs[i]);
			}

	}

	if (tests_ran == 0)
		printf("***** No tests found *****\n");
	else {
		if (counter > 0) {
			printf("***** There were %d failed test(s) *****\n", counter);
		} else {
			printf("All %d tests passed\n", tests_ran);
		}
	}
	return 1;
}
