SRC = ./src
MAKE = make
CP = cp -r
RM = rm -rf

.PHONY: clean

all:
	$(MAKE) -C $(SRC)/model
	mkdir -p bin
	$(CP) $(SRC)/model/bin/* bin

clean:
	$(MAKE) -C $(SRC)/model clean
	$(RM) bin
