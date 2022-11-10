OBJ = my_ls.o
	TARGET = my_ls

%.o: %.c 
	gcc -c $< -o $@

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $@

fclean:
	-rm -f $(OBJ)
	-rm -f $(TARGET)
.PHONY: fclean 
