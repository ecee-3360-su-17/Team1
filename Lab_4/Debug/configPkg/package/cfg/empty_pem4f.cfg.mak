# invoke SourceDir generated makefile for empty.pem4f
empty.pem4f: .libraries,empty.pem4f
.libraries,empty.pem4f: package/cfg/empty_pem4f.xdl
	$(MAKE) -f /Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/Lab_4/src/makefile.libs

clean::
	$(MAKE) -f /Users/dannylangevin/Desktop/School/Senior/Digital Design Lab/Team1/Lab_4/src/makefile.libs clean

