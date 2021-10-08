/*
 * tnet_new_test_Tests.cpp
 *
 *  Created on: 2021
 *      Author: Janusz Wolak
 */

/*-
 * Copyright (c) 2021 Janusz Wolak  
 * All rights reserved.
 *
 */

extern "C" {
#include "../TouchstoNet/src/tnet_debug.c"
#include "../TouchstoNet/src/tnet_new_test.c"
}

#include <gtest/gtest.h>

namespace {
int32_t	kTestPortNumber = 8080;
}

class TnetNewTestTests : public ::testing::Test {
public:
	TnetNewTestTests() : new_test(NULL) {}
	struct tnet_new_test* new_test;

	void CreateNewTest(struct tnet_new_test** new_test) {
		*new_test = (struct tnet_new_test*)malloc(sizeof(struct tnet_new_test));
		memset(*new_test, 0, sizeof(struct tnet_new_test));
	}

	void CloseSocketTest(struct tnet_new_test* new_test) {
		shutdown(new_test->socket_fd, SHUT_RDWR);
	}

	void CreateServerSocketAddressTest(struct tnet_new_test** new_test) {
		(*new_test)->server_socket_address_stuct = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
		(*new_test)->server_socket_address_stuct->sin_family = AF_INET;
		(*new_test)->server_socket_address_stuct->sin_addr.s_addr = INADDR_ANY;
		(*new_test)->server_socket_address_stuct->sin_port = htons(kTestPortNumber);
	}

	void CreateSocketTest(struct tnet_new_test* new_test) {
		new_test->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	}

	void TearDown() override {
	}
};


TEST_F(TnetNewTestTests, Allocate_New_Test_Struct_And_True_Returned) {
	ASSERT_TRUE(tnet_create_new_test(&new_test));
}

TEST_F(TnetNewTestTests, Allocate_New_Test_Struct_And_Memory_Allocated) {
	tnet_create_new_test(&new_test);
	ASSERT_TRUE(new_test);
}

TEST_F(TnetNewTestTests, Free_New_Test_And_True_Returned) {
	CreateNewTest(&new_test);
	ASSERT_TRUE(tnet_free_new_test(new_test));
}

TEST_F(TnetNewTestTests, Try_Free_New_Test_Which_Is_Null_And_False_Returned) {
	ASSERT_FALSE(tnet_free_new_test(new_test));
}

TEST_F(TnetNewTestTests, Create_Socket_File_Descriptor_And_True_Is_Returned) {
	CreateNewTest(&new_test);
	ASSERT_TRUE(tnet_create_socket_fd(new_test, AF_INET, SOCK_STREAM, 0));
	CloseSocketTest(new_test);
}

TEST_F(TnetNewTestTests, Try_Create_Socket_For_Null_New_Test_Struct_And_False_Returned) {
	ASSERT_FALSE(tnet_create_socket_fd(new_test, AF_INET, SOCK_STREAM, 0));
}

TEST_F(TnetNewTestTests, Cretate_New_Server_Socket_Address_Struct_And_True_Returned) {
	CreateNewTest(&new_test);
	ASSERT_TRUE(tnet_create_server_socket_address(&new_test, AF_INET, INADDR_ANY, kTestPortNumber));
}

TEST_F(TnetNewTestTests, Try_Cretate_New_Server_Socket_Address_Struct_For_Null_New_Test_Struct_And_False_Returned) {
	ASSERT_FALSE(tnet_create_server_socket_address(&new_test, AF_INET, INADDR_ANY, kTestPortNumber));
}

TEST_F(TnetNewTestTests, Cretate_New_Server_Socket_Address_Struct_And_Struct_Is_Allocated) {
	CreateNewTest(&new_test);
	tnet_create_server_socket_address(&new_test, AF_INET, INADDR_ANY, kTestPortNumber);
	ASSERT_TRUE(new_test->server_socket_address_stuct);
}

TEST_F(TnetNewTestTests, Cretate_New_Client_Socket_Address_Struct_And_True_Returned) {
	CreateNewTest(&new_test);
	ASSERT_TRUE(tnet_create_client_socket_address(&new_test));
}

TEST_F(TnetNewTestTests, Try_Cretate_New_Client_Socket_Address_Struct_For_Null_New_Test_Struct_And_False_Returned) {
	ASSERT_FALSE(tnet_create_client_socket_address(&new_test));
}

TEST_F(TnetNewTestTests, Cretate_New_Client_Socket_Address_Struct_And_Struct_Is_Allocated) {
	CreateNewTest(&new_test);
	tnet_create_client_socket_address(&new_test);
	ASSERT_TRUE(new_test->client_socket_address_stuct);
}

TEST_F(TnetNewTestTests, Try_Bind_To_Proper_Socket_And_True_Returned) {
	CreateNewTest(&new_test);
	CreateServerSocketAddressTest(&new_test);
	CreateSocketTest(new_test);
	ASSERT_TRUE(tnet_bind_to_socket(new_test));
	CloseSocketTest(new_test);
}

TEST_F(TnetNewTestTests, Try_Bind_To_Improper_Socket_And_False_Returned) {
	CreateNewTest(&new_test);
	CreateSocketTest(new_test);
	ASSERT_FALSE(tnet_bind_to_socket(new_test));
}

TEST_F(TnetNewTestTests, Try_Bind_For_Null_New_Test_Struct_And_False_Returned) {
	ASSERT_FALSE(tnet_bind_to_socket(new_test));
}
