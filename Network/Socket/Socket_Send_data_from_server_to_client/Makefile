all: server client

server:  $(wildcard Server/*.c)
	gcc -g -Wall $< -o $@

client: $(wildcard Client/*.c)
	gcc -g -Wall $< -o $@

clean:
	rm -f server
	rm -f client
