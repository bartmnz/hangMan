CFLAGS= -std=c11 -Wall -Wextra -pedantic -Wno-deprecated  -Wstack-usage=1024 

TARGET=hangMan
OBJS=hangMan.o

.PHONY: clean debug profile

$(TARGET): $(OBJS)


debug: CFLAGS+=g
debug: $(TARGET)


clean:
	-$(RM) $(TARGET) $(OBJS)

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg
profile: $(TARGET)
hangMan.o: 
