TARGET	= ulib_dist.tar.gz

$(TARGET):
	make -C src/
	make -C lib/
	make -C test/
	tar czf $(TARGET) include/ lib/libulib.a test/

.PHONY: clean remove_bak debug release

debug: $(TARGET)

release:
	make -C src/
	make -C lib/ release
	make -C test/
	tar czf $(TARGET) include/ lib/libulib.a test/

clean:
	rm -rf $(TARGET)
	make -C src/ clean
	make -C test/ clean
	make -C lib/ clean

remove_bak:
	find . -name "*~" | xargs rm
