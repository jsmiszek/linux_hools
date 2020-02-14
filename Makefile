all: directory makeprograms linkprograms

directory: clean
	mkdir -p ODP
	mkdir -p FIFO_files

makeprograms:
	$(MAKE) -C start
	$(MAKE) -C serwer
	$(MAKE) -C klient

linkprograms:
	ln -s ../start/start ODP/start
	ln -s ../serwer/serwer ODP/serwer
	ln -s ../klient/klient ODP/klient
	

clean:
	$(MAKE) -C start clean
	$(MAKE) -C serwer clean
	$(MAKE) -C klient clean
	rm -rf ODP
	rm -rf FIFO_files
