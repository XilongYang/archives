target=test.out
CC=g++
objects=actions.o judge.o main.o menu.o space.o used_space.o free_table.o used_table.o
CPPFLAGS= -g 
INCLUDEFLAGS= -I include
vpath %.cc src
vpath %.h include

$(target): $(objects)
	$(CC) $(objects) -o $(target)

%.o:%.cc
	$(CC) -o $@ -c $< $(CPPFLAGS) $(INCLUDEFLAGS)

%.d:%.cc
	@set -e; rm -f $@; $(CC) -MM $< $(INCLUDEFLAGS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(objects:.o=.d)

.PHONY:clean
clean:
	-rm $(objects) $(target) *.d