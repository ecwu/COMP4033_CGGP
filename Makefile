SRC = ./src
MAKE = make

.PHONY: clean

all:
	$(MAKE) -C $(SRC)

clean:
	$(MAKE) -C $(SRC) clean
