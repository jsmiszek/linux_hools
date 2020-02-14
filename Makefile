all: directory makeprograms linkprograms

directory: clean
	mkdir -p ODP
	mkdir -p FIFO_files

makeprograms:
	$(MAKE) -C start
	$(MAKE) -C serwer
	$(MAKE) -C klient
	$(MAKE) -C potomek
	$(MAKE) -C arbiter
	
linkprograms:
	ln -s ../start/start ODP/start
	ln -s ../serwer/serwer ODP/serwer
	ln -s ../klient/klient ODP/klient
	ln -s ../potomek/potomek ODP/potomek
	ln -s ../arbiter/arbiter ODP/arbiter

clean:
	$(MAKE) -C start clean
	$(MAKE) -C serwer clean
	$(MAKE) -C klient clean
	$(MAKE) -C potomek clean
	$(MAKE) -C arbiter clean
	rm -rf ODP
	rm -rf FIFO_files
