CC = gcc
CFLAGS = -std=c11 -Wall -I./

# 获取lib目录下所有的.c文件
LIB_SRCS = $(wildcard lib/*.c)
# 将.c文件替换成.o文件
LIB_OBJS = $(patsubst lib/%.c,lib/%.o,$(LIB_SRCS))

# 定义客户端和服务端的目标文件
CLIENT_SRCS = $(wildcard tcpcliserv/tcpcli*.c)
SERVER_SRCS = $(wildcard tcpcliserv/tcpserv*.c)
CLIENT_TARGETS = $(patsubst tcpcliserv/%.c,tcpcliserv/%,$(CLIENT_SRCS))
SERVER_TARGETS = $(patsubst tcpcliserv/%.c,tcpcliserv/%,$(SERVER_SRCS))

# 默认目标
all: $(CLIENT_TARGETS) $(SERVER_TARGETS)

# 确保tcpcliserv文件夹存在
$(shell mkdir -p tcpcliserv)

# 编译客户端程序
tcpcliserv/tcpcli%: tcpcliserv/tcpcli%.c libunp.a
	@echo "Compiling $@..."
	$(CC) $(CFLAGS) -o $@ $< libunp.a

# 编译服务端程序
tcpcliserv/tcpserv%: tcpcliserv/tcpserv%.c tcpcliserv/sigchildwait.c libunp.a
	@echo "Compiling $@..."
	$(CC) $(CFLAGS) -o $@ $< tcpcliserv/sigchildwait.c libunp.a

# 打包成libunp.a静态库
libunp.a: $(LIB_OBJS)
	@echo "Creating libunp.a..."
	ar rcs libunp.a $(LIB_OBJS)

# 编译lib目录下的所有.c文件
lib/%.o: lib/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标文件和静态库
clean:
	rm -f $(CLIENT_TARGETS) $(SERVER_TARGETS)
	rm -f libunp.a $(LIB_OBJS)
