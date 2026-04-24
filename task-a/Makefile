CC = gcc
CFLAGS = -Wall -Wextra -g

# vuln build - turned some protections off so we can actually see it break in the lab
VULN_CFLAGS = -fno-stack-protector -z execstack -no-pie -g

.PHONY: all vulnerable secure clean

all: vulnerable secure

vulnerable: vulnerable.c
	$(CC) $(VULN_CFLAGS) -o vulnerable vulnerable.c

secure: secure.c
	$(CC) $(CFLAGS) -D_FORTIFY_SOURCE=2 -O2 -o secure secure.c

clean:
	rm -f vulnerable secure
