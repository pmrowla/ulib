.PHONY: all clean release test

all:
	make -C src/
	make -C lib/
	make -C test/

release:
	make DEBUG=-DUNDEBUG -C src/
	make -C lib/ release
	make DEBUG=-DUNDEBUG -C test/

clean:
	make -C src/ clean
	make -C test/ clean
	make -C lib/ clean
	@find . -name "*~" | xargs rm -rf

test:
	make -C test/ test
