APP = stream-example

# Add any other object files to this list below
APP_OBJS = stream-example.o streamcontrolsyn.o streamcontrolsyn_linux.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) -o $@ $(APP_OBJS) $(LDFLAGS) $(LDLIBS)
clean:
	rm -f $(APP) *.o
