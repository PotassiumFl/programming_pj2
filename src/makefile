CC := gcc
TARGET := ..\\build\\main
SRCS := main.c data.c node.c save.c screen.c
OBJS := $(SRCS:.c=.o)
all: $(TARGET)
$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS)
%.o:%.c
	$(CC) -c $< -o $@
clean:
	del $(OBJS)