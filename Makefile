target := riscv64-unknown-linux-gnu

CC=$(target)-gcc
LD=$(target)-ld
LIBS=-l
SDIR=src
ODIR=obj
INC=-Iinclude

SRCC:=$(wildcard $(SDIR)/*.c)
OBJC=$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCC))

SRCS:=$(wildcard $(SDIR)/*.S)
OBJS=$(patsubst $(SDIR)/%.S, $(ODIR)/%.o, $(SRCS))
	
$(ODIR)/%.o: $(SDIR)/%.c
	$(AT)mkdir -p $(ODIR)
	$(AT)$(CC) $(INC) -c $< -o $@

$(ODIR)/%.o: $(SDIR)/%.S
	$(AT)mkdir -p $(ODIR)
	$(AT)$(CC) $(INC) -c $< -o $@

all: $(OBJC) $(OBJS)
	$(LD) $(ODIR)/*.o -nostdlib -static -nostartfiles -T proxy_kernel.lds -o proxy_kernel

.PHONY: clean

clean:
	$(AT)rm -f $(ODIR)/*.o
	$(AT)rm -rf $(ODIR)
	$(AT)rm -rf proxy_kernel
