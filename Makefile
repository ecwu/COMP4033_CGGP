SRC = ./src
MAKE = make

.PHONY: clean

all:
	$(MAKE) -C $(SRC)/model

clean:
	$(MAKE) -C $(SRC)/model clean